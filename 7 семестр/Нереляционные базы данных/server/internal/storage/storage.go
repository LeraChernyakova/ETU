package storage

import (
	"context"
	"log/slog"

	"go.mongodb.org/mongo-driver/mongo"
	"go.mongodb.org/mongo-driver/mongo/options"
)

type Storage struct {
	Client   *mongo.Client
	DataBase *mongo.Database
}

func New(ctx context.Context, uri, db string) (*Storage, error) {
	client, err := mongo.Connect(ctx, options.Client().ApplyURI(uri))
	if err != nil {
		slog.Error("unable to connect")
		return nil, err
	}
	err = client.Ping(ctx, nil)
	if err != nil {
		slog.Error("ping doesnt work")
		return nil, err
	}
	database := client.Database(db)
	return &Storage{
		DataBase: database,
		Client:   client,
	}, nil
}

func (s *Storage) Disconnect(ctx context.Context) error {
	return s.Client.Disconnect(ctx)
}
