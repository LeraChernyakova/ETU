package storage

import (
	"context"
	"time"

	"plants/internal/models"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

type valsType interface {
	string | primitive.ObjectID
}

func (s *Storage) GetPlantsWithCareRules(ctx context.Context, fltr *models.Filter) ([]*models.CareRules, int64, error) {
	collection := s.DataBase.Collection("care_rules")
	filter := primitive.D{}
	if v, ok := fltr.Labels["description"]; ok {
		filter = append(filter, bson.E{
			Key: "description", Value: bson.M{"$elemMatch": bson.M{"description_addition": bson.M{"$regex": v, "$options": "i"}}},
		},
		)
		delete(fltr.Labels, "description")
	}
	filter = append(filter, parseLabelsToBSON(fltr.Labels)...)
	opts := options.Find()
	opts.SetLimit(fltr.Size)
	opts.SetSkip((fltr.Page - 1) * fltr.Size)
	count, err := collection.CountDocuments(ctx, filter)
	if err != nil {
		return nil, 0, err
	}
	cursor, err := collection.Find(ctx, filter, opts)
	if err != nil {
		return nil, 0, err
	}
	rules := make([]*models.CareRules, 0)
	for cursor.Next(ctx) {
		var rule models.CareRules
		if err = cursor.Decode(&rule); err != nil {
			return nil, 0, err
		}
		rules = append(rules, &rule)
	}
	return rules, count, nil
}

func (s *Storage) CreateNewCareRule(ctx context.Context, rule *models.CareRules) error {
	collection := s.DataBase.Collection("care_rules")
	result := collection.FindOne(ctx, bson.M{
		"species":            rule.Species,
		"temperature_regime": rule.TemperatureRegime,
		"light_condition":    rule.LightCondition,
		"type":               rule.Type,
	})
	if result.Err() != nil && result.Err() == mongo.ErrNoDocuments {
		_, err := collection.InsertOne(ctx, rule)
		return err
	}
	newAddition := bson.D{
		{Key: "description_addition", Value: rule.Description[0].DescriptionAddition},
		{Key: "created_at", Value: rule.Description[0].CreatedAt},
		{Key: "user_id", Value: rule.Description[0].UserID},
	}
	update := bson.D{
		{Key: "$push", Value: bson.D{{Key: "description", Value: newAddition}}},
		{Key: "$set", Value: bson.D{{Key: "update_at", Value: rule.UpdatedAt}}},
		{Key: "$set", Value: bson.D{{Key: "image", Value: rule.Image}}},
	}
	_, err := collection.UpdateOne(ctx, bson.M{
		"species":            rule.Species,
		"temperature_regime": rule.TemperatureRegime,
		"light_condition":    rule.LightCondition,
		"type":               rule.Type,
	}, update)
	return err
}

func (s *Storage) GetCareRulesForPlant(ctx context.Context, id string) (*models.CareRules, error) {
	collection := s.DataBase.Collection("care_rules")
	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return nil, err
	}
	filter := bson.M{"_id": objID}
	cursor := collection.FindOne(ctx, filter)

	var result models.CareRules
	err = cursor.Decode(&result)
	if err != nil {
		return nil, err
	}
	for i, d := range result.Description {
		u, err := s.GetUserById(ctx, d.UserID.Hex())
		if err != nil {
			return nil, err
		}
		result.Description[i].UserName = u.Name
		result.Description[i].UserSurname = u.Surname
		result.Description[i].UserFatherName = u.FatherName
	}
	return &result, nil
}

func (s *Storage) GetPlants(ctx context.Context, fltr *models.Filter) ([]*models.Plant, int64, error) {
	filter := bson.D{{"sold_at", time.Time{}}}
	opts := options.Find()
	if fltr.SortBy != "" {
		opts.SetSort(bson.D{{Key: fltr.SortBy, Value: parseSortType(fltr.IsDesc)}})
	}
	opts.SetLimit(fltr.Size)
	opts.SetSkip((fltr.Page - 1) * fltr.Size)
	if len(fltr.Labels) != 0 {
		filter = append(filter, parseLabelsToBSON(fltr.Labels)...)
	}
	collection := s.DataBase.Collection("plants")
	count, err := collection.CountDocuments(ctx, filter)
	if err != nil {
		return nil, 0, err
	}
	cursor, err := collection.Find(ctx, filter, opts)
	if err != nil {
		return nil, 0, err
	}
	plants := make([]*models.Plant, 0)
	for cursor.Next(ctx) {
		var plant models.Plant
		if err := cursor.Decode(&plant); err != nil {
			return nil, 0, err
		}
		plants = append(plants, &plant)
	}
	return plants, count, nil
}

func (s *Storage) AddPlant(ctx context.Context, plant *models.Plant) error {
	collection := s.DataBase.Collection("plants")
	_, err := collection.InsertOne(ctx, plant)
	if err != nil {
		return err
	}
	return nil
}

func (s *Storage) GetPlantsForTrade(ctx context.Context, id string) ([]*models.Plant, error) {
	collection := s.DataBase.Collection("plants")
	collectionTrades := s.DataBase.Collection("trades")
	objID, err := primitive.ObjectIDFromHex(id)

	filter := bson.D{
		{"user_id", objID},
		{"sold_at", time.Time{}},
	}
	doc, err := collection.Find(ctx, filter)
	if err != nil {
		return nil, err
	}
	plants := make([]*models.Plant, 0)
	for doc.Next(ctx) {
		var plant models.Plant
		if err := doc.Decode(&plant); err != nil {
			return nil, err
		}
		filter := bson.D{
			{Key: "$and", Value: bson.A{
				bson.D{
					{Key: "$or", Value: bson.A{
						bson.D{{Key: "offerer.plant._id", Value: plant.ID}},
						bson.D{{Key: "accepter.plant._id", Value: plant.ID}},
					}},
				},
				bson.D{
					{Key: "$or", Value: bson.A{
						bson.D{{Key: "status", Value: 1}},
						bson.D{{Key: "status", Value: 2}},
					}},
				},
			}},
		}
		var tmpTrade models.Trade
		if err = collectionTrades.FindOne(ctx, filter).Decode(&tmpTrade); err != nil {
			plants = append(plants, &plant)
		}
	}
	return plants, nil
}

