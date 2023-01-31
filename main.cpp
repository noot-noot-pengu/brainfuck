//#include <glad/glad.h>
//#include <GLFW/glfw3.h>


//int main(){
//    glfwInit();
//    GLFWwindow* w = glfwCreateWindow(600,600, "this", NULL, NULL);
//    glfwMakeContextCurrent(w);
//    gladLoadGLLoader((GLADloadproc)glfwGetProcAddress);
//    float t[] = 
//    {
//        -0.5f, -0.5f, 0.f,
//        0.f, 0.5f, 0.f,
//        0.5f, -0.5f, 0.f
//    };
//    uint32_t v;
//    glGenBuffers(1, &v);
//    glBindBuffer(GL_ARRAY_BUFFER, v);
//    glBufferData(GL_ARRAY_BUFFER, sizeof(t)*sizeof(t)/sizeof(t[0]), &t[0], GL_STATIC_DRAW);
//    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, sizeof(float)*3, (void*)0);
//    glEnableVertexAttribArray(0);
//    glViewport(0, 0, 600, 600);
//    while(!glfwWindowShouldClose(w)){
//        glClear(GL_COLOR_BUFFER_BIT);
//        glDrawArrays(GL_TRIANGLES, 0, 3);
//        glfwSwapBuffers(w);
//        glfwPollEvents();
//    }
//




#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>


// Vertex Shader source code
const char* vertexShaderSource = "#version 330 core\n"
"layout (location = 0) in vec3 aPos;\n"
"void main()\n"
"{\n"
"   gl_Position = vec4(aPos.x, aPos.y, aPos.z, 1.0);\n"
"}\0";
//Fragment Shader source code
const char* fragmentShaderSource = "#version 330 core\n"
"out vec4 FragColor;\n"
"void main()\n"
"{\n"
"   FragColor = vec4(0.8f, 0.3f, 0.02f, 1.0f);\n"
"}\n\0";




int main(){
    glfwInit();

    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLfloat vertices[] = {
        -0.5f, -0.5f * float(1.73205080757) / 3, 0.0f,
        0.5f, -0.5f * float(1.73205080757) / 3, 0.0f,
        0.0f, 0.5f * float(1.73205080757) * 2 / 3, 0.0f
    };

    GLFWwindow* window = glfwCreateWindow(600,600, "start", NULL, NULL);
    if (window == NULL){
        std::cout << "failure" << std::endl;
        glfwTerminate();
        return 1;
    }

    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0, 0, 600, 600);

    GLuint vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vertexShaderSource, NULL);
    glCompileShader(vertexShader);

    GLuint fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fragmentShaderSource, NULL);
    glCompileShader(fragmentShader);

    GLuint shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);

    glLinkProgram(shaderProgram);
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);

    GLuint VAO, VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);

    glBindVertexArray(VAO);

    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

    glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3*sizeof(float), (void*)0) ;
    glEnableVertexAttribArray(0);

    glBindBuffer(GL_ARRAY_BUFFER, 0);
    glBindVertexArray(0);



    glClearColor(0.07f, 0.13f, 0.17, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    glfwSwapBuffers(window);


    while(!glfwWindowShouldClose(window)){
        //glfwPollEvents();
        glClearColor(0.07f, 0.13f, 0.17, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0, 3);
        glfwSwapBuffers(window);
    }
    glDeleteVertexArrays(1, &VAO);
    glDeleteBuffers(1, &VBO);
    glDeleteProgram(shaderProgram);

    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}