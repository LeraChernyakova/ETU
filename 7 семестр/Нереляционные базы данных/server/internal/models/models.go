package models

import (
	"time"

	"go.mongodb.org/mongo-driver/bson/primitive"
)

type Role int8

const (
	Admin Role = iota + 1
	Regular
)

type User struct {
	ID          primitive.ObjectID   `bson:"_id,omitempty" json:"id"`
	Photo       string               `bson:"photo" json:"photo"`
	Surname     string               `bson:"surname" json:"surname"`
	Name        string               `bson:"name" json:"name"`
	FatherName  string               `bson:"father_name" json:"father_name"`
	PhoneNumber string               `bson:"phone_number" json:"phone_number"`
	Email       string               `bson:"email" json:"email"`
	Password    string               `bson:"password" json:"-"`
	CreatedAt   time.Time            `bson:"created_at" json:"created_at"`
	UpdatedAt   time.Time            `bson:"updated_at" json:"updated_at"`
	Plants      []Plant              `bson:"plants" json:"plants"`
	Trades      []primitive.ObjectID `bson:"trades,omitempty" json:"trades"`
	Role        Role                 `bson:"role" json:"role"`
}

type Plant struct {
	ID                primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Image             string             `bson:"image" json:"image"`
	UserID            primitive.ObjectID `bson:"user_id" json:"user_id"`
	Size              string             `bson:"size" json:"size"`
	Price             float32            `bson:"price" json:"price"`
	LightCondition    string             `bson:"light_condition" json:"light_condition"`
	WateringFrequency string             `bson:"watering_frequency" json:"watering_frequency"`
	TemperatureRegime string             `bson:"temperature_regime" json:"temperature_regime"`
	CareComplexity    string             `bson:"care_complexity" json:"care_complexity"`
	Description       string             `bson:"description" json:"description"`
	Type              string             `bson:"type" json:"type"`
	Species           string             `bson:"species" json:"species"`
	CreatedAt         time.Time          `bson:"created_at" json:"created_at"`
	Place             string             `bson:"place" json:"place"`
	SoldAt            time.Time          `bson:"sold_at" json:"sold_at"`
}

type TradeUser struct {
	ID         primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Surname    string             `bson:"surname,omitempty" json:"surname"`
	Name       string             `bson:"name,omitempty" json:"name"`
	FatherName string             `bson:"father_name,omitempty" json:"father_name"`
	Plant      TradePlant         `bson:"plant,omitempty" json:"plant"`
}

type Trade struct {
	ID        primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Offerer   TradeUser          `bson:"offerer,omitempty" json:"offerer"`
	Accepter  TradeUser          `bson:"accepter,omitempty" json:"accepter"`
	CreatedAt time.Time          `bson:"created_at" json:"created_at"`
	UpdatedAt time.Time          `bson:"updated_at" json:"updated_at"`
	Status    int                `bson:"status" json:"status"`
	Type      string             `bson:"type" json:"type"`
}

type TradePlant struct {
	ID    primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Name  string             `bson:"species,omitempty" json:"species"`
	Image string             `bson:"image,omitempty" json:"image"`
	Price float32            `bson:"price,omitempty" json:"price"`
}

type CareRules struct {
	ID                primitive.ObjectID    `bson:"_id,omitempty" json:"id"`
	Species           string                `bson:"species" json:"species"`
	Description       []CareDescriptionPart `bson:"description" json:"description"`
	CreatedAt         time.Time             `bson:"created_at" json:"created_at"`
	UpdatedAt         time.Time             `bson:"updated_at" json:"updated_at"`
	Image             string                `bson:"image" json:"image"`
	Type              string                `bson:"type" json:"type"`
	LightCondition    string                `bson:"light_condition" json:"light_condition"`
	TemperatureRegime string                `bson:"temperature_regime" json:"temperature_regime"`
}

type CareDescriptionPart struct {
	UserID              primitive.ObjectID `bson:"user_id" json:"user_id"`
	DescriptionAddition string             `bson:"description_addition" json:"description_addition"`
	CreatedAt           time.Time          `bson:"created_at" json:"created_at"`
	UserName            string             `bson:"user_name" json:"user_name"`
	UserSurname         string             `bson:"user_surname" json:"user_surname"`
	UserFatherName      string             `bson:"user_father_name" json:"user_father_name"`
}

type Filter struct {
	Page   int64
	Size   int64
	SortBy string
	IsDesc bool
	Labels map[string]interface{}
}

type PlantsStats struct {
	ID    primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Count int64              `bson:"count" json:"count"`
	Info  []InnerPlantsStats `bson:"info" json:"info"`
}

type TradeStats struct {
	ID    primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Count int64              `bson:"count" json:"count"`
	Info  []InnerTradeStats  `bson:"info" json:"info"`
}

type BuyStats struct {
	ID    primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Count int64              `bson:"count" json:"count"`
	Info  []InnerBuyStats    `bson:"info" json:"info"`
}

type AdsStats struct {
	ID    primitive.ObjectID `bson:"_id,omitempty" json:"id"`
	Count int64              `bson:"count" json:"count"`
	Info  []InnerAdsStats    `bson:"info" json:"info"`
}

type InnerPlantsStats struct {
	Species string `bson:"species" json:"species"`
	Count   int64  `bson:"count" json:"count"`
}

type InnerBuyStats struct {
	Date  string `bson:"date" json:"date"`
	Count int64  `bson:"count" json:"count"`
}

type InnerTradeStats struct {
	Date   string `bson:"date" json:"date"`
	Status int8   `bson:"status" json:"status"`
	Count  int64  `bson:"count" json:"count"`
}

type InnerAdsStats struct {
	Date  string `bson:"date" json:"date"`
	Count int64  `bson:"count" json:"count"`
}
