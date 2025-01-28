package models

type Student struct {
	StudentId      uint    `gorm:"primaryKey;autoIncrement:true"`
	StudentName    string  `gorm:"size:50;not null"`
	StudentSurname string  `gorm:"size:50;not null"`
	ClassNumber    int     `gorm:"not null"`
	ClassLetter    string  `gorm:"size:2;not null"`
	Grades         []Grade `gorm:"foreignKey:StudentId;constraint:OnDelete:CASCADE"`
}
