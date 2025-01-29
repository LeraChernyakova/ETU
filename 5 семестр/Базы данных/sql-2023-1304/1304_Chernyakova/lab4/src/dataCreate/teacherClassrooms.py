import json
import random


def generate_teacher_classroom_combinations(count):
    teacher_ids = list(range(1, count + 1))
    classroom_numbers = list(range(1, count + 1))

    random.shuffle(teacher_ids)
    random.shuffle(classroom_numbers)

    combinations_teacher_classrooms = [{"TeacherId": teacher_id, "ClassroomNumber": classroom_number}
                                       for teacher_id, classroom_number in zip(teacher_ids, classroom_numbers)]

    return combinations_teacher_classrooms


combinations = generate_teacher_classroom_combinations(1000000)

json_data = json.dumps(combinations, indent=2)

with open('teacherClassrooms1000000.json', 'w') as json_file:
    json_file.write(json_data)

