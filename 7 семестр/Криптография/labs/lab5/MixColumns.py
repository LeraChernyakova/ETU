import numpy as np

# Функция для умножения с использованием правил AES для умножения на 1, 2, 3
def g_mul(a, b):
    if b == 1:        
        return a
    elif b == 2:        
        return ((a << 1) ^ 0x11B) if (a & 0x80) else (a << 1)
    elif b == 3:        
        return g_mul(a, 2) ^ a
    return 0

# Константная матрица для MixColumns
C = np.array([
    [2, 1, 1, 3],    [3, 2, 1, 1],
    [1, 3, 2, 1],    [1, 1, 3, 2],
])

# Исходная матрица состояний
E = np.array([
    [0xD4, 0xBF, 0x5D, 0x30],    [0xE0, 0xB4, 0x52, 0xAE],
    [0xB8, 0x41, 0x11, 0xF1],    [0x1E, 0x27, 0x98, 0xE5],
])

# Умножение на матрицу констант 
nE = []

for i in range(E.shape[0]):    
    col = []
    for j in range(C.shape[1]):        
        p = 0
        for k in range(E.shape[1]):
            p ^= g_mul(E[i][k], C[k][j])        
        col.append(p & 0xFF)  # Обрезаем до 8 бит
    nE.append(np.array(col))
E = np.array(nE).T

# Выводим матрицу состояний в 16-ричном формате
print("Матрица состояний после MixColumns:")
for row in E.T:    
    print(" ".join(f"{val:02X}" for val in row))