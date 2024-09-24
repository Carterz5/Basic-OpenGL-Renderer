#ifndef INDEXBUFFER_H
#define INDEXBUFFER_H


typedef struct IndexBuffer {
    unsigned int RendererID;
    unsigned int Count;

} IndexBuffer;

void IB_Construct(const unsigned int* data, unsigned int count, IndexBuffer* IndexBuffer);
void IB_Destruct(IndexBuffer* IndexBuffer);
const void IB_Bind(IndexBuffer* IndexBuffer);
const void IB_Unbind();
unsigned int IB_Count(IndexBuffer* IndexBuffer);

#endif