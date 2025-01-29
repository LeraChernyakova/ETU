package plants

import (
	"context"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"

	"plants/internal/models"
	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) GetPlantsWithCareRulesV1(
	ctx context.Context,
	req *api.GetPlantsWithCareRulesV1Request,
) (*api.GetPlantsWithCareRulesV1Response, error) {
	filter := &models.Filter{
		Page:   req.Page,
		Size:   req.Size,
		Labels: map[string]interface{}{},
	}
	if req.Filter.Species != "" {
		filter.Labels["species"] = req.Filter.Species
	}
	if req.Filter.Type != "" {
		filter.Labels["type"] = req.Filter.Type
	}
	if len(req.Filter.LightCondition) != 0 {
		filter.Labels["light_condition"] = req.Filter.LightCondition
	}
	if len(req.Filter.TemperatureRegime) != 0 {
		filter.Labels["temperature_regime"] = req.Filter.TemperatureRegime
	}
	if req.Filter.Description != "" {
		filter.Labels["description"] = req.Filter.Description
	}
	rules, count, err := h.storage.GetPlantsWithCareRules(ctx, filter)
	if err != nil {
		return nil, status.Error(codes.Internal, "internal error occured")
	}
	result := make([]*api.GetPlantsWithCareRulesV1Response_PlantInfo, 0, len(rules))

	for _, r := range rules {
		result = append(result, &api.GetPlantsWithCareRulesV1Response_PlantInfo{
			Species: r.Species,
			Image:   r.Image,
			RuleId:  r.ID.Hex(),
			Type:    r.Type,
		})
	}
	return &api.GetPlantsWithCareRulesV1Response{
		Plants: result,
		Count:  count,
	}, nil
}
