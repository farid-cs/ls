#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int
main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *entry;
	char *filepath;

	filepath = argc > 1 ? argv[1] : ".";

	if ((dir = opendir(filepath)) == NULL) {
		fputs("error: opendir", stderr);
		return 1;
	}

	for (;;) {
		errno = 0;
		if ((entry = readdir(dir)) == NULL)
			break;

		puts(entry->d_name);
	}

	if (errno) {
		fputs("error: readdir", stderr);
		return 1;
	}

	if (closedir(dir)) {
		fputs("error: closedir", stderr);
		return 1;
	}

	return 0;
}
