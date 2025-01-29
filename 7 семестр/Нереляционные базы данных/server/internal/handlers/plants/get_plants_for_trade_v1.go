package plants

import (
	"context"
	"fmt"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"

	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) GetPlantsForTradeV1(
	ctx context.Context,
	req *api.GetPlantsForTradeV1Request,
) (*api.GetPlantsForTradeV1Response, error) {
	plants, err := h.storage.GetPlantsForTrade(ctx, req.UserId)
	if err != nil {
		return nil, status.Error(codes.Internal, "cant get plants")
	}

	result := make([]*api.GetPlantsForTradeV1Response_PlantInfo, len(plants))
	for i, r := range plants {
		result[i] = &api.GetPlantsForTradeV1Response_PlantInfo{
			Species:   r.Species,
			Price:     fmt.Sprintf("%f", r.Price),
			Place:     r.Place,
			CreatedAt: timestamppb.New(r.CreatedAt),
			Id:        r.ID.Hex(),
			Image:     r.Image,
		}
	}
	return &api.GetPlantsForTradeV1Response{
		Plants: result,
	}, nil
}
