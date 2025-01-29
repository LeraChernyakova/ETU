from subprocess import Popen, PIPE

generated = []
resolved = []
outputed = []

print("Input program name:")
program = input()
print("Input number of starts:")
starts = int(input())
print()

for _ in range(starts):
    process = Popen(["./" + program], stdout=PIPE)
    (output, err) = process.communicate()
    data = output.decode("utf-8").split("\n")[0:-1]
    generated.append(int(data[0].split()[1]))
    resolved.append(int(data[1].split()[1]))
    outputed.append(int(data[2].split()[1]))
    process.wait()


def average(arr):
    return sum(arr) / len(arr)


print("Generated: ", average(generated))
print("Resolved: ", average(resolved))
print("Outputed: ", average(outputed))