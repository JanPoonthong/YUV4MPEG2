#include <stdio.h>

typedef struct {
  int y, cb, cr;
} YCbCr;

void save_ppm_file(int pixels[], int pixels_size, int stride) {
  int w = stride;
  int h = pixels_size / stride;
  FILE *out_put = fopen("output.ppm", "w");
  const int buffer_size = 3;

  fprintf(out_put, "P6\n%i %i 255\n", w, h);
  for (int i = 0; i < pixels_size; i++) {
    char buffer[] = {
        (pixels[i] >> 8 * 2) & 0xFF,
        (pixels[i] >> 8 * 1) & 0xFF,
        (pixels[i] >> 8 * 0) & 0xFF,
    };
    fwrite(buffer, 1, buffer_size, out_put);
  }

  fclose(out_put);
}

void uv_gradient_pattern(int stride, int pixels[], int pixels_size) {
  int width = stride;
  int height = pixels_size / stride;
  for (int y = 0; y < height; y++) {
    for (int x = 0; x < width; x++) {
      float u = (float)x / width;
      float v = (float)y / height;
      int r = u * 255;
      int g = v * 255;
      pixels[y * width + x] = (r << 8 * 2) | (g << 8 * 1);
    }
  }
}

void assign_zero_color(int pixels[], int pixels_size) {
  for (int i = 0; i < pixels_size; i++) {
    pixels[i] = 0;
  }
}

void random_pattern(int pixels[], int stride, int pixel_size, int luma)
{
  int w = stride;
  int h = pixel_size / w;
  for (int y = 0; y < h; y++) {
    for (int x = 0; x < w; x++) {
      int cb = y & 0xFF;
      int cr = x & 0xFF;
      pixels[y*stride+x] = (luma << (8 * 2)) | (cb << (8 * 0)) | (cr << (8 * 1));
    }
  }
}

void generate_yuvmpeg(int stride, int pixels_size, int pixels[], FILE *out_put) {
  fprintf(out_put, "FRAME\n");
  for (int i = 0; i < pixels_size; i++) {
    char ycbcr[] = {
      (pixels[i] >> 8*2) & 0xFF, // y
      (pixels[i] >> 8*0) & 0xFF, // cb
      (pixels[i] >> 8*1) & 0xFF, // cr
    };
    fwrite(ycbcr, 1, 3, out_put);
  }
}

int main(void) {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  int pixels[WIDTH * HEIGHT];
  const int pixels_size = WIDTH * HEIGHT;
  const int FPS = 30;
  const int DURATION = 5;
  const int frames_count = (FPS * DURATION);

  assign_zero_color(pixels, pixels_size);

  FILE *out_put = fopen("output.y4m", "w");
  fprintf(out_put, "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C444\n", WIDTH, HEIGHT, frames_count);

  for (int j = 0; j < frames_count; j++) {
    float luma = ((float)j / frames_count) * 255.0;
    random_pattern(pixels, WIDTH, pixels_size, luma);
    generate_yuvmpeg(WIDTH, pixels_size, pixels, out_put);
  }

  fclose(out_put);
  fprintf(stdout, "Generated output.y4m\n");
  // uv_gradient_pattern(WIDTH, pixels, pixels_size);
  // save_ppm_file(pixels, pixels_size, WIDTH);
}
