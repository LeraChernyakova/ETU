package app

import (
	"context"
	"fmt"
	"log/slog"
	"net"
	"net/http"

	"github.com/grpc-ecosystem/grpc-gateway/runtime"
	"golang.org/x/sync/errgroup"
	"google.golang.org/grpc"

	"plants/internal/config"
	"plants/internal/handlers/data"
	"plants/internal/handlers/plants"
	"plants/internal/handlers/stats"
	"plants/internal/handlers/trades"
	"plants/internal/handlers/users"
	dataAPI "plants/internal/pkg/pb/data/v1"
	plantsAPI "plants/internal/pkg/pb/plants/v1"
	statsAPI "plants/internal/pkg/pb/stats/v1"
	tradesAPI "plants/internal/pkg/pb/trades/v1"
	usersAPI "plants/internal/pkg/pb/users/v1"
	"plants/internal/storage"
)

func Run(cfg *config.Config) error {
	ctx, cancel := context.WithCancel(context.Background())
	defer cancel()
	gRPCServer := grpc.NewServer()
	mongoURL := fmt.Sprintf(
		"mongodb://%s:%s@%s:%s",
		cfg.Mongo.User,
		cfg.Mongo.Password,
		cfg.Mongo.Host,
		cfg.Mongo.Port,
	)
	slog.Info(mongoURL)
	repo, err := storage.New(ctx, mongoURL, cfg.Mongo.DataBase)
	if err != nil {
		return err
	}

	plantsHandler := plants.New(repo)
	plantsAPI.RegisterPlantsAPIServer(gRPCServer, plantsHandler)

	usersHandler := users.New(repo)
	usersAPI.RegisterUserServer(gRPCServer, usersHandler)

	tradesHandler := trades.New(repo)
	tradesAPI.RegisterTradesServer(gRPCServer, tradesHandler)

	dataHandler := data.New(repo)
	dataAPI.RegisterDataAPIServer(gRPCServer, dataHandler)

	statsHandler := stats.New(repo)
	statsAPI.RegisterStatsAPIServer(gRPCServer, statsHandler)

	mux := runtime.NewServeMux()
	if err = plantsAPI.RegisterPlantsAPIHandlerServer(ctx, mux, plantsHandler); err != nil {
		return err
	}

	if err = usersAPI.RegisterUserHandlerServer(ctx, mux, usersHandler); err != nil {
		return err
	}

	if err = tradesAPI.RegisterTradesHandlerServer(ctx, mux, tradesHandler); err != nil {
		return err
	}
	if err = dataAPI.RegisterDataAPIHandlerServer(ctx, mux, dataHandler); err != nil {
		return err
	}
	if err = statsAPI.RegisterStatsAPIHandlerServer(ctx, mux, statsHandler); err != nil {
		return err
	}

	var group errgroup.Group
	l, err := net.Listen("tcp", fmt.Sprintf(":%v", cfg.GRPC.Port))

	if err != nil {
		return err
	}
	group.Go(func() error {
		slog.Info("Started grpc server")
		return gRPCServer.Serve(l)
	})

	group.Go(func() error {
		slog.Info("Started http server")
		return http.ListenAndServe(":8881", mux)
	})
	return group.Wait()
}
