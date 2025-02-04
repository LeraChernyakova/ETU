// Code generated by protoc-gen-go-grpc. DO NOT EDIT.
// versions:
// - protoc-gen-go-grpc v1.5.1
// - protoc             v3.6.1
// source: stats/v1/stats.proto

package stats_v1

import (
	context "context"
	grpc "google.golang.org/grpc"
	codes "google.golang.org/grpc/codes"
	status "google.golang.org/grpc/status"
)

// This is a compile-time assertion to ensure that this generated file
// is compatible with the grpc package it is being compiled against.
// Requires gRPC-Go v1.64.0 or later.
const _ = grpc.SupportPackageIsVersion9

const (
	StatsAPI_GetPlantsStatsV1_FullMethodName = "/stats.v1.StatsAPI/GetPlantsStatsV1"
	StatsAPI_GetBuyStatsV1_FullMethodName    = "/stats.v1.StatsAPI/GetBuyStatsV1"
	StatsAPI_GetTradeStatsV1_FullMethodName  = "/stats.v1.StatsAPI/GetTradeStatsV1"
	StatsAPI_GetAdsStatsV1_FullMethodName    = "/stats.v1.StatsAPI/GetAdsStatsV1"
)

// StatsAPIClient is the client API for StatsAPI service.
//
// For semantics around ctx use and closing/ending streaming RPCs, please refer to https://pkg.go.dev/google.golang.org/grpc/?tab=doc#ClientConn.NewStream.
type StatsAPIClient interface {
	GetPlantsStatsV1(ctx context.Context, in *GetPlantsStatsV1Request, opts ...grpc.CallOption) (*GetPlantsStatsV1Response, error)
	GetBuyStatsV1(ctx context.Context, in *GetBuyStatsV1Request, opts ...grpc.CallOption) (*GetBuyStatsV1Response, error)
	GetTradeStatsV1(ctx context.Context, in *GetTradeStatsV1Request, opts ...grpc.CallOption) (*GetTradeStatsV1Response, error)
	GetAdsStatsV1(ctx context.Context, in *GetAdsStatsV1Request, opts ...grpc.CallOption) (*GetAdsStatsV1Response, error)
}

type statsAPIClient struct {
	cc grpc.ClientConnInterface
}

func NewStatsAPIClient(cc grpc.ClientConnInterface) StatsAPIClient {
	return &statsAPIClient{cc}
}

