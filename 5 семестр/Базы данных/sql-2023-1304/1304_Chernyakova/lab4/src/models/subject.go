package models

type Subject struct {
	SubjectId       uint              `gorm:"primaryKey;autoIncrement:true;index" fake:"skip"`
	SubjectName     string            `gorm:"size:50;not null;index" fake:"{randomstring:[English, Mathematics, Science, History, Geography, Physics, Chemistry, Biology, Art, Music, Literature]}"`
	TeacherSubjects []TeacherSubjects `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE" fake:"skip"`
	Grades          []Grade           `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE" fake:"skip"`
	Schedules       []Schedule        `gorm:"foreignKey:SubjectId;constraint:OnDelete:CASCADE" fake:"skip"`
}
