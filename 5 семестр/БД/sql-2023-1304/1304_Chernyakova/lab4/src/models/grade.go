package models

type Grade struct {
	GradeId      uint `gorm:"primaryKey;autoIncrement:true" fake:"skip"`
	StudentId    uint `gorm:"not null" fake:"{number:1,10000}"`
	QuaterNumber uint `gorm:"not null" fake:"{number:1,4}"`
	SubjectId    uint `gorm:"not null" fake:"{number:1,10000}"`
	Mark         uint `gorm:"not null" fake:"{number:2,5}"`
}
