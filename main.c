#include <stdio.h>

void save_ppm_file(int pixels[], int pixels_size, int stride)
{
	int w = stride;
	int h = pixels_size / stride;
	FILE *out_put = fopen("output.ppm", "w");
	fprintf(out_put, "P3\n%i %i 255\n", w, h);
	int r, g, b;
	
	unsigned char * pix = (unsigned char*) pixels;
	
	for (int i = 0; i < pixels_size; i++) {
		r = pix[0];
		g = pix[1];
		b = pix[2];
		fprintf(out_put, "%u %u %u  ", r, g, b);
		pix+=4;
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
