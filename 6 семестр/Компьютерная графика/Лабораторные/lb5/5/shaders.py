from OpenGL import GL as gl


# Загрузка файла шейдера
def readShader(file):
    return open(file, 'r').read()


# Создание шейдера из файла
def createShader(shader_type, file):
    shader = gl.glCreateShader(shader_type)
    gl.glShaderSource(shader, readShader(file))
    gl.glCompileShader(shader)
    return shader


# Компиляция шейдерной программы
def createWaveProgram():
    vertex = createShader(gl.GL_VERTEX_SHADER, './wave.vert')
    fragment = createShader(gl.GL_FRAGMENT_SHADER, './wave.frag')
    waveProgram = gl.glCreateProgram()
    gl.glAttachShader(waveProgram, vertex)
    gl.glAttachShader(waveProgram, fragment)
    gl.glLinkProgram(waveProgram)
    return waveProgram
