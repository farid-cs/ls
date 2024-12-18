#include <dirent.h>
#include <errno.h>
#include <stdio.h>

int
main(void)
{

	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(".")) == NULL) {
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
