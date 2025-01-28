package models

type Classroom struct {
	ClassroomNumber  uint               `gorm:"primaryKey;autoIncrement:false"`
	TeacherClassroom []TeacherClassroom `gorm:"foreignKey:ClassroomNumber;constraint:OnDelete:CASCADE"`
	Schedules        []Schedule         `gorm:"foreignKey:ClassroomNumber;constraint:OnDelete:CASCADE"`
}
