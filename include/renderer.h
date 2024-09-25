#ifndef RENDERER_H
#define RENDERER_H
#include <GL/glew.h>
#include <signal.h>
#include <stdbool.h>
#include "stb_ds.h"
#include "shader.h"
#include "indexbuffer.h"
#include "vertexarray.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"




#define TARGET_FPS 60
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);

void R_Draw(VertexArray* va, IndexBuffer* ib, Shader* shader);
void R_Clear();

#endif