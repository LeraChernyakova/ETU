package models

type Teacher struct {
	TeacherId         uint               `gorm:"primaryKey;autoIncrement:true"`
	TeacherName       string             `gorm:"size:50;not null"`
	TeacherSurname    string             `gorm:"size:50;not null"`
	TeacherPatronimyc string             `gorm:"size:50;default:null"`
	TeacherSubjects   []TeacherSubject   `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE"`
	TeacherClassroom  []TeacherClassroom `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE"`
	Schedules         []Schedule         `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE"`
}
