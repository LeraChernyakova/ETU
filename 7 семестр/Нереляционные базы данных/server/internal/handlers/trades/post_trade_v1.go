package trades

import (
	"context"
	"time"

	"plants/internal/models"
	api "plants/internal/pkg/pb/trades/v1"

	"go.mongodb.org/mongo-driver/bson/primitive"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

func (h *Handler) PostTradeV1(
	ctx context.Context,
	req *api.PostTradeV1Request,
) (*api.PostTradeV1Response, error) {

	offerer, erro := h.storage.GetUserByIdForTrade(ctx, req.OffererId)
	if erro != nil {
		return &api.PostTradeV1Response{}, status.Error(codes.Internal, "could not find accepters offerer")
	}
	accepter, erra := h.storage.GetUserByIdForTrade(ctx, req.AccepterId)
	if erra != nil {
		return &api.PostTradeV1Response{}, status.Error(codes.Internal, "could not find accepter")
	}
	offPlant, errop := h.storage.GetPlantByIdForTrade(ctx, req.OffererPlantId)
	if errop != nil {
		return &api.PostTradeV1Response{}, status.Error(codes.Internal, "could not find offerers plant")
	}
	accPlant, errap := h.storage.GetPlantByIdForTrade(ctx, req.AccepterPlantId)
	if errap != nil {
		return &api.PostTradeV1Response{}, status.Error(codes.Internal, "could not find accepters plant")
	}

	err := h.storage.CreateBuyTrade(ctx, &models.Trade{
		ID: primitive.NewObjectID(),
		Offerer: models.TradeUser{
			ID:         offerer.ID,
			Surname:    offerer.Surname,
			Name:       offerer.Name,
			FatherName: offerer.FatherName,
			Plant: models.TradePlant{
				ID:    offPlant.ID,
				Name:  offPlant.Species,
				Image: offPlant.Image,
				Price: offPlant.Price,
			},
		},
		Accepter: models.TradeUser{
			ID:         accepter.ID,
			Surname:    accepter.Surname,
			Name:       accepter.Name,
			FatherName: accepter.FatherName,
			Plant: models.TradePlant{
				ID:    accPlant.ID,
				Name:  accPlant.Species,
				Image: accPlant.Image,
				Price: accPlant.Price,
			},
		},
		CreatedAt: time.Now().UTC(),
		UpdatedAt: time.Now().UTC(),
		Status:    1,
		Type:      "trade",
	})
	if err != nil {
		return nil, status.Error(codes.Internal, "could not create trade")
	}
	return &api.PostTradeV1Response{}, nil
}
