#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H


typedef struct VertexBuffer {
    unsigned int RendererID;

} VertexBuffer;

void VB_Construct(const void* data, unsigned int size, VertexBuffer* VertexBuffer);
void VB_Destruct(VertexBuffer* VertexBuffer);
void VB_Bind(VertexBuffer* VertexBuffer);
void VB_Unbind();

#endif