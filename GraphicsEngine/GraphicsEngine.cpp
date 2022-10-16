#include <gl/glew.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <fstream>

GLuint vao;

GLuint shaderProgram;

void init() {
    const float positions[] = {
        0.0f, 0.5f, 1.0f,
        -0.5f, -0.5f, 1.0f,
        0.5f, -0.5f, 1.0f
    };
    GLuint positionBuffer;
    glGenBuffers(1, &positionBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(positions), positions, GL_STATIC_DRAW);

    const float color[] = { 0.0f, 0.5f, 1.0f,
                            0.5f, 1.0f, 0.0f,
                            1.0f, 1.0f, 0.0f};
    GLuint colorBuffer;
    glGenBuffers(1, &colorBuffer);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glBufferData(GL_ARRAY_BUFFER, sizeof(color), color, GL_STATIC_DRAW);

    glGenVertexArrays(1, &vao);
    glBindVertexArray(vao);
    glBindBuffer(GL_ARRAY_BUFFER, positionBuffer);
    glVertexAttribPointer(0, 3, GL_FLOAT, false, 0, 0);
    glBindBuffer(GL_ARRAY_BUFFER, colorBuffer);
    glVertexAttribPointer(1, 3, GL_FLOAT, false, 0, 0);
    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    
    std::ifstream vs_file("shader.vert");
    std::string vs_src((std::istreambuf_iterator<char>(vs_file)), std::istreambuf_iterator<char>());
    std::ifstream fs_file("shader.frag");
    std::string fs_src((std::istreambuf_iterator<char>(fs_file)), std::istreambuf_iterator<char>());

    const char* vs = vs_src.c_str();
    const char* fs = fs_src.c_str();

    glShaderSource(vertexShader, 1, &vs, NULL);
    glShaderSource(fragmentShader, 1, &fs, NULL);

    glCompileShader(vertexShader);
    glCompileShader(fragmentShader);

    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    glLinkProgram(shaderProgram);
}

void display(void) {
    /* Render here */
    glClear(GL_COLOR_BUFFER_BIT);
    glClear(GL_BUFFER);
    
    glUseProgram(shaderProgram);

    glBindVertexArray(vao);

    glDrawArrays(GL_TRIANGLES, 0, 3);

    //glEnd();
}

int main(void)
{
    GLFWwindow* window;

    

    /* Initialize the library */
    if (!glfwInit())
        return -1;

    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(640, 480, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);
    
    if (glewInit()) {
        return 0;
    }

    init();


    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        display();

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    glfwTerminate();
    return 0;
}