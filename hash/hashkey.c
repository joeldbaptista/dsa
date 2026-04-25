#include <stdio.h>

#include "hashfn.h"

int
main(void)
{
	size_t k;
	const char *words[] = {
		"Hello", "world", "my", "name", "is", "Bakaru", NULL
	};

	for (k = 0; words[k]; ++k) {
		printf("%zu. '%s' -> %lu %lu\n", k, words[k],
		    fnv1a(words[k]), fnv1a(words[k]) % 1000);
	}
	return 0;
}
