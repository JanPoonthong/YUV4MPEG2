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

typedef struct {
  int rx, ry, rw, rh;
} Rect;

Rect vrect(int rx, int ry, int rw, int rh) {
  return (Rect){
      .rx = rx,
      .ry = ry,
      .rw = rw,
      .rh = rh,
  };
}

YCbCr rgb_conveter(int r, int g, int b) {
  return (YCbCr){
      .y = 16 + (65.738 * r + 129.057 * g + 25.064 * b) / 256,
      .cb = 128 + (-37.945 * r - 74.494 * g + 112.439 * b) / 256,
      .cr = 128 + (112.439 * r - 94.154 * g - 18.285 * b) / 256,
  };
}

void fill_rect_rgb(char canvas[], Rect rect, int color) {
  for (int dy = 0; dy < rect.rh; dy++) {
    for (int dx = 0; dx < rect.rw; dx++) {
      int x = rect.rx + dx;
      int y = rect.ry + dy;

      if (WIDTH <= x && HEIGHT <= y) {
        canvas[y * WIDTH + x] = color;
      }
    }
  }
}

int main(void) {
  char canvas[WIDTH * HEIGHT];
  int color = 255;
  FILE *file = fopen("output.y4m", "w");
  fprintf(file, "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C444\n", WIDTH, HEIGHT,
          FRAMES_COUNT);

  fill_rect_rgb(canvas, vrect(0, 0, 0, 0), color);
  YCbCr ycbcr = rgb_conveter(255, 0, 0);
  for (int frame = 0; frame < FRAMES_COUNT; frame++) {
    fprintf(file, "FRAME\n");
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.y};
      fwrite(pixels, 1, 1, file);
    }
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.cb};
      fwrite(pixels, 1, 1, file);
    }
    for (int j = 0; j < PIXELS_SIZE; j++) {
      char pixels[] = {ycbcr.cr};
      fwrite(pixels, 1, 1, file);
    }

    float progess = round((float)frame / FRAMES_COUNT * 100);
    printf("%f%%\r", progess);
    fflush(stdout);
  }

  fclose(file);
  fprintf(stdout, "Generated output.y4m\n");
}
