#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include "renderer.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "texture.h"



int main(void)
{
    GLFWwindow* window;

    /* Initialize the library */
    if (!glfwInit())
        return -1;


    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);


    /* Create a windowed mode window and its OpenGL context */
    window = glfwCreateWindow(1024, 768, "Hello World", NULL, NULL);
    if (!window)
    {
        glfwTerminate();
        return -1;
    }

    /* Make the window's context current */
    glfwMakeContextCurrent(window);



    if (glewInit() != GLEW_OK){
        printf("Error!\n");
    }
    GLCall(const unsigned char *glversion = glGetString(GL_VERSION));
    printf("GL version is |%s|\n", glversion);

    float positions[] = {
        -0.5f, -0.5f, 0.0f, 0.0f, // 0
         0.5f, -0.5f, 1.0f, 0.0f, // 1
         0.5f,  0.5f, 1.0f, 1.0f, // 2
        -0.5f,  0.5f, 0.0f, 1.0f, // 3
    };

    unsigned int indices[] = {
        0, 1, 2,
        2, 3, 0

    };
    GLCall(glEnable(GL_BLEND));
    GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));

    VertexArray va;
    VA_Construct(&va);

    
    VertexBuffer vb;
    VB_Construct(positions, 4 * 4 * sizeof(float), &vb);
    
    VertexBufferLayout vbl;
    VBL_Construct(&vbl);
    VBL_Pushfloat(2, &vbl);
    VBL_Pushfloat(2, &vbl);
    
    VA_AddBuffer(&vb, &vbl, &va);
  

    IndexBuffer ib;
    IB_Construct(indices, 6, &ib);

    Shader shader;
    SH_Construct(&shader,"../res/shaders/Basic.shader");
    SH_Bind(&shader);
    SH_SetUniform4f(&shader, "u_Color", 0.2f, 0.3f, 0.8f, 1.0f);

    Texture texture;
    TX_Construct("../res/textures/C.png", &texture);
    TX_Bind(0, &texture);
    SH_SetUniform1i(&shader, "u_Texture", 0);

    VA_Unbind(&va);
    SH_Unbind();
    VB_Unbind();
    IB_Unbind();


    float r = 0.0f;
    float increment = 0.05f;
    double lasttime = glfwGetTime();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */

        //Different way to limit framerate than Cherno. glfwSwapInterval was not working on virtual machine.
        while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {

        };
        lasttime += 1.0/TARGET_FPS;


        R_Clear();

        SH_Bind(&shader);
        //SH_SetUniform4f(&shader, "u_Color", r, 0.3f, 0.8f, 1.0f);

        R_Draw(&va, &ib, &shader);

        if (r > 1.0f){
            increment = -0.05f;
        } else if (r < 0.0f){
            increment = 0.05f;
        }
        r += increment;

        /* Swap front and back buffers */
        glfwSwapBuffers(window);

        /* Poll for and process events */
        glfwPollEvents();
    }

    //GLCall(glDeleteProgram(shader));
    SH_Destruct(&shader);
    IB_Destruct(&ib);
    VB_Destruct(&vb);
    VA_Destruct(&va);
    TX_Destruct(&texture);

    glfwTerminate();
    return 0;
}


