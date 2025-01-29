package stats

import (
	"context"
	api "plants/internal/pkg/pb/stats/v1"
	"time"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"
)

func (h *Handler) GetTradeStatsV1(ctx context.Context,
	req *api.GetTradeStatsV1Request,
) (*api.GetTradeStatsV1Response, error) {
	fltr := parseFilter(req.Filter)
	trades, err := h.storage.GetTradeStats(ctx, fltr)
	if err != nil {
		return nil, status.Errorf(codes.Internal, "Error occured %v", err)
	}
	stats := make([]*api.GetTradeStatsV1Response_StatsInfo, len(trades.Info))
	for i, p := range trades.Info {
		t, err := time.Parse("2006-01-02", p.Date)
		if err != nil {
			return nil, status.Errorf(codes.Internal, "Error occured %v", err)
		}
		stats[i] = &api.GetTradeStatsV1Response_StatsInfo{
			Date:   timestamppb.New(t),
			Count:  p.Count,
			Status: int64(p.Status),
		}
	}
	return &api.GetTradeStatsV1Response{
		Count: trades.Count,
		Stats: stats,
	}, nil
}
