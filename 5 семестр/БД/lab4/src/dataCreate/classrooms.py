import json


def generate_classroom_numbers(count):
    return list(range(1, count + 1))


classroom_numbers = generate_classroom_numbers(1000000)

json_data = [{"ClassroomNumber": number} for number in classroom_numbers]

with open('classrooms1000000.json', 'w') as json_file:
    json.dump(json_data, json_file, indent=2)
