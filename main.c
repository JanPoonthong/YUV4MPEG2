#include <stdio.h>

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

  fclose(out_put);
}

int main(void) {
  const int WIDTH = 800;
  const int HEIGHT = 600;
  int pixels[WIDTH * HEIGHT];
  int pixels_size = WIDTH * HEIGHT;
  int FPS = 30;
  int DURATION = 1;
  int frames_count = (FPS * DURATION);

  assign_zero_color(pixels, pixels_size);
  generate_yuvmpeg(WIDTH, pixels_size);

  // uv_gradient_pattern(WIDTH, pixels, pixels_size);
  // save_ppm_file(pixels, pixels_size, WIDTH);
}
