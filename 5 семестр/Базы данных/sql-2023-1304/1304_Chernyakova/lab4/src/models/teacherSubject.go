package models

type TeacherSubjects struct {
	TeacherId uint `gorm:"primaryKey;autoIncrement:false"`
	SubjectId uint `gorm:"primaryKey;autoIncrement:false"`
}
