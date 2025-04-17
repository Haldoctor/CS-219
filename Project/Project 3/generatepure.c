#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>

#pragma pack(push, 1) // 禁用字节对齐
typedef struct {
    uint16_t signature;     // 文件标识 "BM"
    uint32_t file_size;     // 文件总大小
    uint16_t reserved1;     // 保留字段
    uint16_t reserved2;
    uint32_t data_offset;   // 像素数据偏移量
} BmpFileHeader;

typedef struct {
    uint32_t header_size;   // 信息头大小 (40)
    int32_t  width;         // 图像宽度（有符号）
    int32_t  height;        // 图像高度（有符号，正数表示倒序存储）
    uint16_t planes;        // 颜色平面数 (必须为1)
    uint16_t bits_per_pixel;// 每像素位数 (24)
    uint32_t compression;   // 压缩格式 (0=未压缩)
    uint32_t image_size;    // 像素数据大小
    int32_t  x_res;         // 水平分辨率 (像素/米)
    int32_t  y_res;         // 垂直分辨率 (像素/米)
    uint32_t colors_used;   // 调色板颜色数 (0表示不使用)
    uint32_t important_colors; // 重要颜色数 (通常0)
} BmpInfoHeader;
#pragma pack(pop)

void generate_solid_bmp(const char* filename, int width, int height,
                        uint8_t r, uint8_t g, uint8_t b) {
    // 计算行大小（4字节对齐）
    const uint32_t row_size = ((width * 3 + 3) / 4) * 4;
    const uint32_t pixel_array_size = row_size * abs(height);
    
    // 初始化文件头
    BmpFileHeader file_header = {
        .signature = 0x4D42, // 'B' 'M'
        .file_size = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader) + pixel_array_size,
        .reserved1 = 0,
        .reserved2 = 0,
        .data_offset = sizeof(BmpFileHeader) + sizeof(BmpInfoHeader)
    };

    // 初始化信息头
    BmpInfoHeader info_header = {
        .header_size = sizeof(BmpInfoHeader),
        .width = width,
        .height = height, // 正数表示倒序存储（从下到上）
        .planes = 1,
        .bits_per_pixel = 24,
        .compression = 0,
        .image_size = pixel_array_size,
        .x_res = 2835, // 72 DPI
        .y_res = 2835,
        .colors_used = 0,
        .important_colors = 0
    };

    // 创建像素数组
    uint8_t* pixels = (uint8_t*)malloc(pixel_array_size);
    if (!pixels) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }

    // 填充像素数据
    for (int y = 0; y < abs(height); y++) {
        for (int x = 0; x < width; x++) {
            // 计算像素位置
            int offset = y * row_size + x * 3;
            
            // BMP存储顺序为BGR
            pixels[offset] = b;     // 蓝色分量
            pixels[offset + 1] = g; // 绿色分量
            pixels[offset + 2] = r; // 红色分量
        }
        // 填充对齐字节
        for (int p = width * 3; p < row_size; p++) {
            pixels[y * row_size + p] = 0;
        }
    }

    // 写入文件
    FILE* file = fopen(filename, "wb");
    if (!file) {
        perror("Failed to create file");
        free(pixels);
        exit(EXIT_FAILURE);
    }

    fwrite(&file_header, 1, sizeof(BmpFileHeader), file);
    fwrite(&info_header, 1, sizeof(BmpInfoHeader), file);
    fwrite(pixels, 1, pixel_array_size, file);

    fclose(file);
    free(pixels);
}

int main() {
  generate_solid_bmp("data/white.bmp", 256, 256, 255, 255, 255);

    printf("BMP files generated successfully\n");
    return 0;
}
