#include "renderer.h"
#include <stdbool.h>
#include <stdio.h>



void GLClearError(){
    while(glGetError() != GL_NO_ERROR);
};


bool GLLogCall(const char* function, const char* file, int line){
    GLenum error;
    while(error = glGetError()){
        
        printf("[OpenGL Error] (%d): %s, file: %s, line: %d\n", error, function, file, line);
        return false;
    }
    return true;
}



void R_Draw(VertexArray* va, IndexBuffer* ib, Shader* shader){

    SH_Bind(shader);
    VA_Bind(va);
    IB_Bind(ib);

    GLCall(glDrawElements(GL_TRIANGLES, ib->Count, GL_UNSIGNED_INT, NULL));

};

void R_Clear(){

    GLCall(glClear(GL_COLOR_BUFFER_BIT));

}