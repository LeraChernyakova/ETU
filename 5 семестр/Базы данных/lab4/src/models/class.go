package models

type Class struct {
	ClassNumber int         `gorm:"primaryKey;autoIncrement:false;index"`
	ClassLetter string      `gorm:"primaryKey;size:2;not null;index"`
	Students    []*Student  `gorm:"foreignKey:ClassNumber,ClassLetter;constraint:OnDelete:CASCADE"`
	Schedules   []*Schedule `gorm:"foreignKey:ClassNumber,ClassLetter;constraint:OnDelete:CASCADE"`
}
