package models

type Subject struct {
	SubjectId       uint             `gorm:"primaryKey;autoIncrement:true"`
	SubjectName     string           `gorm:"size:50;not null"`
	TeacherSubjects []TeacherSubject `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE"`
	Grades          []Grade          `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE"`
	Schedules       []Schedule       `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE"`
}
