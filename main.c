#include <stdio.h>

void save_ppm_file(int pixels[], int pixels_size, int stride)
{
	int w = stride;
	int h = pixels_size / stride;
	FILE *out_put = fopen("output.ppm", "w");
	int r, g, b;
	const int buffer_size = 3;

	fprintf(out_put, "P6\n%i %i 255\n", w, h);
	for (int i = 0; i < pixels_size; i++) {
		char buffer[] = {
			pixels[i] >> (8 * 2) & 0xFF,
			pixels[i] >> (8 * 1) & 0xFF,
			pixels[i] >> (8 * 0) & 0xFF,
		};
		fwrite(buffer, 1, buffer_size, out_put);
	}

	fclose(out_put);
}

void uv_gradient_pattern(int stride, int pixels[], int pixels_size)
{
	int width = stride;
	int height = pixels_size / stride;
	for (int y = 0; y < height; y++) {
		for (int x = 0; x < width; x++) {
			float u = (float) x / width;
			float v = (float) y / height;
			int r = u * 255;
			int g = v * 255;
			pixels[y * width + x] = (r << 8 * 2) | (g << 8 * 1);
		}
	}
}

void assign_background_color(int COLOR, int pixels[], int pixels_size)
{
	for (int i = 0; i < pixels_size; i++) {
		pixels[i] = COLOR;
	}
}

void generate_yuvmpeg(int stride, int pixels_size)
{
	int w = stride;
	int h = pixels_size / stride;
	int fps = 30;
	FILE *out_put = fopen("output.y4m", "w");
	fprintf(out_put, "YUV4MPEG2 W%d H%d F%d:1 Ip A1:1 C444\n", w, h, fps);

	for (int i = 0; i < fps; i++) {
		fprintf(out_put, "FRAME\n");
		for (int j = 0; j < w*h; j++) {
			char pixels[] = {76, 84, 255};;
			fwrite(pixels, 1, 3, out_put);
		}
	}

	fclose(out_put);
}

int main(void) 
{
	int COLOR        = 0x00FFFF;
	const int WIDTH  = 500;
	const int HEIGHT = 500;
	int pixels[WIDTH * HEIGHT];
	int pixels_size  = WIDTH * HEIGHT;

	assign_background_color(COLOR, pixels, pixels_size);
	generate_yuvmpeg(WIDTH, pixels_size);

	// uv_gradient_pattern(WIDTH, pixels, pixels_size);
	// save_ppm_file(pixels, pixels_size, WIDTH);
}
