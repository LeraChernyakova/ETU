package models

type Student struct {
	StudentId      uint    `gorm:"primaryKey;autoIncrement:true;index" fake:"skip"`
	StudentName    string  `gorm:"size:50;not null" fake:"{firstname}"`
	StudentSurname string  `gorm:"size:50;not null" fake:"{lastname}"`
	ClassNumber    int     `gorm:"not null;index" fake:"skip"`
	ClassLetter    string  `gorm:"size:2;not null;index" fake:"skip"`
	Grades         []Grade `gorm:"foreignKey:StudentId;constraint:OnDelete:CASCADE" fakesize:"1"`
}
