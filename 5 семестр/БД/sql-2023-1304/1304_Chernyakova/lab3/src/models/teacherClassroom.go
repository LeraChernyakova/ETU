package models

type TeacherClassroom struct {
	TeacherId       uint `gorm:"primaryKey;autoIncrement:false"`
	ClassroomNumber uint `gorm:"primaryKey;autoIncrement:false"`
}
