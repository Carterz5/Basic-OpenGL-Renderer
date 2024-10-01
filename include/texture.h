
typedef struct Texture {
    unsigned int RendererID;
    char* FilePath;
    unsigned char* LocalBuffer;
    int Width, Height, BPP;
    
} Texture;


void TX_Construct(char* filepath, Texture* tx);
void TX_Destruct(Texture* tx);
void TX_Bind(unsigned int slot, Texture* tx);
void TX_Unbind();