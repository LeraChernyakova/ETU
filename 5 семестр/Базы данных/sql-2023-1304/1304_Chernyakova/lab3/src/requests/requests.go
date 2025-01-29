package requests

import (
	"gorm.io/gorm"
	"lab3/models"
)

func GetSubjectByClassDayNumber(
	db *gorm.DB,
	classNumber int,
	classLetter string,
	lessonNumber int,
	dayName string) (result []models.Subject) {
	db.
		Joins(
			"INNER JOIN schedules ON schedules.subject_id = subjects.subject_id",
		).
		Where(
			"class_number = ? AND class_letter = ? AND day_name = ? AND lesson_number = ?",
			classNumber, classLetter, dayName, lessonNumber,
		).
		Find(&result)
	return
}

func GetClassTeachers(db *gorm.DB, classNumber int, classLetter string) (result []models.Teacher) {
	db.
		Joins(
			"INNER JOIN schedules ON schedules.teacher_id = teachers.teacher_id",
		).
		Where(
			"class_number = ? AND class_letter = ?",
			classNumber, classLetter,
		).
		Find(&result)
	return
}

func GetClassroom(
	db *gorm.DB,
	lessonNumber int,
	dayName string,
	classNumber int,
	ClassLetter string) (result []models.Schedule) {
	db.
		Where(
			"lesson_number = ? AND day_name = ? AND class_number = ? AND class_letter = ?",
			lessonNumber, dayName, classNumber, ClassLetter,
		).
		Find(&result)
	return
}

func GetTeacherClasses(
	db *gorm.DB,
	teacherName string,
	teacherSurname string,
	teacherPatronimyc string,
	subject string) (result []models.Schedule) {
	db.
		Joins(
			"INNER JOIN teachers ON schedules.teacher_id = teachers.teacher_id",
		).
		Joins(
			"INNER JOIN subjects ON schedules.subject_id = subjects.subject_id",
		).
		Where(
			"teacher_name = ? AND teacher_surname = ? AND teacher_patronimyc = ? AND subject_name = ?",
			teacherName, teacherSurname, teacherPatronimyc, subject,
		).
		Find(&result)
	return
}

type Question5 struct {
	LessonNumber      int
	SubjectName       string
	TeacherName       string
	TeacherSurname    string
	TeacherPatronimyc string
}

func GetSchedule(db *gorm.DB, classNumber int, classLetter string, dayName string) (result []Question5) {
	db.
		Table("schedules").
		Select("schedules.lesson_number, subjects.subject_name, teachers.teacher_name, "+
			"teachers.teacher_surname, teachers.teacher_patronimyc").
		Joins(
			"INNER JOIN teachers ON schedules.teacher_id = teachers.teacher_id",
		).
		Joins(
			"INNER JOIN subjects ON schedules.subject_id = subjects.subject_id",
		).
		Where(
			"class_letter = ? AND class_number = ? and day_name = ?",
			classLetter, classNumber, dayName,
		).
		Find(&result)
	return
}

func GetStudentsInClass(db *gorm.DB, classNumber int, classLetter string) (result int64) {
	db.
		Table("students").
		Joins("INNER JOIN classes ON students.class_number = classes.class_number AND "+
			"students.class_letter = classes.class_letter").
		Where("students.class_letter = ? AND students.class_number = ?", classLetter, classNumber).
		Count(&result)
	return
}
