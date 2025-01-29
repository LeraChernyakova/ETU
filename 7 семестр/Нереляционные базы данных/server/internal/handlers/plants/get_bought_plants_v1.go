package plants

import (
	"context"

	api "plants/internal/pkg/pb/plants/v1"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"
)

func (h *Handler) GetBoughtPlantsV1(
	ctx context.Context,
	req *api.GetBoughtPlantsV1Request,
) (*api.GetBoughtPlantsV1Response, error) {
	tradeIds, err := h.storage.GetUserTrades(ctx, req.UserId)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot get users trades %v", err)
	}
	trades, err := h.storage.GetTradesByIds(ctx, tradeIds, "buy", 2)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot get trades %v", err)
	}
	plantsIds := make([]string, len(trades))
	for i, t := range trades {
		plantsIds[i] = t.Offerer.Plant.ID.Hex()
	}
	fltr := parseFilterLabels(req.Filter)
	plants, err := h.storage.GetPlantsByIds(ctx, plantsIds, fltr)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot get plants %v", err)
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
	return &api.GetBoughtPlantsV1Response{
		Plants: result,
	}, nil
}
