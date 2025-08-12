#include <cstdio>
#include <raylib.h>
#include <cstdint>
#include <cstdlib>
#include <cstring>

#include "qrcodegen.h"
#include "version.h"

int main(int argc, char * argv[])
{
    int scale = 10;
    qrcodegen_Ecc eccValue = qrcodegen_Ecc_LOW;

    switch(argc)
    {
        case 1: printf("No args! Ending...\n"); return 1;

        case 4: eccValue = (qrcodegen_Ecc) atoi(argv[3]); [[fallthrough]];
        case 3: scale = atoi(argv[2]); break;
    }

    uint8_t qrCode[qrcodegen_BUFFER_LEN_MAX];
    {
        uint8_t temp[qrcodegen_BUFFER_LEN_MAX];
        if(!qrcodegen_encodeText(argv[1], temp, qrCode, eccValue, qrcodegen_VERSION_MIN, qrcodegen_VERSION_MAX, qrcodegen_Mask_AUTO, true))
        {
            printf("Encoding error! Ending...\n");
            return 2;
        }
    }

    const int size = qrcodegen_getSize(qrCode);
    uint8_t pixels[size][size];
    char title[512];

    for (int y = 0; y < size; y++)
		for (int x = 0; x < size; x++)
			pixels[x][y] = qrcodegen_getModule(qrCode, x, y) ? 0x00 : 0xFF;
    
    sprintf(title, "%s %s (%dx%d)", BUILD_TEXT, argv[1], size, size);
    InitWindow(size * scale, size * scale, title);
    SetTargetFPS(0);

    Texture2D tex = LoadTextureFromImage(
        {.data = pixels, .width = size, .height = size, .mipmaps = 1, .format = PIXELFORMAT_UNCOMPRESSED_GRAYSCALE});

    while(!WindowShouldClose() && !IsKeyPressed(KEY_ESCAPE))
    {
        BeginDrawing();
            ClearBackground(WHITE);
            DrawTextureEx(tex, {}, 0, scale, WHITE);
        EndDrawing();
    }
    return 0;
}