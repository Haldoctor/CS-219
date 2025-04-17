#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <sys/stat.h>

// 增强版目录创建函数
void create_data_dir() {
  const char* dir_path = "data";
  
  // 检查目录是否已存在
  struct stat st;
  if (stat(dir_path, &st) == 0) {
      if (S_ISDIR(st.st_mode)) {
          return;  // 目录已存在
      } else {
          fprintf(stderr, "Error: 'data' exists but is not a directory\n");
          exit(EXIT_FAILURE);
      }
  }

  // 创建目录（兼容Windows和Linux）
  #ifdef _WIN32
  int ret = _mkdir(dir_path);
  #else
  int ret = mkdir(dir_path, 0777);  // 设置权限rwxrwxrwx
  #endif

  if (ret != 0) {
      perror("Failed to create data directory");
      exit(EXIT_FAILURE);
  }
}


#pragma pack(push, 1)
typedef struct {
    char signature[2];
    int file_size;
    short reserved1;
    short reserved2;
    int data_offset;
} BMPFileHeader;

typedef struct {
    int header_size;
    int width;
    int height;
    short planes;
    short bits_per_pixel;
    int compression;
    int image_size;
    int x_pixels_per_m;
    int y_pixels_per_m;
    int colors_used;
    int important_colors;
} BMPInfoHeader;
#pragma pack(pop)

void create_dir(const char* path) {
    #ifdef _WIN32
    _mkdir(path);
    #else
    mkdir(path, 0777);
    #endif
}

int main() {
    create_dir("data");  // 创建目录
    srand(time(NULL));

    const int width = 256;
    const int height = 256;
    const int block_size = 64;  // 256/4=64
    const int bytes_per_pixel = 3;

    // 计算行大小（4字节对齐）
    int row_size = (width * bytes_per_pixel + 3) & ~3;

    // 初始化文件头
    BMPFileHeader file_header = {
        .signature = {'B', 'M'},
        .file_size = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader) + row_size * height,
        .reserved1 = 0,
        .reserved2 = 0,
        .data_offset = sizeof(BMPFileHeader) + sizeof(BMPInfoHeader)
    };

    // 初始化信息头
    BMPInfoHeader info_header = {
        .header_size = sizeof(BMPInfoHeader),
        .width = width,
        .height = height,
        .planes = 1,
        .bits_per_pixel = 24,
        .compression = 0,
        .image_size = row_size * height,
        .x_pixels_per_m = 2835,
        .y_pixels_per_m = 2835,
        .colors_used = 0,
        .important_colors = 0
    };

    // 生成16种随机颜色（BGR格式）
    unsigned char colors[16][3];
    for (int i = 0; i < 16; i++) {
        colors[i][0] = rand() % 256;  // 蓝
        colors[i][1] = rand() % 256;  // 绿
        colors[i][2] = rand() % 256;  // 红
    }

    // 创建像素数组（从下到上存储）
    unsigned char pixels[height][row_size];
    
    // 填充4x4色块
    for (int block_y = 0; block_y < 4; block_y++) {
        for (int block_x = 0; block_x < 4; block_x++) {
            // 当前色块颜色索引
            int color_index = block_y * 4 + block_x;
            
            // 计算色块像素范围
            int start_x = block_x * block_size;
            int end_x = (block_x + 1) * block_size;
            int start_y = block_y * block_size;
            int end_y = (block_y + 1) * block_size;

            // 填充色块
            for (int y = start_y; y < end_y; y++) {
                for (int x = start_x; x < end_x; x++) {
                    int pos = x * bytes_per_pixel;
                    pixels[y][pos]     = colors[color_index][0];  // 蓝
                    pixels[y][pos + 1] = colors[color_index][1];  // 绿
                    pixels[y][pos + 2] = colors[color_index][2];  // 红
                }
            }
        }
    }

    // 写入文件
    FILE* file = fopen("data/color_blocks.bmp", "wb");
    if (!file) {
        perror("Error creating file");
        return 1;
    }

    fwrite(&file_header, sizeof(BMPFileHeader), 1, file);
    fwrite(&info_header, sizeof(BMPInfoHeader), 1, file);
    
    // BMP数据从下到上写入
    for (int y = height-1; y >= 0; y--) {
        fwrite(pixels[y], 1, row_size, file);
    }

    fclose(file);
    printf("生成成功：data/color_blocks.bmp\n");
    return 0;
}
