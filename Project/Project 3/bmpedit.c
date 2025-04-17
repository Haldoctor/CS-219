#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>

#pragma pack(push, 1)
typedef struct {
  char signature[2];
  int file_size;
  short reserved1;
  short reserved2;
  int data_offset;
} BmpFileHeader;

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
} BmpInfoHeader;

typedef struct {
  BmpFileHeader file_header;
  BmpInfoHeader info_header;
  unsigned char* pixel_data;
  int row_size;
} BmpImage;
#pragma pack(pop)

#define CHECK_NULL(ptr, msg)                  \
  do {                                        \
    if ((ptr) == NULL) {                      \
      fprintf(stderr, "Error: %s\n", (msg));  \
      exit(EXIT_FAILURE);                     \
    }                                         \
  } while (0)

typedef struct {
  char* output_file;
  char* input_files[2];
  int input_count;
  char* operation;
  int value;
} Config;

BmpImage* read_bmp(const char* filename);
void write_bmp(const char* filename, BmpImage* image);
void adjust_brightness(BmpImage* image, int delta);
void average_blend(BmpImage* img1, BmpImage* img2, BmpImage* result);
void free_bmp(BmpImage* image);
void parse_arguments(int argc, char* argv[], Config* config);

BmpImage* read_bmp(const char* filename) {
  FILE* file = fopen(filename, "rb");
  CHECK_NULL(file, "Failed to open file");

  BmpImage* image = malloc(sizeof(BmpImage));
  CHECK_NULL(image, "Memory allocation failed");

  if (fread(&image->file_header, sizeof(BmpFileHeader), 1, file) != 1) {
    fprintf(stderr, "Error reading file header\n");
    exit(EXIT_FAILURE);
  }

  if (image->file_header.signature[0] != 'B' ||
      image->file_header.signature[1] != 'M') {
    fprintf(stderr, "Invalid BMP file\n");
    exit(EXIT_FAILURE);
  }

  if (fread(&image->info_header, sizeof(BmpInfoHeader), 1, file) != 1) {
    fprintf(stderr, "Error reading info header\n");
    exit(EXIT_FAILURE);
  }

  if (image->info_header.bits_per_pixel != 24 ||
      image->info_header.compression != 0) {
    fprintf(stderr, "Unsupported BMP format\n");
    exit(EXIT_FAILURE);
  }

  image->row_size = ((image->info_header.width * 3 + 3) / 4) * 4;
  image->pixel_data = malloc(image->row_size * image->info_header.height);
  CHECK_NULL(image->pixel_data, "Pixel data allocation failed");

  fseek(file, image->file_header.data_offset, SEEK_SET);
  if (fread(image->pixel_data, 1, image->row_size * image->info_header.height,
           file) != image->row_size * image->info_header.height) {
    fprintf(stderr, "Error reading pixel data\n");
    exit(EXIT_FAILURE);
  }

  fclose(file);
  return image;
}

void write_bmp(const char* filename, BmpImage* image) {
  FILE* file = fopen(filename, "wb");
  CHECK_NULL(file, "Failed to create output file");

  fwrite(&image->file_header, sizeof(BmpFileHeader), 1, file);
  fwrite(&image->info_header, sizeof(BmpInfoHeader), 1, file);

  fseek(file, image->file_header.data_offset, SEEK_SET);
  fwrite(image->pixel_data, 1, image->row_size * image->info_header.height, file);

  fclose(file);
}

void adjust_brightness(BmpImage* image, int delta) {
  unsigned char* ptr = image->pixel_data;
  int total_bytes = image->row_size * image->info_header.height;

  for (int i = 0; i < total_bytes; ++i) {
    int val = (int)ptr[i] + delta;
    ptr[i] = (unsigned char)fmax(0, fmin(255, val));
  }
}

