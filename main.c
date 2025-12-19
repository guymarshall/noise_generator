#include <stdio.h>
#include <stdlib.h>
#include <time.h>

// TODO: make README.md

#define MAX 255

int main(int argc, char **argv)
{
	if (argc != 5)
	{
		fprintf(stderr, "Incorrect argument count of %d.\n", argc);
		fprintf(stderr, "USAGE: ./main {frame_count} {frames_per_second} {width} {height}\n");

		return 1;
	}

	int frame_count = atoi(argv[1]);
	// int frames_per_second = atoi(argv[2]);
	int width = atoi(argv[3]);
	int height = atoi(argv[4]);

	srand(time(NULL));

	char buffer[256];
	for (int i = 0; i < frame_count; i++)
	{
		snprintf(buffer, sizeof(buffer), "output-%d.ppm", i);
		const char *output_path = buffer;
		FILE *file = fopen(output_path, "wb");
		if (!file)
		{
			perror("fopen");
			return 1;
		}

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

#ifdef _WIN32
#define FFMPEG_CMD "ffmpeg.exe -y -framerate 60 -i output-%d.ppm output.mp4"
#else
#define FFMPEG_CMD "ffmpeg -y -framerate 60 -i output-%d.ppm output.mp4"
#endif

	int ret = system(FFMPEG_CMD);
	if (ret != 0)
	{
		perror("system");
		return 1;
	}

	for (int i = 0; i < frame_count; i++)
	{
		sprintf(buffer, "output-%d.ppm", i);

		remove(buffer);
	}

	return 0;
}
