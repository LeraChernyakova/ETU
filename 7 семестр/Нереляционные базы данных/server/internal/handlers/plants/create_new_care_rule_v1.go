package plants

import (
	"context"
	"time"

	"go.mongodb.org/mongo-driver/bson/primitive"
	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"

	"plants/internal/models"
	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) CreateNewCareRuleV1(
	ctx context.Context,
	req *api.CreateNewCareRuleV1Request,
) (*api.CreateNewCareRuleV1Response, error) {
	userId, err := primitive.ObjectIDFromHex(req.UserId)
	if err != nil {
		return nil, status.Error(codes.InvalidArgument, "invalid user id")
	}
	user, err := h.storage.GetUserById(ctx, req.UserId)
	if err != nil {
		return nil, status.Errorf(codes.NotFound, "user not found %v", err)
	}
	err = h.storage.CreateNewCareRule(ctx, &models.CareRules{
		Species:   req.Species,
		CreatedAt: time.Now().UTC(),
		UpdatedAt: time.Now().UTC(),
		Description: []models.CareDescriptionPart{
			{
				UserID:              userId,
				DescriptionAddition: req.DescriptionAddition,
				CreatedAt:           time.Now().UTC(),
				UserName:            user.Name,
				UserSurname:         user.Surname,
				UserFatherName:      user.FatherName,
			},
		},
		LightCondition:    req.LightCondition,
		Image:             req.Image,
		Type:              req.Type,
		TemperatureRegime: req.TemperatureRegime,
	})
	if err != nil {
		return nil, status.Error(codes.Internal, "Internal error occured")
	}
	return &api.CreateNewCareRuleV1Response{}, nil
}
