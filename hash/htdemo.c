#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "hashtab.h"

#define NBUCKETS 64
#define LINEMAX  256

static void
trim_newline(char *s)
{
	size_t n = strlen(s);
	while (n > 0 && (s[n - 1] == '\n' || s[n - 1] == '\r'))
		s[--n] = '\0';
}

int
main(int argc, char *argv[])
{
	FILE *fp;
	Hashtab *h;
	char line[LINEMAX];
	unsigned long lineno = 0;
	int rc = 0;

	if (argc != 2) {
		fprintf(stderr, "usage: %s <commands-file>\n", argv[0]);
		return 2;
	}
	fp = fopen(argv[1], "r");
	if (!fp) {
		perror(argv[1]);
		return 1;
	}
	h = ht_new(NBUCKETS);
	if (!h) {
		fprintf(stderr, "ht_new failed\n");
		fclose(fp);
		return 1;
	}

	while (fgets(line, sizeof(line), fp)) {
		char *op, *key, *save;

		lineno++;
		trim_newline(line);
		if (line[0] == '\0' || line[0] == '#')
			continue;

		op = strtok_r(line, " \t", &save);
		key = strtok_r(NULL, " \t", &save);
		if (!op || !key) {
			fprintf(stderr, "line %lu: malformed\n", lineno);
			continue;
		}

		if (strcmp(op, "insert") == 0) {
			int r = ht_insert(h, key);
			if (r < 0) {
				fprintf(stderr, "insert %s: oom\n", key);
				rc = 1;
				break;
			}
			printf("insert %-12s %s (size=%zu)\n", key,
			    r == 1 ? "ok" : "duplicate", ht_size(h));
		} else if (strcmp(op, "search") == 0) {
			int found = ht_search(h, key);
			printf("search %-12s %s\n", key,
			    found ? "found" : "missing");
		} else if (strcmp(op, "delete") == 0) {
			int r = ht_delete(h, key);
			printf("delete %-12s %s (size=%zu)\n", key,
			    r ? "ok" : "missing", ht_size(h));
		} else {
			fprintf(stderr, "line %lu: unknown op '%s'\n",
			    lineno, op);
		}
	}

	ht_free(h);
	fclose(fp);
	return rc;
}
