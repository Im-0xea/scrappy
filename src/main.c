#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <stdnoreturn.h>
#include <getopt.h>

#include "logging.h"

bool verbose = false;

extern bool init_db(const char *);
extern void spider(const char *, const char *);

static noreturn int help(const int code)
{
	puts("Usage: spidy [OPTIONS] [initial url]\n\n"
	     " -h, --help     -> prints this\n"
	     " -V, --version  -> prints version info\n"
	     " -v, --verbose  -> output extra info\n"
	     " -d, --database -> define database (default spidy.db)");
	exit(code);
}
int main(const int c, char * const * a, char * const * v)
{
	char * db_path = "spidy.db";
	int opt;
	while ((opt = getopt(c, v, "Vvhd:")) != -1) {
		switch (opt) {
		default:
		case '?':
			exit(1);
		case 'V':
			puts("spidy v0.0");
			exit(0);
		case 'v':
			verbose = true;
			break;
		case 'h':
			help(0);
		case 'd':
			db_path = optarg;
		}
	}
	char buf_link[128];
	char * link = NULL;
	if (!init_db(db_path)) {
		if (optind >= c) {
			
			fputs("Enter Initial Link: ", stdout);
			if (scanf("%128s\n", buf_link) <= 0)
				lerror(1, "failed to parse link from stdin");
			link = buf_link;
		} else {
			link = v[optind];
		}
	}
	
	spider(db_path, link);
}
