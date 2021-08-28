#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 30
#define DURATION 2
#define frames_count (FPS * DURATION)
#define pixels_size (WIDTH * HEIGHT)

typedef struct
{
  int y, cb, cr;
} YCbCr;

void save_ppm_file(int pixels[], int stride)
{
  int w = stride;
  int h = pixels_size / stride;
  FILE *out_put = fopen("output.ppm", "w");
  const int buffer_size = 3;

  fprintf(out_put, "P6\n%i %i 255\n", w, h);
  for (int i = 0; i < pixels_size; i++)
  {
    char buffer[] = {
        (pixels[i] >> 8 * 2) & 0xFF,
        (pixels[i] >> 8 * 1) & 0xFF,
        (pixels[i] >> 8 * 0) & 0xFF,
    };
    fwrite(buffer, 1, buffer_size, out_put);
  }

  fclose(out_put);
}

void uv_gradient_pattern(int stride, int pixels[])
{
  int width = stride;
  int height = pixels_size / stride;
  for (int y = 0; y < height; y++)
  {
    for (int x = 0; x < width; x++)
    {
      float u = (float)x / width;
      float v = (float)y / height;
      int r = u * 255;
      int g = v * 255;
      pixels[y * width + x] = (r << 8 * 2) | (g << 8 * 1);
    }
  }
}

void assign_zero_color(int pixels[])
{
  for (int i = 0; i < pixels_size; i++)
  {
    pixels[i] = 0;
  }
}

void random_pattern(int pixels[], int stride, int luma)
{
  int w = stride;
  int h = pixels_size / w;
  for (int y = 0; y < h; y++)
  {
    for (int x = 0; x < w; x++)
    {
      int cb = x & 0xFF;
      int cr = y & 0xFF;
      pixels[y * stride + x] =
          (luma << (8 * 2)) | (cb << (8 * 0)) | (cr << (8 * 1));
    }
  }
}

YCbCr rgb_conveter(int r, int g, int b)
{
  return (YCbCr){
      .y = 16 + (65.738 * r + 129.057 * g + 25.064 * b) / 256,
      .cb = 128 + (-37.945 * r - 74.494 * g + 112.439 * b) / 256,
      .cr = 128 + (112.439 * r - 94.154 * g - 18.285 * b) / 256,
  };
}

int main(void)
{
  int pixels[WIDTH * HEIGHT];
  assign_zero_color(pixels);

  FILE *out_put = fopen("output.y4m", "w");
  fprintf(out_put, "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C444\n", WIDTH, HEIGHT,
          frames_count);

  YCbCr ycbcr = rgb_conveter(255, 0, 0);
  for (int j = 0; j < frames_count; j++)
  {
    fprintf(out_put, "FRAME\n");
    for (int j = 0; j < pixels_size; j++)
    {
      char pixels[] = {ycbcr.y};
      fwrite(pixels, 1, 1, out_put);
    }
    for (int j = 0; j < pixels_size; j++)
    {
      char pixels[] = {ycbcr.cb};
      fwrite(pixels, 1, 1, out_put);
    }
    for (int j = 0; j < pixels_size; j++)
    {
      char pixels[] = {ycbcr.cr};
      fwrite(pixels, 1, 1, out_put);
    }
  }

  fclose(out_put);
  fprintf(stdout, "Generated output.y4m\n");
}
