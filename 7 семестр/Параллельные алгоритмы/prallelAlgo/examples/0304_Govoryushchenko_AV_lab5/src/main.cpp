#include <GL/glew.h>
#define GLFW_INCLUDE_NONE
#include <GLFW/glfw3.h>
#include <cstdlib>
#include <iostream>
#include <memory>
#include <chrono>

#include <mandelbrot.h>
 
constexpr float verts[4][2] =
{
    { -1.0f, -1.0f },
    {  1.0f, -1.0f },
    { -1.0f,  1.0f },
    {  1.0f,  1.0f }
};

const char *vertexShader = R"(
#version 330 core
in vec2 pos;
out vec2 texCoord;
void main()
{
     gl_Position = vec4( pos, 0.0, 1.0 );
     texCoord = pos * 0.5 + 0.5;
}
)";

const char *fragmentShader = R"(
#version 330 core
in vec2 texCoord;
uniform sampler2D image;
void main()
{
     gl_FragColor = texture2D( image, texCoord );
}
)";

bool str_to_size(const std::string& str, std::size_t& num)
{
    try
    {
        num = std::stoul(str);
    }
    catch (...)
    {
        return false;
    }
    return true;
}
 
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (key == GLFW_KEY_ESCAPE && action == GLFW_PRESS)
        glfwSetWindowShouldClose(window, GLFW_TRUE);
}

size_t align(size_t x, size_t bound) {
    return (x + bound - 1) / bound * bound;
}

int main(int argc, char *argv[])
{
    GLFWwindow* window;
    GLuint texture, shader, vao, vbo;
    size_t width, height, maxIters;
 
    if (argc != 5 || !str_to_size(argv[2], width)
        || !str_to_size(argv[3], height) || !str_to_size(argv[4], maxIters))
    {
        std::cout << "Usage: " << argv[0] << " [cpu|opencl] <width> <height> <maxIters>\n";
        return EXIT_FAILURE;
    }
    const std::string compType = argv[1];
    size_t image_width = align(width, workgroupSize[0]);
    size_t image_height = align(height, workgroupSize[1]);
    auto buffer = std::make_unique<char[]>(image_width * image_height * channels);
    auto t1 = std::chrono::high_resolution_clock::now();
    if (compType == "opencl") {
        mandelbrotOpencl(buffer.get(), image_width, image_height, maxIters);
    } else if (compType == "cpu") {
        mandelbrotCpu(buffer.get(), image_width, image_height, maxIters);
    } else {
        std::cout << "Usage: " << argv[0] << " [cpu|opencl] <width> <height> <maxIters>\n";
        return EXIT_FAILURE;
    }

    if (!glfwInit()) {
        return EXIT_FAILURE;
    }
    auto t2 = std::chrono::high_resolution_clock::now();
    std::cout << "Time elapsed: "
        << std::chrono::duration< double, std::milli >( t2 - t1 ).count()
        << " ms\n";
 
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
 
    window = glfwCreateWindow(width, height, "Mandelbrot set", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return EXIT_FAILURE;
    }
 
    glfwSetKeyCallback(window, key_callback);
 
    glfwMakeContextCurrent(window);

    if (glewInit() != GLEW_OK || !GLEW_VERSION_3_3) {
        return EXIT_FAILURE;
    }
    glfwSwapInterval(1);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    shader = glCreateProgram();

    GLuint handle = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(handle, 1, &vertexShader, 0);
    glCompileShader(handle);
    glAttachShader(shader, handle);
    glDeleteShader(handle);

    handle = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(handle, 1, &fragmentShader, 0);
    glCompileShader(handle);
    glAttachShader(shader, handle);
    glDeleteShader(handle);

    glLinkProgram(shader);
    glValidateProgram(shader);
    glUseProgram(shader);

    glGenBuffers(1, &vbo);
    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, sizeof(verts), &verts[ 0 ][ 0 ], GL_STATIC_DRAW);

    glEnableVertexAttribArray(0);
    glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, sizeof(float) * 2, 0);
 
    glGenTextures(1, &texture);
    glBindTexture(GL_TEXTURE_2D, texture);
    glPixelStorei(GL_UNPACK_ALIGNMENT, 1);
    glTexImage2D(GL_TEXTURE_2D, 0, GL_RGB, image_width, image_height,
        0, GL_RGB, GL_UNSIGNED_BYTE, buffer.get());
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glActiveTexture(GL_TEXTURE0);
    glUniform1i(glGetUniformLocation(shader, "image"), 0);
 
    glDrawArrays(GL_TRIANGLE_STRIP, 0, 4);
    glfwSwapBuffers(window);
    while (!glfwWindowShouldClose(window))
    {
        glfwPollEvents();
    }

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);
    glUseProgram(0);
    glDeleteBuffers(1, &vbo);
    glDeleteProgram(shader);
    glDeleteTextures(1, &texture);
    glDeleteVertexArrays(1, &vao);
    glfwDestroyWindow(window);
 
    glfwTerminate();
    exit(EXIT_SUCCESS);
}