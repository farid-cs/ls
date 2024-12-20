#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

struct {
	int a;
	int A;
} flags;

int
main(int argc, char **argv)
{
	DIR *dir;
	struct dirent *entry;
	char *filepath;
	int c;

	opterr = 0;
	while ((c = getopt(argc, argv, "aA")) != -1) {
		switch (c) {
		case 'a':
			flags.a = 1;
			break;
		case 'A':
			flags.A = 1;
			break;
		case '?':
			fputs("usage: ls [-a] [DIR]\n", stderr);
			return 1;
		}
	}

	filepath = optind < argc ? argv[optind] : ".";

	if ((dir = opendir(filepath)) == NULL) {
		fputs("error: opendir", stderr);
		return 1;
	}

	for (;;) {
		errno = 0;
		if ((entry = readdir(dir)) == NULL)
			break;

		/* FIXME: find a bettry way */
		if (entry->d_name[0] != '.' || flags.a ||
		    flags.A && strcmp(entry->d_name, ".") &&
		    strcmp(entry->d_name, ".."))
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
