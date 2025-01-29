package plants

import (
	"context"

	"google.golang.org/grpc/codes"
	"google.golang.org/grpc/status"
	"google.golang.org/protobuf/types/known/timestamppb"

	api "plants/internal/pkg/pb/plants/v1"
)

func (h *Handler) GetCareRuleV1(
	ctx context.Context,
	req *api.GetCareRuleV1Request,
) (*api.GetCareRuleV1Response, error) {
	rules, err := h.storage.GetCareRulesForPlant(ctx, req.Id)
	if err != nil {
		return nil, status.Error(codes.Internal, "cant get plant")
	}
	result := make([]*api.CareRule, len(rules.Description))
	for i, r := range rules.Description {
		result[i] = &api.CareRule{
			User: &api.CareRule_User{
				UserId:         r.UserID.Hex(),
				UserName:       r.UserName,
				UserSurname:    r.UserSurname,
				UserFatherName: r.UserFatherName,
			},
			Description: r.DescriptionAddition,
			CreatedAt:   timestamppb.New(r.CreatedAt),
		}
	}
	return &api.GetCareRuleV1Response{
		CareRules: result,
	}, nil
}
