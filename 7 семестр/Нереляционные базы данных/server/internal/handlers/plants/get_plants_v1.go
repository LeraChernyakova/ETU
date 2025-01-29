package plants

import (
	"context"

	"go.mongodb.org/mongo-driver/bson/primitive"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"

	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) GetPlantsV1(
	ctx context.Context,
	req *api.GetPlantsV1Request,
) (*api.GetPlantsV1Response, error) {
	filter := parseFilterLabels(req.Filter)
	filter.Page = req.Page
	filter.Size = req.Size
	filter.SortBy = req.Sort
	filter.IsDesc = req.IsDesc
	userId, err := primitive.ObjectIDFromHex(req.UserId)
	if err != nil {
		return nil, status.Errorf(codes.InvalidArgument, "Cannot convert user id %v", err)
	}
	filter.Labels["user_id"] = userId
	plants, count, err := h.storage.GetPlants(ctx, filter)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not get plants. Error %v", err)
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
	return &api.GetPlantsV1Response{
		Plants: result,
		Count:  count,
	}, nil
}
