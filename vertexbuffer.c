#include "renderer.h"
#include "vertexbuffer.h"




void VB_Construct(const void* data, unsigned int size, VertexBuffer* VertexBuffer){
    GLCall(glGenBuffers(1, &VertexBuffer->RendererID));
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->RendererID));
    GLCall(glBufferData(GL_ARRAY_BUFFER, size, data, GL_STATIC_DRAW));
}

void VB_Destruct(VertexBuffer* VertexBuffer){
    GLCall(glDeleteBuffers(1, &VertexBuffer->RendererID))
};

void VB_Bind(VertexBuffer* VertexBuffer){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, VertexBuffer->RendererID));
};

const void VB_Unbind(){
    GLCall(glBindBuffer(GL_ARRAY_BUFFER, 0));
};