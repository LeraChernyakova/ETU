package users

import (
	"context"

	api "plants/internal/pkg/pb/users/v1"
)

func (h *Handler) UpdateUserV1(
	ctx context.Context,
	req *api.UpdateUserV1Request,
) (*api.UpdateUserV1Response, error) {
	err := h.storage.UpdateUser(ctx, req.Id, req.Name, req.Surname, req.FatherName, req.Email, req.PhoneNumber, req.Photo)
	if err != nil {
		return &api.UpdateUserV1Response{}, err
	}
	return &api.UpdateUserV1Response{}, err
}
