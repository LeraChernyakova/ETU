package models

type Teacher struct {
	TeacherId         uint               `gorm:"primaryKey;autoIncrement:true;index" fake:"skip"`
	TeacherName       string             `gorm:"size:50;not null;index" fake:"{firstname}"`
	TeacherSurname    string             `gorm:"size:50;not null;index" fake:"{lastname}"`
	TeacherPatronimyc string             `gorm:"size:50;default:null" fake:"skip"`
	TeacherSubjects   []TeacherSubjects  `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE" fake:"skip"`
	TeacherClassroom  []TeacherClassroom `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE" fake:"skip"`
	Schedules         []Schedule         `gorm:"foreignKey:TeacherId;constraint:OnDelete:CASCADE" fake:"skip"`
}
