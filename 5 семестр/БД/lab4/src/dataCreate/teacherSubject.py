import json
import random


def generate_combinations(count):
    create_combinations = set()

    while len(create_combinations) < count:
        teacher_id = random.randint(1, 1000000)
        subject_id = random.randint(1, 1000000)
        combination = {"TeacherId": teacher_id, "SubjectId": subject_id}
        create_combinations.add(json.dumps(combination))

    return list(create_combinations)


combinations = generate_combinations(1000000)

json_data = [json.loads(combination) for combination in combinations]

with open('teacherSubject1000000.json', 'w') as json_file:
    json.dump(json_data, json_file, indent=2)
