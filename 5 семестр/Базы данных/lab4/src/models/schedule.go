package models

type Schedule struct {
	ScheduleId      uint   `gorm:"primaryKey;autoIncrement:true" fake:"skip"`
	DayName         string `gorm:"size:30;not null;index" fake:"{weekday}"`
	LessonNumber    uint   `gorm:"not null;index" fake:"{number:1,8}"`
	SubjectId       uint   `gorm:"not null;index" fake:"skip"`
	TeacherId       uint   `gorm:"not null;index" fake:"skip"`
	ClassroomNumber uint   `gorm:"not null;index" fake:"{number:1,10000}"`
	ClassNumber     uint   `gorm:"not null;index" fake:"skip"`
	ClassLetter     string `gorm:"size:2;not null;index" fake:"skip"`
}
