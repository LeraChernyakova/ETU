import copy
import numpy as np
from Rectangle import createRectangle


def fractalGenerator(gl):
    if gl.iterations in gl.steps:
        gl.old_rectangles = gl.steps[gl.iterations]
        gl.new_rectangles = []
        return

    for rectangle in gl.old_rectangles:
        x = rectangle['x']
        y = rectangle['y']
        h = rectangle['h']
        w = rectangle['w']
        angle = rectangle['angle']

        gl.new_rectangles.append(createRectangle(
            x - w + 2 * w * 72 / 240,
            y - h + 2 * h * (1 - 55 / 176),
            angle + np.pi / 12,
            h * 67 / 176,
            w * 129 / 240
        ))

        gl.new_rectangles.append(createRectangle(
            x - w + 2 * w * 177 / 240,
            y - h + 2 * h * (1 - 65 / 176),
            angle - np.pi / 8,
            h * 71 / 176,
            w * 102 / 240
        ))

        gl.new_rectangles.append(createRectangle(
            x - w + 2 * w * 117 / 240,
            y - h + 2 * h * (1 - 120 / 176),
            angle,
            h * 117 / 176,
            w * 102 / 240
        ))

    gl.old_rectangles = copy.deepcopy(gl.new_rectangles)
    gl.steps[gl.iterations] = copy.deepcopy(gl.new_rectangles)
    gl.new_rectangles = []