func (s *Storage) GetPlant(ctx context.Context, id string) (*models.Plant, error) {
	collection := s.DataBase.Collection("plants")
	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return nil, err
	}
	var plant models.Plant
	if err = collection.FindOne(ctx, bson.D{{"_id", objID}}).Decode(&plant); err != nil {
		return nil, err
	}
	return &plant, nil
}

func (s *Storage) SoldPlant(ctx context.Context, id string) error {
	collection := s.DataBase.Collection("plants")
	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return err
	}
	_, err = collection.UpdateOne(ctx, bson.D{{"_id", objID}}, bson.M{"$set": bson.M{"sold_at": time.Now().UTC()}})
	if err != nil {
		return err
	}
	return nil

}

func (s *Storage) GetPlantsByIds(ctx context.Context, ids []string, fltr *models.Filter) ([]*models.Plant, error) {
	var (
		plants []*models.Plant
	)
	collection := s.DataBase.Collection("plants")
	objIDs, err := convertStringToIDs(ids)
	if err != nil {
		return nil, err
	}
	filter := parseLabelsToBSON(fltr.Labels)
	filter = append(filter, createOrFilter("_id", objIDs)...)
	cur, err := collection.Find(ctx, filter)
	if err != nil {
		return nil, err
	}
	for cur.Next(ctx) {
		var plant models.Plant
		if err := cur.Decode(&plant); err != nil {
			return nil, err
		}
		plants = append(plants, &plant)
	}
	return plants, nil
}

func (s *Storage) GetPlantsByUserId(ctx context.Context, userId string, isSold bool) ([]*models.Plant, error) {
	var plants []*models.Plant
	objID, err := primitive.ObjectIDFromHex(userId)
	if err != nil {
		return nil, err
	}
	collection := s.DataBase.Collection("plants")
	filter := bson.D{{"user_id", objID}}
	if isSold {
		filter = append(filter, bson.E{"sold_at", bson.M{"$ne": time.Time{}}})
	} else {
		filter = append(filter, bson.E{"sold_at", time.Time{}})
	}
	cur, err := collection.Find(ctx, filter)
	if err != nil {
		return nil, err
	}
	for cur.Next(ctx) {
		var plant models.Plant
		if err = cur.Decode(&plant); err != nil {
			return nil, err
		}
		plants = append(plants, &plant)
	}
	return plants, nil
}

func (s *Storage) GetTypes(ctx context.Context) ([]string, error) {
	type Type struct {
		Name string `bson:"type" json:"name"`
	}
	collection := s.DataBase.Collection("plants")
	cur, err := collection.Aggregate(ctx, []bson.D{
		{
			{
				"$group",
				bson.D{
					{
						"_id",
						"$type",
					},
				},
			},
		},
		{
			{
				"$project",
				bson.D{
					{
						"_id", 0,
					},
					{
						"type", "$_id",
					},
				},
			},
		},
	})
	if err != nil {
		return nil, err
	}
	var (
		t     Type
		types []string
	)

	for cur.Next(ctx) {
		if err = cur.Decode(&t); err != nil {
			return nil, err
		}
		types = append(types, t.Name)
	}
	return types, nil
}

func parseSortType(isDesc bool) int8 {
	if isDesc {
		return -1
	}
	return 1
}

func parseLabelsToBSON(labels map[string]interface{}) bson.D {
	bsonFltr := bson.D{}
	for k, v := range labels {
		switch vc := v.(type) {
		case string:
			if k == "user_id" {
				continue
			}
			bsonFltr = append(bsonFltr, bson.E{Key: k, Value: bson.M{"$regex": vc, "$options": "i"}})
		case []string:
			bsonFltr = append(bsonFltr, createOrFilter(k, vc)...)
		}
	}
	if v, ok := labels["price_to"]; ok && v != -1 {
		bsonFltr = append(bsonFltr, bson.E{Key: "price", Value: bson.M{"$lte": v}})
	}
	if v, ok := labels["price_from"]; ok && v != -1 {
		bsonFltr = append(bsonFltr, bson.E{Key: "price", Value: bson.M{"$gte": v}})
	}
	if v, ok := labels["user_id"]; ok {
		bsonFltr = append(bsonFltr, bson.E{Key: "user_id", Value: bson.M{"$ne": v}})
	}
	return bsonFltr
}

func createOrFilter[T valsType](k string, vals []T) bson.D {
	bsonFltr := bson.D{}
	listFltr := make([]bson.D, len(vals))
	for i, e := range vals {
		listFltr[i] = bson.D{{Key: k, Value: e}}
	}
	bsonFltr = append(bsonFltr, bson.E{Key: "$or", Value: listFltr})
	return bsonFltr
}

func convertStringToIDs(ids []string) ([]primitive.ObjectID, error) {
	objIDs := make([]primitive.ObjectID, len(ids))
	for i, id := range ids {
		objID, err := primitive.ObjectIDFromHex(id)
		if err != nil {
			return nil, err
		}
		objIDs[i] = objID
	}
	return objIDs, nil
}
