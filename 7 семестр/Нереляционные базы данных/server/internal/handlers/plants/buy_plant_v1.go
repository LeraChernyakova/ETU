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

func (h *Handler) BuyPlantV1(
	ctx context.Context,
	req *api.BuyPlantV1Request,
) (*api.BuyPlantV1Response, error) {
	plant, err := h.storage.GetPlant(ctx, req.PlantId)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot find plant by Id. Error %v", err)
	}
	offerer, err := h.storage.GetUserById(ctx, req.BuyerId)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot find offerer by Id. Error %v", err)
	}
	accepter, err := h.storage.GetUserById(ctx, req.SellerId)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "cannot find accepter by Id. Error %v", err)
	}
	err = h.storage.SoldPlant(ctx, req.PlantId)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not sold plants. Error %v", err)
	}
	trade := models.Trade{
		ID: primitive.NewObjectID(),
		Offerer: models.TradeUser{
			ID:         offerer.ID,
			Name:       offerer.Name,
			Surname:    offerer.Surname,
			FatherName: offerer.FatherName,
			Plant: models.TradePlant{
				ID:    plant.ID,
				Name:  plant.Species,
				Image: plant.Image,
				Price: plant.Price,
			},
		},
		Accepter: models.TradeUser{
			ID:         accepter.ID,
			Name:       accepter.Name,
			Surname:    accepter.Surname,
			FatherName: accepter.FatherName,
		},
		Type:      "buy",
		Status:    2,
		CreatedAt: time.Now().UTC(),
		UpdatedAt: time.Now().UTC(),
	}
	err = h.storage.DeletePlantFromUser(ctx, accepter.ID.Hex(), plant.ID.Hex())
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not delete plant from user. Error %v", err)
	}
	err = h.storage.CreateBuyTrade(ctx, &trade)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not create trade. Error %v", err)
	}
	err = h.storage.AddTradeToUser(ctx, accepter.ID, trade.ID)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not add trade to buyer. Error %v", err)
	}
	err = h.storage.AddTradeToUser(ctx, offerer.ID, trade.ID)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "could not add trade to seller. Error %v", err)
	}
	return &api.BuyPlantV1Response{}, nil
}
