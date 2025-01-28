package models

type Grade struct {
	GradeId      uint `gorm:"primaryKey;autoIncrement:true"`
	StudentId    uint `gorm:"not null"`
	QuaterNumber uint `gorm:"not null"`
	SubjectId    uint `gorm:"not null"`
	Mark         uint `gorm:"not null"`
}
