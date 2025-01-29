# Минимальная версия CMake
cmake_minimum_required(VERSION 3.10)

# Название проекта
project(MatrixApp LANGUAGES CXX)

# Установка стандарта C++
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED True)

# Установка флагов компилятора
set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -g3 -pthread")

# Общие исходные файлы
set(COMMON_SOURCES matrix.cpp)

# Основной исполняемый файл
add_executable(main main.cpp ${COMMON_SOURCES})

# Настройка очистки
set_directory_properties(PROPERTIES CLEAN_NO_CUSTOM True)

# Команда custom_clean (замена `clean`)
add_custom_target(clean_custom
        COMMAND ${CMAKE_COMMAND} -E rm -f $<TARGET_FILE:main>
        COMMAND ${CMAKE_COMMAND} -E rm -f *.o
        COMMENT "Custom cleaning up..."
)
