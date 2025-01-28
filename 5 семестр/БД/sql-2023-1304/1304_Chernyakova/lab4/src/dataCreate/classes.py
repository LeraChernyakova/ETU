import json
import random
import string


def generate_unique_combinations(count):
    unique_combinations = set()

    while len(unique_combinations) < count:
        number = random.randint(1, 1000000)
        letter = random.choice(string.ascii_uppercase)
        combination = {"ClassNumber": number, "ClassLetter": letter}
        unique_combinations.add(json.dumps(combination))

    return list(unique_combinations)


combinations = generate_unique_combinations(1000000)

json_data = [json.loads(combination) for combination in combinations]

with open('classes1000000.json', 'w') as json_file:
    json.dump(json_data, json_file, indent=2)
