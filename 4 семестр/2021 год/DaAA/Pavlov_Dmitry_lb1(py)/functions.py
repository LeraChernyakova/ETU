from random import randint


def get_sq(side):
    return [[0 for j in range(side)] for i in range(side)]


def set_sq(x, y, w, map, el):
    for line_id in range(len(map)):
        line = map[line_id]
        if line_id < y:
            continue
        if line_id - y > w - 1:
            break
        for sym_id in range(len(line)):
            if sym_id < x:
                continue
            if sym_id - x > w - 1:
                break
            line[sym_id] = el
    return map


def check_sq(x, y, cur, map):
    if (x + cur > len(map)) or (y + cur > len(map)):
        return False
    for i in range(x, x + cur):
        for j in range(y, y + cur):
            if map[j][i] != 0:
                return False
    return True


def find_sq(map):
    sq = 0
    for line in map:
        for s in line:
            if s == 0:
                sq += 1

    return sq


def set_for_prime(map, points):
    side = len(map)
    set_sq(0, 0, (int(side / 2) + 1), map, 1)
    set_sq(int(side / 2) + side % 2, 0, int(side / 2), map, 2)
    set_sq(0, int(side / 2) + side % 2, int(side / 2), map, 3)
    set_sq(int(side / 2) + side % 2, int(side / 2) + side % 2 - 1, 1, map, 4)
    points.append([0, 0, (int(side / 2) + 1)])
    points.append([int(side / 2) + side % 2, 0, int(side / 2)])
    points.append([0, int(side / 2) + side % 2, int(side / 2)])
    points.append([int(side / 2) + side % 2, int(side / 2) + side % 2 - 1, 1])
    return map


def print_points(points):
    # print(points)
    for point in points:
        print(point[0], point[1], point[2])


def find_possible(map, cur):
    var = []
    for i in range(len(map)):
        for j in range(len(map[i])):
            if map[j][i] == 0:
                if check_sq(i, j, cur, map):
                    var.append([i, j, cur])

    return var


def code_map(map):
    res = []
    for line in map:
        cline = []
        for sym in line:
            cline.append(sym + 1)
        res.append(cline)

    return res


def decode_map(map):
    res = []
    for line in map:
        cline = []
        for sym in line:
            cline.append(sym - 1)
        res.append(cline)

    return res


def process(side):
    points = []
    map = set_for_prime(get_sq(side), points)
    cur = round(0.2684 * side + 0.3398)
    save = code_map(map)
    op = 0
    bestc = round(0.0012 * side ** 3 - 0.0571 * side ** 2 + 1.1161 * side + 3.7250) + 1
    bestm = []
    bestp = []
    svcur = cur + 1
    svpoints = code_map(points)

    while op < 1:
        map = decode_map(save)
        points = decode_map(svpoints)
        count = 4
        cur = svcur - 1
        rest = False
        while find_sq(map) > 0:
            if count > bestc:
                rest = True
                break
            opt = find_possible(map, cur)
            while len(opt) == 0:
                cur -= 1
                opt = find_possible(map, cur)
            if len(opt) == 1:
                opt = opt[0]
            else:
                opt = opt[randint(0, (len(opt) - 1))]
            count += 1
            map = set_sq(opt[0], opt[1], cur, map, count)
            points.append([opt[0], opt[1], cur])
        if rest:
            continue
        if count < bestc:
            bestc = count
            bestm = map
            bestp = points
            break

    return [bestc, bestm, bestp]
