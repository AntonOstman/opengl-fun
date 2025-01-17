#include <iostream>
#include <vector>
#include <sstream>
#include <fstream>
#include <GLFW/glfw3.h>
#include <glad/glad.h>
#include <stdio.h>

void framebuffer_size_callback(GLFWwindow* window, int width, int height);  
void display();
void init();

// Can be globals for now...
GLuint plainFrag = 0;
GLuint plainVert = 0;
GLuint shaderProgram;
GLuint VBO;


int main() {
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window = glfwCreateWindow(800, 600, "LearnOpenGL", NULL, NULL);
    if (window == NULL) 
    {
        std::cout << "Failed to create window" << std::endl;
        glfwTerminate();
        return -1;
    }
    glfwMakeContextCurrent(window);

    if(!gladLoadGLLoader((GLADloadproc)glfwGetProcAddress))
    {
        std::cout << "Failed to load GLAD" << std::endl;
        return -1;
    }
    glViewport(0, 0, 800, 600);

    glfwSetFramebufferSizeCallback(window, framebuffer_size_callback);  

    init();

    while(!glfwWindowShouldClose(window))
    {
        glfwSwapBuffers(window);
        glfwPollEvents();    
        display();
    }

    printf("Hello World\n");
    glfwTerminate();
    return 0;
}


GLuint loadShaders(const std::string &vertShader, const std::string &fragShader) {
    GLuint program = 0;
    std::vector<std::string> shaders = std::vector<std::string>{vertShader, fragShader};

    for (uint i = 0; i < shaders.size(); i++)
    {
        const std::string name = shaders[i];
        std::ifstream file(name, std::ios::in);

        if (file.is_open())
        {
            std::cout << "Failed to open shader file: " << name << std::endl;
            exit(-1);
        }

        GLuint shader_id = 0;
        if (i == 0)
        {
            shader_id = glCreateShader(GL_VERTEX_SHADER);
        }
        if (i == 1)
        {
            shader_id = glCreateShader(GL_FRAGMENT_SHADER);
        }

        std::stringstream ss;

        ss << file.rdbuf();

        file.close();

        std::string s_file = ss.str();
        const char * raw_file = s_file.c_str();

        glShaderSource(shader_id, 1, &raw_file, NULL);
        glCompileShader(shader_id); 

        int  success;
        char infoLog[512];
        glGetShaderiv(shader_id, GL_COMPILE_STATUS, &success);

        if(!success)
        {
            glGetShaderInfoLog(shader_id, 512, NULL, infoLog);
            std::cout << "ERROR::SHADER::VERTEX::COMPILATION_FAILED\n" << infoLog << std::endl;
        }
        glAttachShader(program, shader_id);
    }
    glLinkProgram(program);

    int  success;
    char infoLog[512];
    glGetProgramiv(shaderProgram, GL_LINK_STATUS, &success);

    if(!success) {
        glGetProgramInfoLog(shaderProgram, 512, NULL, infoLog);
        std::cout << "ERROR::LINK::COMPILATION_FAILED\n" << infoLog << std::endl;
    }

    return program;
}

void init()
{
    printf("%d\n",shaderProgram);
    shaderProgram = loadShaders(std::string{"plain.vert"}, std::string{"plain.frag"});
    shaderProgram = loadShaders(std::string{"plain.vert"}, std::string{"plain.frag"});
    printf("%d\n",shaderProgram);
}

void display() {

    float vertices[] = {
        -0.5f, -0.5f, 0.0f,
         0.5f, -0.5f, 0.0f,
         0.0f,  0.5f, 0.0f
    };  
    
    glGenBuffers(1, &VBO);  
    glBindBuffer(GL_ARRAY_BUFFER, VBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);

}

void framebuffer_size_callback(GLFWwindow* window, int width, int height)
{
    glViewport(0, 0, width, height);
}  
