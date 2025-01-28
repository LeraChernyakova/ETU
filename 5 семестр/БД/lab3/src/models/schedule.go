package models

type Schedule struct {
	ScheduleId      uint   `gorm:"primaryKey;autoIncrement:true"`
	DayName         string `gorm:"size:30;not null"`
	LessonNumber    uint   `gorm:"not null"`
	SubjectId       uint   `gorm:"not null"`
	TeacherId       uint   `gorm:"not null"`
	ClassroomNumber uint   `gorm:"not null"`
	ClassNumber     uint   `gorm:"not null"`
	ClassLetter     string `gorm:"size:2;not null"`
}
