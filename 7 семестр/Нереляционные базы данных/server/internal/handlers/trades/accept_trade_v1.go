package trades

import (
	"context"

	api "plants/internal/pkg/pb/trades/v1"
)

func (h *Handler) AcceptTradeV1(
	ctx context.Context,
	req *api.AcceptTradeV1Request,
) (*api.AcceptTradeV1Response, error) {
	err := h.storage.UpdateTrade(ctx, req.TradeId, 2)
	if err != nil {
		return &api.AcceptTradeV1Response{}, err
	}
	return &api.AcceptTradeV1Response{}, err
}
