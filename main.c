#include <stdio.h>

// TODO(jan): Maybe
// typedef struct {
// 	int r, g, b;
// 
// } rgb;
//
//

int buffer[3];
const int buffer_size = sizeof(buffer) / sizeof(buffer[0]);

void make_rgb(int r, int g, int b, int buffer[])
{

	buffer[0] = r;
	buffer[1] = g;
	buffer[2] = b;
}

void save_ppm_file(int pixels[], int pixels_size, int stride)
{
	int w = stride;
	int h = pixels_size / stride;
	FILE *out_put = fopen("output.ppm", "w");
	int r, g, b;

	fprintf(out_put, "P6\n%i %i 255\n", w, h);
	for (int i = 0; i < pixels_size; i++) {
		r = pixels[i] >> (8 * 2) & 0xFF;
		g = pixels[i] >> (8 * 1) & 0xFF;
		b = pixels[i] >> (8 * 0) & 0xFF;
		make_rgb(r, g, b, buffer);
		for (int i = 0; i < buffer_size; i++) {
			fwrite(&buffer[i], 1, 1, out_put);

		}
	}
	fwrite(&buffer, 1, 1, out_put);

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
