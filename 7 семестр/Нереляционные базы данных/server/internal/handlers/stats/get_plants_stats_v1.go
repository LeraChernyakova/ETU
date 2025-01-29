package stats

import (
	"context"
	api "plants/internal/pkg/pb/stats/v1"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
)

func (h *Handler) GetPlantsStatsV1(ctx context.Context,
	req *api.GetPlantsStatsV1Request,
) (*api.GetPlantsStatsV1Response, error) {
	fltr := parseFilter(req.Filter)
	if len(req.LightCondition) != 0 {
		fltr["light_condition"] = req.LightCondition
	}
	if len(req.Type) != 0 {
		fltr["type"] = req.Type
	}
	plants, err := h.storage.GetPlantsStats(ctx, fltr)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "Error occured %v", err)
	}
	stats := make([]*api.GetPlantsStatsV1Response_StatsInfo, len(plants.Info))
	for i, p := range plants.Info {
		stats[i] = &api.GetPlantsStatsV1Response_StatsInfo{
			Count:   p.Count,
			Species: p.Species,
		}
	}
	return &api.GetPlantsStatsV1Response{
		Count: plants.Count,
		Stats: stats,
	}, nil
}
