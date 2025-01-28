package main

import (
	"fmt"
	"gorm.io/driver/postgres"
	"gorm.io/gorm"
	"lab3/models"
	"lab3/requests"
)

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
		&models.TeacherSubject{},
		&models.Class{},
		&models.Student{},
		&models.Grade{},
		&models.Schedule{},
	)
	if err != nil {
		fmt.Print("Произошла ошибка при миграции схем!")
	}

	classes := []models.Class{
		{ClassNumber: 5, ClassLetter: "А"},
		{ClassNumber: 5, ClassLetter: "Б"},
		{ClassNumber: 6, ClassLetter: "Б"},
		{ClassNumber: 6, ClassLetter: "Г"},
		{ClassNumber: 7, ClassLetter: "В"},
		{ClassNumber: 7, ClassLetter: "Д"},
		{ClassNumber: 8, ClassLetter: "А"},
		{ClassNumber: 9, ClassLetter: "А"},
	}

	classrooms := []models.Classroom{
		{ClassroomNumber: 101},
		{ClassroomNumber: 205},
		{ClassroomNumber: 220},
		{ClassroomNumber: 135},
		{ClassroomNumber: 310},
		{ClassroomNumber: 222},
		{ClassroomNumber: 112},
		{ClassroomNumber: 300},
		{ClassroomNumber: 315},
	}

	subjects := []models.Subject{
		{SubjectName: "Математика"},
		{SubjectName: "Русский язык"},
		{SubjectName: "История"},
		{SubjectName: "Физика"},
		{SubjectName: "Биология"},
		{SubjectName: "Химия"},
		{SubjectName: "Иностранный язык"},
		{SubjectName: "Литература"},
		{SubjectName: "География"},
		{SubjectName: "Искусство"},
	}

	teachers := []models.Teacher{
		{TeacherName: "Иванов", TeacherSurname: "Александр", TeacherPatronimyc: "Петрович"},
		{TeacherName: "Смирнова", TeacherSurname: "Мария", TeacherPatronimyc: "Игоревна"},
		{TeacherName: "Петров", TeacherSurname: "Андрей", TeacherPatronimyc: "Сергеевич"},
		{TeacherName: "Козлов", TeacherSurname: "Елена", TeacherPatronimyc: "Владимировна"},
		{TeacherName: "Соколов", TeacherSurname: "Игорь", TeacherPatronimyc: "Анатольевич"},
		{TeacherName: "Волкова", TeacherSurname: "Наталья", TeacherPatronimyc: "Александровна"},
		{TeacherName: "Михайлов", TeacherSurname: "Артем", TeacherPatronimyc: "Дмитриевич"},
		{TeacherName: "Передерий", TeacherSurname: "Ольга"},
	}

	grades := []models.Grade{
		{StudentId: 1, QuaterNumber: 1, SubjectId: 2, Mark: 4},
		{StudentId: 2, QuaterNumber: 1, SubjectId: 10, Mark: 5},
		{StudentId: 3, QuaterNumber: 1, SubjectId: 5, Mark: 3},
		{StudentId: 4, QuaterNumber: 1, SubjectId: 3, Mark: 3},
		{StudentId: 5, QuaterNumber: 1, SubjectId: 1, Mark: 4},
		{StudentId: 6, QuaterNumber: 1, SubjectId: 9, Mark: 4},
		{StudentId: 7, QuaterNumber: 1, SubjectId: 6, Mark: 5},
		{StudentId: 8, QuaterNumber: 1, SubjectId: 4, Mark: 5},
		{StudentId: 9, QuaterNumber: 1, SubjectId: 7, Mark: 5},
		{StudentId: 10, QuaterNumber: 1, SubjectId: 8, Mark: 3},
	}

	schedules := []models.Schedule{
		{DayName: "Понедельник", LessonNumber: 1, SubjectId: 2, TeacherId: 1,
			ClassroomNumber: 310, ClassNumber: 5, ClassLetter: "А"},
		{DayName: "Понедельник", LessonNumber: 2, SubjectId: 1, TeacherId: 5,
			ClassroomNumber: 220, ClassNumber: 5, ClassLetter: "А"},
		{DayName: "Понедельник", LessonNumber: 3, SubjectId: 3, TeacherId: 3,
			ClassroomNumber: 112, ClassNumber: 5, ClassLetter: "Б"},
		{DayName: "Понедельник", LessonNumber: 4, SubjectId: 5, TeacherId: 4,
			ClassroomNumber: 220, ClassNumber: 5, ClassLetter: "Б"},
		{DayName: "Вторник", LessonNumber: 1, SubjectId: 7, TeacherId: 7,
			ClassroomNumber: 101, ClassNumber: 6, ClassLetter: "Б"},
		{DayName: "Вторник", LessonNumber: 2, SubjectId: 1, TeacherId: 2,
			ClassroomNumber: 205, ClassNumber: 6, ClassLetter: "Б"},
		{DayName: "Вторник", LessonNumber: 5, SubjectId: 9, TeacherId: 8,
			ClassroomNumber: 135, ClassNumber: 6, ClassLetter: "Г"},
		{DayName: "Вторник", LessonNumber: 6, SubjectId: 8, TeacherId: 1,
			ClassroomNumber: 310, ClassNumber: 6, ClassLetter: "Г"},
		{DayName: "Среда", LessonNumber: 5, SubjectId: 4, TeacherId: 1,
			ClassroomNumber: 310, ClassNumber: 7, ClassLetter: "В"},
		{DayName: "Среда", LessonNumber: 6, SubjectId: 10, TeacherId: 6,
			ClassroomNumber: 300, ClassNumber: 7, ClassLetter: "В"},
		{DayName: "Среда", LessonNumber: 3, SubjectId: 2, TeacherId: 1,
			ClassroomNumber: 310, ClassNumber: 7, ClassLetter: "Д"},
		{DayName: "Среда", LessonNumber: 4, SubjectId: 5, TeacherId: 4,
			ClassroomNumber: 315, ClassNumber: 7, ClassLetter: "Д"},
		{DayName: "Четверг", LessonNumber: 1, SubjectId: 6, TeacherId: 4,
			ClassroomNumber: 135, ClassNumber: 8, ClassLetter: "А"},
		{DayName: "Четверг", LessonNumber: 2, SubjectId: 3, TeacherId: 3,
			ClassroomNumber: 112, ClassNumber: 8, ClassLetter: "А"},
		{DayName: "Пятница", LessonNumber: 1, SubjectId: 9, TeacherId: 8,
			ClassroomNumber: 135, ClassNumber: 9, ClassLetter: "А"},
		{DayName: "Пятница", LessonNumber: 2, SubjectId: 4, TeacherId: 1,
			ClassroomNumber: 310, ClassNumber: 9, ClassLetter: "А"},
	}

	students := []models.Student{
		{StudentName: "Басалаев", StudentSurname: "Леонид", ClassNumber: 5, ClassLetter: "А"},
		{StudentName: "Кудашкина", StudentSurname: "Анастасия", ClassNumber: 5, ClassLetter: "А"},
		{StudentName: "Карасев", StudentSurname: "Алексей", ClassNumber: 5, ClassLetter: "Б"},
		{StudentName: "Максимлчкина", StudentSurname: "Софья", ClassNumber: 5, ClassLetter: "Б"},
		{StudentName: "Мангутов", StudentSurname: "Тимур", ClassNumber: 6, ClassLetter: "Б"},
		{StudentName: "Аракчеева", StudentSurname: "Арина", ClassNumber: 6, ClassLetter: "Г"},
		{StudentName: "Чернякова", StudentSurname: "Валерия", ClassNumber: 7, ClassLetter: "В"},
		{StudentName: "Дубровин", StudentSurname: "Игорь", ClassNumber: 7, ClassLetter: "Д"},
		{StudentName: "Никитин", StudentSurname: "Никита", ClassNumber: 8, ClassLetter: "А"},
		{StudentName: "Бомштейн", StudentSurname: "Юлия", ClassNumber: 9, ClassLetter: "А"},
	}

	teachersClassrooms := []models.TeacherClassroom{
		{TeacherId: 7, ClassroomNumber: 101},
		{TeacherId: 2, ClassroomNumber: 205},
		{TeacherId: 5, ClassroomNumber: 220},
		{TeacherId: 8, ClassroomNumber: 135},
		{TeacherId: 1, ClassroomNumber: 310},
		{TeacherId: 3, ClassroomNumber: 112},
		{TeacherId: 6, ClassroomNumber: 300},
	}

	teachersSubjects := []models.TeacherSubject{
		{TeacherId: 2, SubjectId: 1},
		{TeacherId: 5, SubjectId: 1},
		{TeacherId: 7, SubjectId: 2},
		{TeacherId: 1, SubjectId: 2},
		{TeacherId: 3, SubjectId: 3},
		{TeacherId: 1, SubjectId: 4},
		{TeacherId: 4, SubjectId: 5},
		{TeacherId: 4, SubjectId: 6},
		{TeacherId: 7, SubjectId: 7},
		{TeacherId: 1, SubjectId: 8},
		{TeacherId: 8, SubjectId: 9},
		{TeacherId: 6, SubjectId: 10},
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
	createRecords(&students)
	createRecords(&grades)
	createRecords(&schedules)
	createRecords(&teachersClassrooms)
	createRecords(&teachersSubjects)

	fmt.Println("Какой предмет будет в заданном классе, в заданный день недели на заданном уроке?")
	for _, subject := range requests.GetSubjectByClassDayNumber(
		db, 9, "А", 2, "Пятница") {
		fmt.Println(subject.SubjectName)
	}

	fmt.Println("Кто из учителей преподает в заданном классе?")
	for _, teacher := range requests.GetClassTeachers(db, 5, "А") {
		fmt.Println(teacher.TeacherName, teacher.TeacherSurname, teacher.TeacherPatronimyc)
	}

	fmt.Println("В каком кабинете будет 5-й урок в среду у некоторого класса?")
	for _, schedule := range requests.GetClassroom(db, 5, "Среда", 7, "В") {
		fmt.Println(schedule.ClassroomNumber)
	}

	fmt.Println("В каких классах преподает заданный предмет заданный учитель?")
	for _, schedule := range requests.GetTeacherClasses(
		db, "Козлов", "Елена", "Владимировна", "Биология") {
		fmt.Println(schedule.ClassNumber, schedule.ClassLetter)
	}

	fmt.Println("Расписание на заданный день недели для указанного класса?")
	for _, data := range requests.GetSchedule(db, 6, "Б", "Вторник") {
		fmt.Println(
			data.LessonNumber,
			data.SubjectName,
			data.TeacherName,
			data.TeacherSurname,
			data.TeacherPatronimyc)
	}

	fmt.Println("Сколько учеников в указанном классе?")
	fmt.Println(requests.GetStudentsInClass(db, 5, "А"))
}
