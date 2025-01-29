package trades

import (
	"context"

	api "plants/internal/pkg/pb/trades/v1"
)

func (h *Handler) RejectTradeV1(
	ctx context.Context,
	req *api.RejectTradeV1Request,
) (*api.RejectTradeV1Response, error) {
	err := h.storage.UpdateTrade(ctx, req.TradeId, 3)
	if err != nil {
		return &api.RejectTradeV1Response{}, err
	}
	return &api.RejectTradeV1Response{}, err
}
