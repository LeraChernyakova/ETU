package storage

import (
	"context"
	"errors"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/bson/primitive"
	"go.mongodb.org/mongo-driver/mongo"

	"plants/internal/models"
)

func (s *Storage) GetUserByLogin(
	ctx context.Context,
	login string,
) (models.User, error) {
	collection := s.DataBase.Collection("users")

	filter := bson.D{
		{"$or", bson.A{
			bson.D{{"email", login}},
			bson.D{{"phone_number", login}},
		}}}

	var result models.User
	var err error
	if err = collection.FindOne(ctx, filter).Decode(&result); err != nil {
		if errors.Is(err, mongo.ErrNoDocuments) {
			return models.User{}, ErrUserNotFound
		}
		return models.User{}, err
	}
	return result, nil
}

func (s *Storage) GetUserByLoginAndPassword(
	ctx context.Context,
	login, password string,
) (string, models.Role, error) {
	collection := s.DataBase.Collection("users")

	filter := bson.D{
		{"$or", bson.A{
			bson.D{{"email", login}},
			bson.D{{"phone_number", login}},
		}},
		{"password", password},
	}

	var result models.User
	if err := collection.FindOne(ctx, filter).Decode(&result); err != nil {
		if errors.Is(err, mongo.ErrNoDocuments) {
			return "", 0, ErrUserNotFound
		}
		return "", 0, err
	}
	return result.ID.Hex(), result.Role, nil
}

func (s *Storage) CreateUser(ctx context.Context, user models.User) error {
	collection := s.DataBase.Collection("users")
	if _, err := collection.InsertOne(ctx, user); err != nil {
		return err
	}
	return nil
}

func (s *Storage) GetUserById(ctx context.Context, id string) (models.User, error) {
	collection := s.DataBase.Collection("users")
	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return models.User{}, ErrUserInvalidId
	}
	filter := bson.M{"_id": objID}
	var result models.User
	if err := collection.FindOne(ctx, filter).Decode(&result); err != nil {
		if errors.Is(err, mongo.ErrNoDocuments) {
			return models.User{}, ErrUserNotFound
		}
		return models.User{}, err
	}
	return result, nil
}

func (s *Storage) UpdateUser(ctx context.Context,
	id string, name string,
	surname string,
	fatherName string,
	email string,
	phoneNumber string,
	photo string) error {

	collection := s.DataBase.Collection("users")

	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return ErrUserInvalidId
	}

	filter := bson.M{"_id": objID}
	var usr models.User
	err = collection.FindOne(ctx, filter).Decode(&usr)
	if name != "" {
		usr.Name = name
	}
	if surname != "" {
		usr.Surname = surname
	}
	if fatherName != "" {
		usr.FatherName = fatherName
	}
	if email != "" {
		usr.Email = email
	}
	if phoneNumber != "" {
		usr.PhoneNumber = phoneNumber
	}
	if photo != "" {
		usr.Photo = photo
	}

	update := bson.D{
		{"$set", bson.D{
			{"name", usr.Name},
			{"surname", usr.Surname},
			{"father_name", usr.FatherName},
			{"email", usr.Email},
			{"phone_number", usr.PhoneNumber},
			{"photo", usr.Photo},
		}},
	}
	_, errres := collection.UpdateOne(ctx, filter, update)
	if errres != nil {
		return ErrUserNotUpdated
	}

	return nil
}

func (s *Storage) DeletePlantFromUser(ctx context.Context, userId, plantId string) error {
	collection := s.DataBase.Collection("users")
	uID, err := primitive.ObjectIDFromHex(userId)
	if err != nil {
		return err
	}
	pID, err := primitive.ObjectIDFromHex(plantId)
	if err != nil {
		return err
	}
	filter := bson.M{"_id": uID}
	_, err = collection.UpdateByID(ctx, filter, bson.M{
		"$pull": bson.M{"plants": bson.M{"_id": pID}},
	})
	if err != nil {
		return err
	}
	return nil
}

func (s *Storage) GetUserTrades(ctx context.Context, id string) ([]primitive.ObjectID, error) {
	objID, err := primitive.ObjectIDFromHex(id)
	if err != nil {
		return nil, err
	}
	collection := s.DataBase.Collection("users")
	var user models.User
	err = collection.FindOne(ctx, bson.D{{Key: "_id", Value: objID}}).Decode(&user)
	if err != nil {
		return nil, err
	}
	return user.Trades, nil
}

func (s *Storage) AddTradeToUser(ctx context.Context, userId, tradeId primitive.ObjectID) error {
	collection := s.DataBase.Collection("users")
	return collection.FindOneAndUpdate(
		ctx,
		bson.D{{Key: "_id", Value: userId}},
		bson.D{{Key: "$push", Value: bson.D{{Key: "trades", Value: tradeId}}}},
	).Err()
}

func (s *Storage) AddPlantToUser(ctx context.Context, plant *models.Plant) error {
	collection := s.DataBase.Collection("users")
	return collection.FindOneAndUpdate(
		ctx,
		bson.D{{Key: "_id", Value: plant.UserID}},
		bson.D{{Key: "$push", Value: bson.D{{Key: "plants", Value: plant}}}},
	).Err()
}
