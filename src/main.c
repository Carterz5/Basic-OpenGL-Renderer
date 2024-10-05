#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <signal.h>
#include <GL/glew.h>
#include <GLFW/glfw3.h>
#include <time.h>
#include "renderer.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"
#include "texture.h"
#include "cglm/cglm.h"
#include "cglm/mat4.h"



#define NK_INCLUDE_FIXED_TYPES
#define NK_INCLUDE_STANDARD_IO
#define NK_INCLUDE_STANDARD_VARARGS
#define NK_INCLUDE_DEFAULT_ALLOCATOR
#define NK_INCLUDE_VERTEX_BUFFER_OUTPUT
#define NK_INCLUDE_FONT_BAKING
#define NK_INCLUDE_DEFAULT_FONT
#define NK_IMPLEMENTATION
#define NK_GLFW_GL3_IMPLEMENTATION
#define NK_KEYSTATE_BASED_INPUT
#include "nuklear.h"
#include "nuklear_glfw_gl3.h"

#define MAX_VERTEX_BUFFER 512 * 1024
#define MAX_ELEMENT_BUFFER 128 * 1024


int main(void){

    struct nk_glfw glfw = {0};
    int width = 0, height = 0;
    struct nk_context *ctx;
    struct nk_colorf bg;
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
    glfwGetWindowSize(window, &width, &height);


    if (glewInit() != GLEW_OK){
        printf("Error!\n");
    }
    GLCall(const unsigned char *glversion = glGetString(GL_VERSION));
    printf("GL version is |%s|\n", glversion);

    ctx = nk_glfw3_init(&glfw, window, NK_GLFW3_INSTALL_CALLBACKS);
    {struct nk_font_atlas *atlas;
    nk_glfw3_font_stash_begin(&glfw, &atlas);
    nk_glfw3_font_stash_end(&glfw);
    }
    bg.r = 0.10f, bg.g = 0.18f, bg.b = 0.24f, bg.a = 1.0f;


    float positions[] = {
        -50.0f,  -50.0f, 0.0f, 0.0f, // 0
         50.0f,  -50.0f, 1.0f, 0.0f, // 1
         50.0f,   50.0f, 1.0f, 1.0f, // 2
        -50.0f,   50.0f, 0.0f, 1.0f, // 3
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


    mat4 proj;
    glm_ortho(0.0f, 1024.0f, 0.0f, 768.0f, -1.0f, 1.0f, proj);

    mat4 view;
    glm_mat4_identity(view);
    vec3 viewtranslation = { 0.0f, 0.0f, 0.0f};
    glm_translate(view, viewtranslation);


    mat4 model;
    glm_mat4_identity(model);
    vec3 modeltranslationA = {0.0f, 0.0f, 0.0f};
    vec3 modeltranslationB = {400.0f, 200.0f, 0.0f};
    glm_translate(model, modeltranslationA);


    float modelxA = 200.0f;
    float modelyA = 200.0f;
    float modelxB = 400.0f;
    float modelyB = 200.0f;

    mat4 mvp;
    mat4 temp;
    glm_mat4_mul(proj, view, temp);
    glm_mat4_mul(temp, model, mvp);


    Shader shader;
    SH_Construct(&shader,"../res/shaders/Basic.shader");
    SH_Bind(&shader);

    SH_SetUniformMat4f(&shader, "u_MVP", mvp);
    

    Texture texture;
    TX_Construct("../res/textures/C.png", &texture);
    TX_Bind(0, &texture);
    SH_SetUniform1i(&shader, "u_Texture", 0);


    VA_Unbind(&va);
    SH_Unbind();
    VB_Unbind();
    IB_Unbind();

    clock_t current_ticks, delta_ticks;
    clock_t fps = 0;
    float r = 0.0f;
    float increment = 0.05f;
    double lasttime = glfwGetTime();
    /* Loop until the user closes the window */
    while (!glfwWindowShouldClose(window))
    {
        /* Render here */
        current_ticks = clock();
        //Different way to limit framerate than Cherno. glfwSwapInterval was not working on virtual machine.
        while (glfwGetTime() < lasttime + 1.0/TARGET_FPS) {

        };
        lasttime += 1.0/TARGET_FPS;

        glfwPollEvents();


        //Nuklear GUI
        nk_glfw3_new_frame(&glfw);

        /* GUI */
        if (nk_begin(ctx, "Demo", nk_rect(50, 50, 230, 250),
            NK_WINDOW_BORDER|NK_WINDOW_MOVABLE|NK_WINDOW_SCALABLE|
            NK_WINDOW_MINIMIZABLE|NK_WINDOW_TITLE))
        {

            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "A X axis", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_slider_float(ctx, 1.0f, &modelxA, 1024.0f, 1.0f);
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "A Y axis", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_slider_float(ctx, 1.0f, &modelyA, 768.0f, 1.0f);
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "B X axis", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_slider_float(ctx, 1.0f, &modelxB, 1024.0f, 1.0f);
            nk_layout_row_dynamic(ctx, 20, 1);
            nk_label(ctx, "B Y axis", NK_TEXT_LEFT);
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_slider_float(ctx, 1.0f, &modelyB, 768.0f, 1.0f);
            nk_layout_row_dynamic(ctx, 25, 1);
            nk_labelf(ctx, NK_TEXT_LEFT, "FPS: %ld", fps);

        }
        nk_end(ctx);

        R_Clear();
        glClearColor(bg.r, bg.g, bg.b, bg.a);

        SH_Bind(&shader);

        modeltranslationA[0] = modelxA;
        modeltranslationA[1] = modelyA;

        modeltranslationB[0] = modelxB;
        modeltranslationB[1] = modelyB;

        glm_mat4_identity(model);
        glm_translate(model, modeltranslationA);
        glm_mat4_mul(temp, model, mvp);
        SH_SetUniformMat4f(&shader, "u_MVP", mvp);
        R_Draw(&va, &ib, &shader, &texture);


        glm_mat4_identity(model);
        glm_translate(model, modeltranslationB);
        glm_mat4_mul(temp, model, mvp);
        SH_SetUniformMat4f(&shader, "u_MVP", mvp);
        R_Draw(&va, &ib, &shader, &texture);

        if (r > 1.0f){
            increment = -0.05f;
        } else if (r < 0.0f){
            increment = 0.05f;
        }
        r += increment;


        glfwGetWindowSize(window, &width, &height);
        glViewport(0, 0, width, height);
        /* IMPORTANT: `nk_glfw_render` modifies some global OpenGL state
         * with blending, scissor, face culling, depth test and viewport and
         * defaults everything back into a default state.
         * Make sure to either a.) save and restore or b.) reset your own state after
         * rendering the UI. */
        nk_glfw3_render(&glfw, NK_ANTI_ALIASING_ON, MAX_VERTEX_BUFFER, MAX_ELEMENT_BUFFER);

        GLCall(glEnable(GL_BLEND));
        GLCall(glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA));





        /* Swap front and back buffers */
        glfwSwapBuffers(window);


        delta_ticks = clock() - current_ticks; // the time it took to render the scene
            if (delta_ticks > 0){
                fps = CLOCKS_PER_SEC / delta_ticks;
            };
        
    }

    //GLCall(glDeleteProgram(shader));
    SH_Destruct(&shader);
    IB_Destruct(&ib);
    VB_Destruct(&vb);
    VA_Destruct(&va);
    TX_Destruct(&texture);


    nk_glfw3_shutdown(&glfw);

    glfwTerminate();
    return 0;
}


