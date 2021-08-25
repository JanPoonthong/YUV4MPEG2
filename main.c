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
}

void assign_background_color(int COLOR, int pixels[], int pixels_size)
{
	for (int i = 0; i < pixels_size; i++) {
		pixels[i] = COLOR;
	}
}

int main(void) 
{
	int COLOR        = 0x00FFFF;
	const int WIDTH  = 500;
	const int HEIGHT = 500;
	int pixels[WIDTH * HEIGHT];
	int pixels_size  = WIDTH * HEIGHT;

	assign_background_color(COLOR, pixels, pixels_size);
	// uv_gradient_pattern(HEIGHT, WIDTH, pixels);
	for (int y = 0; y < HEIGHT; y++) {
		for (int x = 0; x < WIDTH; x++) {
			float u = x / WIDTH;
			float v = y / HEIGHT;
			printf("%d %d\n", u, v);
			int r = u * 255;
			int g = v * 255;
			// printf("%d %d\n", r, g);
			pixels[y * WIDTH + x] = (r << 8 * 2) | (g << 8 * 1);
		}
	}

	save_ppm_file(pixels, pixels_size, WIDTH);
}
