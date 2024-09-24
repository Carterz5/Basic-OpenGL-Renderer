#ifndef VERTEXARRAY_H
#define VERTEXARRAY_H
#include "renderer.h"
#include "vertexbuffer.h"
#include "vertexbufferlayout.h"

typedef struct VertexArray {
    unsigned int RendererID;

} VertexArray;

void VA_Construct(VertexArray* va);
void VA_Destruct(VertexArray* va);
void VA_AddBuffer(VertexBuffer* vb, const VertexBufferLayout* layout, VertexArray* va);
const void VA_Bind(VertexArray* va);
const void VA_Unbind(VertexArray* va);


#endif