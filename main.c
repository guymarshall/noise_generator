#include <stdio.h>

// TODO: make image of random pixels
// TODO: take user input for number of frames, frames per second, width, height
// TODO: call ffmpeg to create video e.g. "ffmpeg -i output-%02d.ppm -r 60 output.mp4"
// TODO: clean up all .ppm files
// TODO: make README.md

int main(void)
{
	char buffer[256];
	for (int i = 0; i < 60; i++)
	{
		snprintf(buffer, sizeof(buffer), "output-%02d.ppm", i);
		const char *output_path = buffer;
		FILE *file = fopen(output_path, "wb");

		int width = 16 * 60;
		int height = 9 * 60;

		fprintf(file, "P6\n");
		fprintf(file, "%d %d\n", width, height);
		fprintf(file, "255\n");

		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				fputc(0xFF, file);
				fputc(0x00, file);
				fputc(0x00, file);
			}
		}

		fclose(file);
		printf("Generated %s\n", output_path);
	}

	return 0;
}
