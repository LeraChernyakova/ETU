package users

import (
	"context"
	"errors"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"

	"plants/internal/models"
	api "plants/internal/pkg/pb/users/v1"
	repo "plants/internal/storage"
)

func (h *Handler) GetUserV1(
	ctx context.Context,
	req *api.GetUserV1Request,
) (*api.GetUserV1Response, error) {
	user, err := h.storage.GetUserById(ctx, req.GetId())
	if err != nil {
		switch {
		case errors.Is(err, repo.ErrUserInvalidId):
			return &api.GetUserV1Response{}, status.Error(codes.InvalidArgument, err.Error())
		case errors.Is(err, repo.ErrUserNotFound):
			return &api.GetUserV1Response{}, status.Error(codes.NotFound, err.Error())
		default:
			return &api.GetUserV1Response{}, status.Error(codes.Internal, err.Error())
		}
	}
	return &api.GetUserV1Response{User: userToGRPC(user)}, nil
}

func userToGRPC(user models.User) *api.GetUserV1Response_User {
	return &api.GetUserV1Response_User{
		Photo:       user.Photo,
		Surname:     user.Surname,
		Name:        user.Name,
		FatherName:  user.FatherName,
		PhoneNumber: user.PhoneNumber,
		Email:       user.Email,
		CreatedAt:   timestamppb.New(user.CreatedAt),
		UpdatedAt:   timestamppb.New(user.UpdatedAt),
	}
}
