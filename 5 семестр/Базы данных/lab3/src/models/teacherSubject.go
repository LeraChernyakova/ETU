package models

type TeacherSubject struct {
	TeacherId uint `gorm:"primaryKey;autoIncrement:false"`
	SubjectId uint `gorm:"primaryKey;autoIncrement:false"`
}
