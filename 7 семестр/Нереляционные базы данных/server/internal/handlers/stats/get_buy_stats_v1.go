package stats

import (
	"context"
	api "plants/internal/pkg/pb/stats/v1"
	"time"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"
)

func (h *Handler) GetBuyStatsV1(ctx context.Context,
	req *api.GetBuyStatsV1Request,
) (*api.GetBuyStatsV1Response, error) {
	fltr := parseFilter(req.Filter)
	buyings, err := h.storage.GetBuyStats(ctx, fltr)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "Error occured %v", err)
	}
	stats := make([]*api.GetBuyStatsV1Response_StatsInfo, len(buyings.Info))
	for i, p := range buyings.Info {
		t, err := time.Parse("2006-01-02", p.Date)
		if err != nil {
			return nil, status.Errorf(codes.Internal, "Error occured %v", err)
		}
		stats[i] = &api.GetBuyStatsV1Response_StatsInfo{
			Date:  timestamppb.New(t),
			Count: p.Count,
		}
	}
	return &api.GetBuyStatsV1Response{
		Count: buyings.Count,
		Stats: stats,
	}, nil
}
