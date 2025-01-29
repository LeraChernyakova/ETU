package models

type Classroom struct {
	ClassroomNumber  int                `gorm:"primaryKey;autoIncrement:false;index"`
	TeacherClassroom []TeacherClassroom `gorm:"foreignKey:ClassroomNumber;constraint:OnDelete:CASCADE" fake:"skip"`
	Schedules        []Schedule         `gorm:"foreignKey:ClassroomNumber;constraint:OnDelete:CASCADE" fake:"skip"`
}
