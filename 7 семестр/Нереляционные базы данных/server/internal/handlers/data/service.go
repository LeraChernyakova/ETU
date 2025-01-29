package data

import (
	"context"

	v1 "plants/internal/pkg/pb/data/v1"
)

type Storage interface {
	ExportDB(context.Context) ([]byte, error)
	ImportDB(context.Context, []byte) error
}

type Handler struct {
	v1.UnimplementedDataAPIServer
	storage Storage
}

func New(storage Storage) *Handler {
	return &Handler{
		storage: storage,
	}
}
