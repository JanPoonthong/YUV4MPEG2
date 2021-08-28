#include <math.h>
#include <stdio.h>

#define WIDTH 800
#define HEIGHT 600
#define FPS 30
#define DURATION 2
#define FRAMES_COUNT (FPS * DURATION)
#define PIXELS_SIZE (WIDTH * HEIGHT)

typedef struct {
  int y, cb, cr;
} YCbCr;

void assign_zero_color(int pixels[]) {
  for (int i = 0; i < PIXELS_SIZE; i++) {
    pixels[i] = 0;
  }
}

YCbCr rgb_conveter(int r, int g, int b) {
  return (YCbCr){
      .y = 16 + (65.738 * r + 129.057 * g + 25.064 * b) / 256,
      .cb = 128 + (-37.945 * r - 74.494 * g + 112.439 * b) / 256,
      .cr = 128 + (112.439 * r - 94.154 * g - 18.285 * b) / 256,
  };
}

int main(void) {
  int pixels[WIDTH * HEIGHT];
  assign_zero_color(pixels);

  FILE *out_put = fopen("output.y4m", "w");
  fprintf(out_put, "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C444\n", WIDTH, HEIGHT,
          FRAMES_COUNT);

  YCbCr ycbcr = rgb_conveter(138, 43, 226);
  for (int frame = 0; frame < FRAMES_COUNT; frame++) {
    fprintf(out_put, "FRAME\n");
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.y};
      fwrite(pixels, 1, 1, out_put);
    }
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.cb};
      fwrite(pixels, 1, 1, out_put);
    }
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.cr};
      fwrite(pixels, 1, 1, out_put);
    }

    float progess = round((float)frame / FRAMES_COUNT * 100);
    printf("%f%%\r", progess);
    fflush(stdout);
  }

  fclose(out_put);
  fprintf(stdout, "Generated output.y4m\n");
}
