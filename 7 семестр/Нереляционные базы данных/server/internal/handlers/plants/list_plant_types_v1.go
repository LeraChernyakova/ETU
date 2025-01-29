package plants

import (
	"context"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"

	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) ListPlantTypesV1(
	ctx context.Context,
	req *api.GetPlantTypesV1Request,
) (*api.GetPlantTypesV1Response, error) {
	types, err := h.storage.GetTypes(ctx)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "some error occured while getting types %v", err)
	}
	return &api.GetPlantTypesV1Response{
		Types: types,
	}, nil
}
