package plants

import (
	"context"

	api "plants/internal/pkg/pb/plants/v1"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"
)

func (h *Handler) GetArchivedPlantsV1(
	ctx context.Context,
	req *api.GetArchivedPlantsV1Request,
) (*api.GetArchivedPlantsV1Response, error) {
	plants, err := h.storage.GetPlantsByUserId(ctx, req.UserId, true)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot find plants due to %v", err)
	}
	result := make([]*api.Plant, len(plants))
	for i, p := range plants {
		result[i] = &api.Plant{
			Id:        p.ID.Hex(),
			Image:     p.Image,
			Species:   p.Species,
			Price:     p.Price,
			CreatedAt: timestamppb.New(p.CreatedAt),
			Place:     p.Place,
		}
	}
	return &api.GetArchivedPlantsV1Response{
		Plants: result,
	}, nil
}
