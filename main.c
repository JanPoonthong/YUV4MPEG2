#include <stdio.h>

void save_ppm_file(int pixels[], int pixels_size, int stride)
{
	int w = stride;
	int h = pixels_size / stride;
	FILE *out_put = fopen("output.ppm", "w");
	fprintf(out_put, "P3\n%i %i 255\n", w, h);
	int r, g, b;
	for (int i = 0; i < pixels_size; i++) {
		r = pixels[i] << (8 * 2) & 0xFF;
		g = pixels[i] << (8 * 1) & 0xFF;
		b = pixels[i] << (8 * 0) & 0xFF;
		fprintf(out_put, "%d %d %d  ", r, g, b);
	}
}

int main(void) 
{
	int COLOR        = 0x00FFFF;
	const int WIDTH  = 200;
	const int HEIGHT = 200;
	int pixels[WIDTH * HEIGHT];

	int pixels_size  = sizeof(pixels) / sizeof(pixels[0]);
	for (int i = 0; i < pixels_size; i++) {
		pixels[i] = COLOR;
	}

	save_ppm_file(pixels, pixels_size, WIDTH);
}
