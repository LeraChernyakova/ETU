package data

import (
	"context"
	"os"

	api "plants/internal/pkg/pb/data/v1"
)

func (h *Handler) ImportDBV1(
	ctx context.Context,
	req *api.ImportDBV1Request,
) (*api.ImportDBV1Response, error) {
	filePath := "imported_db.json"
	err := os.WriteFile(filePath, req.Db, 0644)
	if err != nil {
		return nil, err
	}
	defer os.Remove(filePath)
	fileData, err := os.ReadFile(filePath)
	if err != nil {
		return nil, err
	}
	err = h.storage.ImportDB(ctx, fileData)
	if err != nil {
		return nil, err
	}
	return &api.ImportDBV1Response{}, nil
}