func (c *statsAPIClient) GetPlantsStatsV1(ctx context.Context, in *GetPlantsStatsV1Request, opts ...grpc.CallOption) (*GetPlantsStatsV1Response, error) {
	cOpts := append([]grpc.CallOption{grpc.StaticMethod()}, opts...)
	out := new(GetPlantsStatsV1Response)
	err := c.cc.Invoke(ctx, StatsAPI_GetPlantsStatsV1_FullMethodName, in, out, cOpts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *statsAPIClient) GetBuyStatsV1(ctx context.Context, in *GetBuyStatsV1Request, opts ...grpc.CallOption) (*GetBuyStatsV1Response, error) {
	cOpts := append([]grpc.CallOption{grpc.StaticMethod()}, opts...)
	out := new(GetBuyStatsV1Response)
	err := c.cc.Invoke(ctx, StatsAPI_GetBuyStatsV1_FullMethodName, in, out, cOpts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *statsAPIClient) GetTradeStatsV1(ctx context.Context, in *GetTradeStatsV1Request, opts ...grpc.CallOption) (*GetTradeStatsV1Response, error) {
	cOpts := append([]grpc.CallOption{grpc.StaticMethod()}, opts...)
	out := new(GetTradeStatsV1Response)
	err := c.cc.Invoke(ctx, StatsAPI_GetTradeStatsV1_FullMethodName, in, out, cOpts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

func (c *statsAPIClient) GetAdsStatsV1(ctx context.Context, in *GetAdsStatsV1Request, opts ...grpc.CallOption) (*GetAdsStatsV1Response, error) {
	cOpts := append([]grpc.CallOption{grpc.StaticMethod()}, opts...)
	out := new(GetAdsStatsV1Response)
	err := c.cc.Invoke(ctx, StatsAPI_GetAdsStatsV1_FullMethodName, in, out, cOpts...)
	if err != nil {
		return nil, err
	}
	return out, nil
}

// StatsAPIServer is the server API for StatsAPI service.
// All implementations must embed UnimplementedStatsAPIServer
// for forward compatibility.
type StatsAPIServer interface {
	GetPlantsStatsV1(context.Context, *GetPlantsStatsV1Request) (*GetPlantsStatsV1Response, error)
	GetBuyStatsV1(context.Context, *GetBuyStatsV1Request) (*GetBuyStatsV1Response, error)
	GetTradeStatsV1(context.Context, *GetTradeStatsV1Request) (*GetTradeStatsV1Response, error)
	GetAdsStatsV1(context.Context, *GetAdsStatsV1Request) (*GetAdsStatsV1Response, error)
	mustEmbedUnimplementedStatsAPIServer()
}

// UnimplementedStatsAPIServer must be embedded to have
// forward compatible implementations.
//
// NOTE: this should be embedded by value instead of pointer to avoid a nil
// pointer dereference when methods are called.
type UnimplementedStatsAPIServer struct{}

func (UnimplementedStatsAPIServer) GetPlantsStatsV1(context.Context, *GetPlantsStatsV1Request) (*GetPlantsStatsV1Response, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetPlantsStatsV1 not implemented")
}
func (UnimplementedStatsAPIServer) GetBuyStatsV1(context.Context, *GetBuyStatsV1Request) (*GetBuyStatsV1Response, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetBuyStatsV1 not implemented")
}
func (UnimplementedStatsAPIServer) GetTradeStatsV1(context.Context, *GetTradeStatsV1Request) (*GetTradeStatsV1Response, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetTradeStatsV1 not implemented")
}
func (UnimplementedStatsAPIServer) GetAdsStatsV1(context.Context, *GetAdsStatsV1Request) (*GetAdsStatsV1Response, error) {
	return nil, status.Errorf(codes.Unimplemented, "method GetAdsStatsV1 not implemented")
}
func (UnimplementedStatsAPIServer) mustEmbedUnimplementedStatsAPIServer() {}
func (UnimplementedStatsAPIServer) testEmbeddedByValue()                  {}

// UnsafeStatsAPIServer may be embedded to opt out of forward compatibility for this service.
// Use of this interface is not recommended, as added methods to StatsAPIServer will
// result in compilation errors.
type UnsafeStatsAPIServer interface {
	mustEmbedUnimplementedStatsAPIServer()
}

func RegisterStatsAPIServer(s grpc.ServiceRegistrar, srv StatsAPIServer) {
	// If the following call pancis, it indicates UnimplementedStatsAPIServer was
	// embedded by pointer and is nil.  This will cause panics if an
	// unimplemented method is ever invoked, so we test this at initialization
	// time to prevent it from happening at runtime later due to I/O.
	if t, ok := srv.(interface{ testEmbeddedByValue() }); ok {
		t.testEmbeddedByValue()
	}
	s.RegisterService(&StatsAPI_ServiceDesc, srv)
}

func _StatsAPI_GetPlantsStatsV1_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetPlantsStatsV1Request)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(StatsAPIServer).GetPlantsStatsV1(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: StatsAPI_GetPlantsStatsV1_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(StatsAPIServer).GetPlantsStatsV1(ctx, req.(*GetPlantsStatsV1Request))
	}
	return interceptor(ctx, in, info, handler)
}

func _StatsAPI_GetBuyStatsV1_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetBuyStatsV1Request)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(StatsAPIServer).GetBuyStatsV1(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: StatsAPI_GetBuyStatsV1_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(StatsAPIServer).GetBuyStatsV1(ctx, req.(*GetBuyStatsV1Request))
	}
	return interceptor(ctx, in, info, handler)
}

func _StatsAPI_GetTradeStatsV1_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetTradeStatsV1Request)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(StatsAPIServer).GetTradeStatsV1(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: StatsAPI_GetTradeStatsV1_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(StatsAPIServer).GetTradeStatsV1(ctx, req.(*GetTradeStatsV1Request))
	}
	return interceptor(ctx, in, info, handler)
}

func _StatsAPI_GetAdsStatsV1_Handler(srv interface{}, ctx context.Context, dec func(interface{}) error, interceptor grpc.UnaryServerInterceptor) (interface{}, error) {
	in := new(GetAdsStatsV1Request)
	if err := dec(in); err != nil {
		return nil, err
	}
	if interceptor == nil {
		return srv.(StatsAPIServer).GetAdsStatsV1(ctx, in)
	}
	info := &grpc.UnaryServerInfo{
		Server:     srv,
		FullMethod: StatsAPI_GetAdsStatsV1_FullMethodName,
	}
	handler := func(ctx context.Context, req interface{}) (interface{}, error) {
		return srv.(StatsAPIServer).GetAdsStatsV1(ctx, req.(*GetAdsStatsV1Request))
	}
	return interceptor(ctx, in, info, handler)
}

// StatsAPI_ServiceDesc is the grpc.ServiceDesc for StatsAPI service.
// It's only intended for direct use with grpc.RegisterService,
// and not to be introspected or modified (even as a copy)
var StatsAPI_ServiceDesc = grpc.ServiceDesc{
	ServiceName: "stats.v1.StatsAPI",
	HandlerType: (*StatsAPIServer)(nil),
	Methods: []grpc.MethodDesc{
		{
			MethodName: "GetPlantsStatsV1",
			Handler:    _StatsAPI_GetPlantsStatsV1_Handler,
		},
		{
			MethodName: "GetBuyStatsV1",
			Handler:    _StatsAPI_GetBuyStatsV1_Handler,
		},
		{
			MethodName: "GetTradeStatsV1",
			Handler:    _StatsAPI_GetTradeStatsV1_Handler,
		},
		{
			MethodName: "GetAdsStatsV1",
			Handler:    _StatsAPI_GetAdsStatsV1_Handler,
		},
	},
	Streams:  []grpc.StreamDesc{},
	Metadata: "stats/v1/stats.proto",
}
