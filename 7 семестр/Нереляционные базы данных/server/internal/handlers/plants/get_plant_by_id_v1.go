package plants

import (
	"context"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"

	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) GetPlantByIdV1(
	ctx context.Context,
	req *api.GetPlantByIdV1Request,
) (*api.GetPlantByIdV1Response, error) {
	plant, err := h.storage.GetPlant(ctx, req.Id)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not get plant. Error %v", err)
	}
	user, err := h.storage.GetUserById(ctx, plant.UserID.Hex())
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not get user. Error %v", err)
	}
	return &api.GetPlantByIdV1Response{
		Plant: &api.GetPlantByIdV1Response_PlantInfo{
			Species:           plant.Species,
			Type:              plant.Type,
			Price:             plant.Price,
			Size:              plant.Size,
			LightCondition:    plant.LightCondition,
			WateringFrequency: plant.WateringFrequency,
			TemperatureRegime: plant.TemperatureRegime,
			CareComplexity:    plant.CareComplexity,
			Description:       plant.Description,
			Place:             plant.Place,
			Image:             plant.Image,
			CreatedAt:         timestamppb.New(plant.CreatedAt),
		},
		User: &api.GetPlantByIdV1Response_User{
			Id:         user.ID.Hex(),
			Photo:      user.Photo,
			Name:       user.Name,
			Surname:    user.Surname,
			FatherName: user.FatherName,
		},
	}, nil
}
