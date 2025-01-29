package main

import (
	"context"
	"log"
	"log/slog"
	"time"

	"go.mongodb.org/mongo-driver/v2/bson"
	"go.mongodb.org/mongo-driver/v2/mongo"
	"go.mongodb.org/mongo-driver/v2/mongo/options"
)

func main() {
	ctx, stop := context.WithTimeout(context.Background(), 10*time.Second)
	defer stop()

	conn, err := mongo.Connect(options.Client().ApplyURI("mongodb://user:pass@mongodb:27017"))
	if err != nil {
		log.Fatal(err)
	}
	defer func() {
		if err := conn.Disconnect(ctx); err != nil {
			log.Fatal(err)
		}
	}()

	collection := conn.Database("example").Collection("example")

	type person struct {
		Name string `bson:"name"`
	}

	_, err = collection.InsertMany(ctx, []interface{}{
		person{"Alice"},
		person{"Bob"},
		person{"Charlie"},
	})
	if err != nil {
		slog.Error("failed to store data", slog.AnyValue(err))
	}

	cur, err := collection.Find(ctx, bson.D{})
	if err != nil {
		slog.Error("failed to find data", slog.AnyValue(err))
	}
	defer func() {
		if err = cur.Close(ctx); err != nil {
			log.Fatal(err)
		}
	}()

	for cur.Next(ctx) {
		var res person
		if err = cur.Decode(&res); err != nil {
			slog.Error("failed to decode data", slog.AnyValue(err))
			continue
		}
		slog.Info("stored data", slog.Any("person", res))
	}
}
