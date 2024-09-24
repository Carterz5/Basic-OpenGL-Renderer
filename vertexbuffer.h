#ifndef VERTEXBUFFER_H
#define VERTEXBUFFER_H
#include "renderer.h"


typedef struct VertexBuffer {
    unsigned int RendererID;

} VertexBuffer;

void VB_Construct(const void* data, unsigned int size, VertexBuffer* VertexBuffer);
void VB_Destruct(VertexBuffer* VertexBuffer);
const void VB_Bind(VertexBuffer* VertexBuffer);
const void VB_Unbind();

#endif