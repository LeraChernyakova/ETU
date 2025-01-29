package users

import (
	"context"
	"errors"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"

	api "plants/internal/pkg/pb/users/v1"
	repo "plants/internal/storage"
)

func (h *Handler) UserLoginV1(
	ctx context.Context,
	req *api.UserLoginV1Request,
) (*api.UserLoginV1Response, error) {
	if req.GetLogin() == "" || req.GetPassword() == "" {
		return &api.UserLoginV1Response{}, status.Error(codes.InvalidArgument, "login and password are required")
	}
	id, role, err := h.storage.GetUserByLoginAndPassword(ctx, req.GetLogin(), req.GetPassword())
	if err != nil {
		if errors.Is(err, repo.ErrUserNotFound) {
			return &api.UserLoginV1Response{}, status.Error(codes.NotFound, "user not found")
		}
		return &api.UserLoginV1Response{}, status.Error(codes.Internal, err.Error())
	}
	return &api.UserLoginV1Response{
		Id:   id,
		Role: api.Role(role),
	}, nil
}
