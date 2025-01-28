# from icecream import ic
# from termcolor import colored
from functions import get_sq, set_sq, print_points, process

if __name__ == '__main__':
    side = int(input('Введите сторону N\n'))
    points = []
    map = get_sq(side)
    count = 0
    if side % 2 == 0:
        # print("Make like cur % 2")
        cur = int(side / 2)
        count = 4
        set_sq(0, 0, side / 2, map, 1)
        set_sq(side / 2, 0, side / 2, map, 2)
        set_sq(0, side / 2, side / 2, map, 3)
        set_sq(side / 2, side / 2, side / 2, map, 4)
        print(f"4\n0 0 {cur}\n"
              f"0 {cur} {cur}\n"
              f"{cur} 0 {cur}\n"
              f"{cur} {cur} {cur}")
        exit(0)

    elif side % 3 == 0:
        # print("Make like cur % 3")
        count += 1
        set_sq(0, 0, side / 3 * 2, map, count)
        points.append([0, 0, int((side / 3) * 2)])
        for i in range(side):
            for j in range(side):
                if map[i][j] == 0:
                    count += 1
                    map = set_sq(j, i, int(side / 3), map, count)
                    points.append([j, i, int(side / 3)])
        print(count)
        print_points(points)
        exit(0)
        # print_map(map)
    else:
        res = process(side)
        best = {'count': res[0], 'map': res[1], 'points': res[2]}

    # print_map(best['map'])
    print(best['count'])
    print_points(best['points'])
