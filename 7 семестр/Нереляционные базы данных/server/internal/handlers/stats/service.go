package stats

import (
	"context"
	"plants/internal/models"
	v1 "plants/internal/pkg/pb/stats/v1"
)

type Storage interface {
	GetPlantsStats(ctx context.Context, filter map[string]interface{}) (*models.PlantsStats, error)
	GetBuyStats(ctx context.Context, filter map[string]interface{}) (*models.BuyStats, error)
	GetTradeStats(ctx context.Context, filter map[string]interface{}) (*models.TradeStats, error)
	GetAdsStats(ctx context.Context, filter map[string]interface{}) (*models.AdsStats, error)
}

type Handler struct {
	v1.UnimplementedStatsAPIServer
	storage Storage
}

func New(storage Storage) *Handler {
	return &Handler{
		storage: storage,
	}
}

func parseFilter(rawFilter *v1.TimeFilter) map[string]interface{} {
	return map[string]interface{}{
		"from": rawFilter.TimeFrom.AsTime(),
		"to":   rawFilter.TimeTo.AsTime(),
	}
}
