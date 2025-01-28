package models

type Class struct {
	ClassNumber uint       `gorm:"primaryKey;autoIncrement:false"`
	ClassLetter string     `gorm:"primaryKey;size:2;not null"`
	Students    []Student  `gorm:"foreignKey:ClassNumber,ClassLetter;constraint:OnDelete:CASCADE"`
	Schedules   []Schedule `gorm:"foreignKey:ClassNumber,ClassLetter;constraint:OnDelete:CASCADE"`
}
