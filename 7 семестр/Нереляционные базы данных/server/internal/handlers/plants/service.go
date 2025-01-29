package plants

import (
	"context"

	"plants/internal/models"
	api "plants/internal/pkg/pb/plants/v1"

	"go.mongodb.org/mongo-driver/bson/primitive"
)

type Storage interface {
	GetPlantsWithCareRules(ctx context.Context, fltr *models.Filter) ([]*models.CareRules, int64, error)
	CreateNewCareRule(ctx context.Context, rule *models.CareRules) error
	GetCareRulesForPlant(ctx context.Context, id string) (*models.CareRules, error)
	GetPlants(ctx context.Context, fltr *models.Filter) ([]*models.Plant, int64, error)
	AddPlant(ctx context.Context, plant *models.Plant) error
	GetPlantsForTrade(ctx context.Context, id string) ([]*models.Plant, error)
	GetPlant(ctx context.Context, id string) (*models.Plant, error)
	GetUserById(ctx context.Context, id string) (models.User, error)
	CreateBuyTrade(ctx context.Context, trade *models.Trade) error
	DeletePlantFromUser(ctx context.Context, userId, plantId string) error
	SoldPlant(ctx context.Context, id string) error
	GetTradesByIds(ctx context.Context, ids []primitive.ObjectID, tradeType string, tradeStatus int8) ([]*models.Trade, error)
	GetUserTrades(ctx context.Context, id string) ([]primitive.ObjectID, error)
	GetPlantsByIds(ctx context.Context, ids []string, fltr *models.Filter) ([]*models.Plant, error)
	AddTradeToUser(ctx context.Context, userId, tradeId primitive.ObjectID) error
	GetPlantsByUserId(ctx context.Context, userId string, isSold bool) ([]*models.Plant, error)
	AddPlantToUser(ctx context.Context, plant *models.Plant) error
	GetTypes(ctx context.Context) ([]string, error)
}

type Handler struct {
	api.UnimplementedPlantsAPIServer
	storage Storage
}

func New(storage Storage) *Handler {
	return &Handler{
		storage: storage,
	}
}

func parseFilterLabels(fltr *api.Filter) *models.Filter {
	var labels = make(map[string]interface{})
	if len(fltr.Species) != 0 {
		labels["species"] = fltr.Species
	}
	if len(fltr.Type) != 0 {
		labels["type"] = fltr.Type
	}
	if len(fltr.Size) != 0 {
		labels["size"] = fltr.Size
	}
	if len(fltr.LightCondition) != 0 {
		labels["light_condition"] = fltr.LightCondition
	}
	if len(fltr.WateringFrequency) != 0 {
		labels["watering_frequency"] = fltr.WateringFrequency
	}
	if len(fltr.TemperatureRegime) != 0 {
		labels["temperature_regime"] = fltr.TemperatureRegime
	}
	if len(fltr.CareComplexity) != 0 {
		labels["care_complexity"] = fltr.CareComplexity
	}
	if len(fltr.Description) != 0 {
		labels["description"] = fltr.Description
	}
	if len(fltr.Place) != 0 {
		labels["place"] = fltr.Place
	}
	if fltr.PriceFrom != 0 {
		labels["price_from"] = fltr.PriceFrom
	}
	if fltr.PriceTo != 0 {
		labels["price_to"] = fltr.PriceTo
	}
	return &models.Filter{
		Labels: labels,
	}
}
