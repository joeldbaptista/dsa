#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

#define FNV_OFFSET 14695981039346656037UL
#define FNV_PRIME 1099511628211UL

/* Return 64-bit FNV-1a hash for key (NUL-terminated). See description:
https://en.wikipedia.org/wiki/Fowler–Noll–Vo_hash_function */
static uint64_t
hashkey(const char *key)
{
	const char *p;
	uint64_t hash = FNV_OFFSET;

	for (p = key; *p; p++) {
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	return hash;
}

int
main(void)
{
	size_t k;
	const char *words[] = {
		"Hello", "world", "my", "name", "is", "Bakaru", NULL
	};

	for (k = 0; words[k]; ++k) {
		printf("%lu. '%s' -> %lu %lu\n", k, words[k], hashkey(words[k]), hashkey(words[k])%1000);
	}

	k = 123;
	printf("test 123 -> %lu %lu\n", hashkey((const char *)&k), hashkey((const char *)&k)%1000);
	return 0;
}
