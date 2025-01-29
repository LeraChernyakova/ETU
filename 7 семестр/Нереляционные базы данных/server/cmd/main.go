package main

import (
	"plants/internal/app"
	"plants/internal/config"
)

func main() {
	cfg := config.MustLoad()

	if err := app.Run(cfg); err != nil {
		panic(err)
	}
}
