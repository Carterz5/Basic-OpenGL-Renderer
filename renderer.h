#ifndef RENDERER_H
#define RENDERER_H
#include <GL/glew.h>
#include <signal.h>
#include <stdbool.h>
#include "stb_ds.h"




#define TARGET_FPS 60
#define ASSERT(x) if (!(x)) raise(SIGTRAP);
#define GLCall(x) GLClearError();\
    x;\
    ASSERT(GLLogCall(#x, __FILE__, __LINE__))

void GLClearError();
bool GLLogCall(const char* function, const char* file, int line);


#endif