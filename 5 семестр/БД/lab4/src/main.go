package main

import (
	"encoding/json"
	"fmt"
	"github.com/brianvoe/gofakeit/v6"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"lab3/models"
	"lab3/requests"
	"math/rand"
	"os"
	"time"
)

const count = 10000

func main() {
	dsn := "host=localhost user=postgres password=LeRa2003 dbname=postgres port=5432"
	db, err := gorm.Open(postgres.Open(dsn), &gorm.Config{})
	if err != nil {
		panic("failed to connect database")
	}

	err = db.AutoMigrate(
		&models.Classroom{},
		&models.Teacher{},
		&models.Subject{},
		&models.TeacherClassroom{},
		&models.TeacherSubjects{},
		&models.Class{},
		&models.Student{},
		&models.Grade{},
		&models.Schedule{},
	)
	if err != nil {
		fmt.Print("Произошла ошибка при миграции схем!")
	}

	classes := make([]models.Class, count)
	classrooms := make([]models.Classroom, count)
	subjects := make([]models.Subject, 0)
	teachers := make([]models.Teacher, 0)
	students := make([]models.Student, 0)
	schedules := make([]models.Schedule, 0)
	teacherClassrooms := make([]models.TeacherClassroom, count)
	teacherSubjects := make([]models.TeacherSubjects, count)

	fileClass, _ := os.Open("data/data10000/classes10000.json")
	fileClassrooms, _ := os.Open("data/data10000/classrooms10000.json")
	fileTeacherSubject, _ := os.Open("data/data10000/teacherSubject10000.json")
	fileTeacherClassroom, _ := os.Open("data/data10000/teacherClassrooms10000.json")

	decoder := json.NewDecoder(fileClass)
	err = decoder.Decode(&classes)
	if err != nil {
		return
	}

	decoder = json.NewDecoder(fileClassrooms)
	err = decoder.Decode(&classrooms)
	if err != nil {
		return
	}

	decoder = json.NewDecoder(fileTeacherSubject)
	err = decoder.Decode(&teacherSubjects)
	if err != nil {
		return
	}

	decoder = json.NewDecoder(fileTeacherClassroom)
	err = decoder.Decode(&teacherClassrooms)
	if err != nil {
		return
	}

	for i := 0; i < count; i++ {

		var subject models.Subject
		err := gofakeit.Struct(&subject)
		if err != nil {
			return
		}
		subjects = append(subjects, subject)

		var teacher models.Teacher
		err = gofakeit.Struct(&teacher)
		if err != nil {
			return
		}
		teachers = append(teachers, teacher)

		var student models.Student
		err = gofakeit.Struct(&student)
		if err != nil {
			return
		}
		randomClass := classes[rand.Intn(count)]
		student.ClassNumber = randomClass.ClassNumber
		student.ClassLetter = randomClass.ClassLetter
		students = append(students, student)

		var schedule models.Schedule
		err = gofakeit.Struct(&schedule)
		if err != nil {
			return
		}
		schedule.ClassNumber = uint(randomClass.ClassNumber)
		schedule.ClassLetter = randomClass.ClassLetter
		randomTeacherSubject := teacherSubjects[rand.Intn(count)]
		schedule.SubjectId = randomTeacherSubject.SubjectId
		schedule.TeacherId = randomTeacherSubject.TeacherId
		schedules = append(schedules, schedule)
	}

	createRecords := func(data interface{}) {
		result := db.Create(data)
		if result.Error != nil {
			fmt.Print("Error during adding tuple")
		}
	}

	createRecords(&classes)
	createRecords(&classrooms)
	createRecords(&subjects)
	createRecords(&teachers)
	createRecords(&teacherClassrooms)
	createRecords(&teacherSubjects)
	createRecords(&students)
	createRecords(&schedules)

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := classes[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := classrooms[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := subjects[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := teachers[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := teacherClassrooms[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 1000 {
		end := i + 1000
		if end > count {
			end = count
		}
		batch := teacherSubjects[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 500 {
		end := i + 500
		if end > count {
			end = count
		}
		batch := students[i:end]
		createRecords(&batch)
	}

	for i := 0; i < count; i += 500 {
		end := i + 500
		if end > count {
			end = count
		}
		batch := schedules[i:end]
		createRecords(&batch)
	}

	startTime := time.Now()

	for _, subject := range requests.GetSubjectByClassDayNumber(
		db, 276, "K", 8, "Monday") {
		fmt.Println(subject.SubjectName)
	}

	for _, teacher := range requests.GetClassTeachers(db, 276, "K") {
		fmt.Println(teacher.TeacherName, teacher.TeacherSurname, teacher.TeacherPatronimyc)
	}

	for _, schedule := range requests.GetClassroom(db, 5, "Wednesday", 871, "H") {
		fmt.Println(schedule.ClassroomNumber)
	}

	for _, schedule := range requests.GetTeacherClasses(
		db, "Darby", "McCullough", "Mathematics") {
		fmt.Println(schedule.ClassNumber, schedule.ClassLetter)
	}

	for _, data := range requests.GetSchedule(db, 8614, "D", "Monday") {
		fmt.Println(
			data.LessonNumber,
			data.SubjectName,
			data.TeacherName,
			data.TeacherSurname,
			data.TeacherPatronimyc)
	}

	fmt.Println(requests.GetStudentsInClass(db, 276, "K"))

	endTime := time.Now()

	elapsedTime := endTime.Sub(startTime)
	fmt.Printf("Прошло времени: %v\n", elapsedTime)
}