void average_blend(BmpImage* img1, BmpImage* img2, BmpImage* result) {
  if (img1->info_header.width != img2->info_header.width ||
      img1->info_header.height != img2->info_header.height) {
    fprintf(stderr, "Image dimensions mismatch\n");
    exit(EXIT_FAILURE);
  }

  unsigned char* p1 = img1->pixel_data;
  unsigned char* p2 = img2->pixel_data;
  unsigned char* pres = result->pixel_data;
  int total_bytes = img1->row_size * img1->info_header.height;

  for (int i = 0; i < total_bytes; ++i) {
    pres[i] = (p1[i] + p2[i]) / 2;
  }
}

void convert_to_grayscale(BmpImage* image) {
  unsigned char* ptr = image->pixel_data;
  int width = image->info_header.width;
  int height = image->info_header.height;

  for (int y = 0; y < height; ++y) {
    for (int x = 0; x < width; ++x) {
      int offset = y * image->row_size + x * 3;

      unsigned char b = ptr[offset];
      unsigned char g = ptr[offset + 1];
      unsigned char r = ptr[offset + 2];

      unsigned char gray = (unsigned char)((r * 77 + g * 150 + b * 29 + 128) / 256);

      ptr[offset] = gray;
      ptr[offset + 1] = gray;
      ptr[offset + 2] = gray;
    }
  }
}

void free_bmp(BmpImage* image) {
  if (image) {
    free(image->pixel_data);
    free(image);
  }
}

void parse_arguments(int argc, char* argv[], Config* config) {
  int opt;
  config->input_count = 0;
  config->operation = NULL;
  config->value = 0;

  while ((opt = getopt(argc, argv, "i:o:p:")) != -1) {
    switch (opt) {
      case 'i':
        if (config->input_count < 2) {
          config->input_files[config->input_count++] = optarg;
        }
        break;
      case 'o':
        config->output_file = optarg;
        break;
      case 'p':
        if (optarg) {
          config->operation = optarg;
          if (strcmp(optarg, "add") == 0 && optind < argc) {
            config->value = atoi(argv[optind++]);
          }
        }
        break;
      default:
        fprintf(stderr, "Usage: %s -i input1.bmp [-i input2.bmp] -o output.bmp "
                "-p [add|average|grayscale] [value]\n", argv[0]);
        exit(EXIT_FAILURE);
    }
  }

  if (config->input_count == 0 || !config->output_file || !config->operation) {
    fprintf(stderr, "Missing required arguments\n");
    exit(EXIT_FAILURE);
  }

  if (strcmp(config->operation, "average") == 0 && config->input_count != 2) {
    fprintf(stderr, "Average operation requires two input files\n");
    exit(EXIT_FAILURE);
  }
}

int main(int argc, char* argv[]) {
  Config config;
  parse_arguments(argc, argv, &config);

  BmpImage* img1 = read_bmp(config.input_files[0]);
  BmpImage* result = NULL;

  if (strcmp(config.operation, "add") == 0) {
    adjust_brightness(img1, config.value);
    result = img1;
  } else if (strcmp(config.operation, "average") == 0) {
    if (config.input_count != 2) {
      fprintf(stderr, "Average operation requires two input files\n");
      exit(EXIT_FAILURE);
    }
    BmpImage* img2 = read_bmp(config.input_files[1]);
    result = malloc(sizeof(BmpImage));
    memcpy(result, img1, sizeof(BmpImage));
    result->pixel_data = malloc(img1->row_size * img1->info_header.height);
    memcpy(result->pixel_data, img1->pixel_data,
          img1->row_size * img1->info_header.height);
    average_blend(img1, img2, result);
    free_bmp(img2);
  } else if (strcmp(config.operation, "grayscale") == 0) {
    convert_to_grayscale(img1);
    result = img1;
  } else {
    fprintf(stderr, "Unknown operation: %s\n", config.operation);
    exit(EXIT_FAILURE);
  }

  write_bmp(config.output_file, result);

  free_bmp(result);
  if (result != img1) {
    free_bmp(img1);
  }

  return 0;
}
