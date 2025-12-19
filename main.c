#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TODO: take user input for number of frames, frames per second, width, height
// TODO: call ffmpeg to create video e.g. "ffmpeg -i output-%02d.ppm -r 60 output.mp4"
// TODO: clean up all .ppm files
// TODO: make README.md

#define MAX 255

int main(void)
{
	srand(time(NULL));

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
		fprintf(file, "%d\n", MAX);

		for (int h = 0; h < height; h++)
		{
			for (int w = 0; w < width; w++)
			{
				int red = rand() % MAX;
				int green = rand() % MAX;
				int blue = rand() % MAX;

				fputc(red, file);
				fputc(green, file);
				fputc(blue, file);
			}
		}

		fclose(file);
		printf("Generated %s\n", output_path);
	}

	return 0;
}
