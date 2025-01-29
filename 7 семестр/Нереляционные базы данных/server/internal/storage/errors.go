package storage

import "errors"

// User errors
var (
	ErrUserInvalidId   = errors.New("invalid id")
	ErrUserNotFound    = errors.New("user not found")
	ErrPlantNotFound   = errors.New("plant not found")
	ErrUserNotUpdated  = errors.New("user not updated")
	ErrTradeNotUpdated = errors.New("trade not updated")
	ErrPlantNotUpdated = errors.New("plant not updated")
	ErrTradeNotFound   = errors.New("trade not found")
	ErrDB              = errors.New("error while importing/exporting database")
)
