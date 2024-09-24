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

//VertexBufferLayout
typedef struct VertexBufferElement {
    unsigned int type;
    unsigned int count;
    unsigned char normalized;

} VertexBufferElement;

typedef struct VertexBufferLayout {
    //use arrput
    VertexBufferElement* Elements;
    unsigned int stride;
} VertexBufferLayout;

//VertexBuffer
typedef struct VertexBuffer {
    unsigned int RendererID;

} VertexBuffer;

//IndexBuffer
typedef struct IndexBuffer {
    unsigned int RendererID;
    unsigned int Count;

} IndexBuffer;

//VertexArray
typedef struct VertexArray {
    unsigned int RendererID;

} VertexArray;


//VertexBufferLayout
unsigned int VBE_GetSizeOfType(unsigned int type);
void VBL_Pushfloat(unsigned int count, VertexBufferLayout* VBL);
void VBL_PushUint(unsigned int count, VertexBufferLayout* VBL);
void VBL_PushUchar(unsigned int count, VertexBufferLayout* VBL);
unsigned int VBL_GetStride(VertexBufferLayout* VBL);
VertexBufferElement* VBL_GetElements(VertexBufferLayout* VBL);
void VBL_Construct(VertexBufferLayout* vbl);

//Vertexbuffer
void VB_Construct(const void* data, unsigned int size, VertexBuffer* VertexBuffer);
void VB_Destruct(VertexBuffer* VertexBuffer);
void VB_Bind(VertexBuffer* VertexBuffer);
const void VB_Unbind();

//IndexBuffer
void IB_Construct(const unsigned int* data, unsigned int count, IndexBuffer* IndexBuffer);
void IB_Destruct(IndexBuffer* IndexBuffer);
const void IB_Bind(IndexBuffer* IndexBuffer);
const void IB_Unbind();
unsigned int IB_Count(IndexBuffer* IndexBuffer);

//VertexArray
void VA_Construct(VertexArray* va);
void VA_Destruct(VertexArray* va);
void VA_AddBuffer(VertexBuffer* vb, VertexBufferLayout* layout, VertexArray* va);
void VA_Bind(VertexArray* va);
const void VA_Unbind();




#endif