#include "renderer.h"
#include "indexbuffer.h"




void IB_Construct(const unsigned int* data, unsigned int count, IndexBuffer* IndexBuffer){
    ASSERT(sizeof(unsigned int) == sizeof(GLuint));
    IndexBuffer->Count = count;

    GLCall(glGenBuffers(1, &IndexBuffer->RendererID));
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->RendererID));
    GLCall(glBufferData(GL_ELEMENT_ARRAY_BUFFER, count * sizeof(unsigned int), data, GL_STATIC_DRAW));
}

void IB_Destruct(IndexBuffer* IndexBuffer){
    GLCall(glDeleteBuffers(1, &IndexBuffer->RendererID))
};

const void IB_Bind(IndexBuffer* IndexBuffer){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, IndexBuffer->RendererID));
};

const void IB_Unbind(){
    GLCall(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));
};

unsigned int IB_Count(IndexBuffer* IndexBuffer){
    return IndexBuffer->Count;
};