package config

import (
	"os"
	"time"

	"github.com/ilyakaznacheev/cleanenv"
)

type Config struct {
	Env   string      `yaml:"env"`
	GRPC  GRPCConfig  `yaml:"grpc"`
	Mongo MongoConfig `yaml:"mongo"`
}

type MongoConfig struct {
	User     string `yaml:"user"`
	Host     string `yaml:"host"`
	DataBase string `yaml:"database"`
	Password string `yaml:"password"`
	Port     string `yaml:"port"`
}

type GRPCConfig struct {
	Port    int           `yaml:"port"`
	Timeout time.Duration `yaml:"timeout"`
}

func MustLoad() *Config {
	path := os.Getenv("CONFIG_PATH")
	if path == "" {
		panic("config path is empty")
	}

	if _, err := os.Stat(path); os.IsNotExist(err) {
		panic("config file does not exist: " + path)
	}

	var cfg Config

	if err := cleanenv.ReadConfig(path, &cfg); err != nil {
		panic("unable to load config: " + err.Error())
	}

	return &cfg
}
