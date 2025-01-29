states_needed = set(input().split(","))
N = int(input())
stations = {}
for i in range(N):
    string = input()
    arr = list(string.split(":"))
    stations[int(arr[0])] = set(arr[1].split(','))

final_stations = set()
states_covered = set()
while states_needed:
    best_station = None
    states_covered = set()
    for station, states in stations.items():
        covered = states_needed & states
        if len(covered) > len(states_covered):
            best_station = station
            states_covered = covered
    states_needed -= states_covered
    final_stations.add(best_station)
answer = list(final_stations)
answer.sort()
print(*answer, sep = ',')