#include <iostream>
#include "glcommon.h"

#include "drawer.h"
#include "cube.h"
#include "shader.h"

using namespace glm;
using namespace std;


int main() {
    if (!glfwInit()) {
        cerr << "Failed to initialize GLFW" << endl;
    }

    glfwWindowHint(GLFW_SAMPLES, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE); // To make MacOS happy; should not be needed
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    GLFWwindow* window;
    window = glfwCreateWindow( 1024, 768, "Cube Simulation", nullptr, nullptr);
    if( window == nullptr ){
        fprintf(stderr, "Failed to open GLFW window.\n" );
        glfwTerminate();
        return -1;
    }

    glfwMakeContextCurrent(window);
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    // Initialize GLEW
    glewExperimental = true; // Needed for core profile

    if (glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to initialize GLEW\n");
        getchar();
        glfwTerminate();
        return -1;
    }
    glGetError();

    GLuint VertexArrayID;
    glGenVertexArrays(1, &VertexArrayID);
    glBindVertexArray(VertexArrayID);

    Cube cube;
    Drawer drawer;

    glm::mat4 Projection = glm::perspective(glm::radians(45.0f), (float)1024/ (float)768, 0.1f, 100.0f);

    glm::mat4 View = glm::lookAt(
            glm::vec3(0,0,2),
            glm::vec3(0,0.25,0),
            glm::vec3(0,1,0)
    );

    glm::mat4 Model = glm::mat4(1.0f);
    glm::mat4 mvp = Projection * View * Model;
    drawer.shader.setMVP(mvp);
    do{
        // Clear the screen
        glClear(GL_COLOR_BUFFER_BIT);
        drawer.draw(&cube);
        cube.update();
        // Swap buffers
        glfwSwapBuffers(window);
        glfwPollEvents();

    } // Check if the ESC key was pressed or the window was closed
    while( glfwGetKey(window, GLFW_KEY_ESCAPE ) != GLFW_PRESS &&
           glfwWindowShouldClose(window) == 0 );
}
