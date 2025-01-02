#include <dirent.h>
#include <errno.h>
#include <stdio.h>
#include <string.h>
#include <unistd.h>

static struct {
	int a;
	int A;
	int i;
} flags;

/* FIXME: find a better way */
static int
should_print(const char *filename)
{
	return filename[0] != '.'
		|| flags.a
		|| flags.A && strcmp(filename, ".") && strcmp(filename, "..");
}

static int
ls(const char *filepath)
{
	DIR *dir;
	struct dirent *entry;

	if ((dir = opendir(filepath)) == NULL) {
		fputs("error: opendir\n", stderr);
		return -1;
	}

	for (;;) {
		errno = 0;
		if ((entry = readdir(dir)) == NULL)
			break;

		if (!should_print(entry->d_name))
			continue;

		if (flags.i)
			printf("%lu %s\n", entry->d_ino, entry->d_name);
		else
			puts(entry->d_name);
	}

	if (errno) {
		fputs("error: readdir\n", stderr);
		return -1;
	}

	if (closedir(dir)) {
		fputs("error: closedir\n", stderr);
		return -1;
	}

	return 0;
}

int
main(int argc, char **argv)
{
	const char *filepath;
	int c;

	opterr = 0;
	while ((c = getopt(argc, argv, "aAi")) != -1) {
		switch (c) {
		case 'a':
			flags.a = 1;
			break;
		case 'A':
			flags.A = 1;
			break;
		case 'i':
			flags.i = 1;
			break;
		case '?':
			fputs("usage: ls [-aAi] [DIR]\n", stderr);
			return 1;
		}
	}

	if (optind < argc)
		filepath = argv[optind];
	else
		filepath = ".";

	if (ls(filepath))
		return 1;

	return 0;
}
