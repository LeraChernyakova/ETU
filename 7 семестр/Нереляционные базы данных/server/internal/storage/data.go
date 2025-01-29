package storage

import (
	"context"
	"encoding/json"
	"errors"
	"html"
	"log"

	"go.mongodb.org/mongo-driver/bson"
	"go.mongodb.org/mongo-driver/mongo"
)

func (s *Storage) ImportDB(ctx context.Context, jsonData []byte) error {
	collections, err := s.Client.Database("plants_market").ListCollectionNames(ctx, bson.D{})
	if err != nil {
		return errors.New("ошибка получения списка коллекций: " + err.Error())
	}
	for _, collectionName := range collections {
		if err := s.Client.Database("plants_market").Collection(collectionName).Drop(ctx); err != nil {
			return errors.New("ошибка очистки коллекции " + collectionName + ": " + err.Error())
		}
	}
	log.Println("База данных успешно очищена.")

	var data map[string][]bson.M
	if err := json.Unmarshal(jsonData, &data); err != nil {
		return errors.New("ошибка парсинга JSON: " + err.Error())
	}

	for collectionName, documents := range data {
		if len(documents) == 0 {
			continue
		}

		collection := s.Client.Database("plants_market").Collection(collectionName)
		var interfaceDoc []interface{}
		for _, doc := range documents {
			interfaceDoc = append(interfaceDoc, doc)
		}
		_, err := collection.InsertMany(ctx, interfaceDoc)
		if err != nil {
			return errors.New("ошибка вставки данных в коллекцию " + collectionName + ": " + err.Error())
		}
	}

	return nil
}

func (s *Storage) ExportDB(ctx context.Context) ([]byte, error) {
	data := make(map[string]interface{})
	collections := []string{"users", "plants", "trades", "care_rules"}

	for _, col := range collections {
		collectionData, err := readCollection(ctx, s.Client, "plants_market", col)
		if err != nil {
			return nil, err
		}
		data[col] = sanitizeData(collectionData)
	}

	log.Println("export before marshal")
	log.Println(data)
	jsonData, err := json.Marshal(data)
	log.Println("export after marshal")
	log.Println(jsonData)
	if err != nil {
		return nil, errors.New("ошибка преобразования данных в JSON: " + err.Error())
	}

	return jsonData, nil
}

func sanitizeData(data []bson.M) []bson.M {
	for _, doc := range data {
		for key, value := range doc {
			if str, ok := value.(string); ok {
				doc[key] = html.EscapeString(str) // Очистка строк
			}
		}
	}
	return data
}

func readCollection(ctx context.Context, client *mongo.Client, dbName, colName string) ([]bson.M, error) {
	collection := client.Database(dbName).Collection(colName)
	cursor, err := collection.Find(ctx, bson.D{})
	if err != nil {
		return nil, err
	}
	defer cursor.Close(ctx)

	var results []bson.M
	if err = cursor.All(ctx, &results); err != nil {
		return nil, err
	}

	return results, nil
}