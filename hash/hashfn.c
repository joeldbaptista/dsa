#include "hashfn.h"

static const uint64_t FNV_OFFSET = 14695981039346656037UL;
static const uint64_t FNV_PRIME = 1099511628211UL;

uint64_t
fnv1a(const char *key)
{
	const char *p;
	uint64_t hash = FNV_OFFSET;

	for (p = key; *p; p++) {
		hash ^= (uint64_t)(unsigned char)(*p);
		hash *= FNV_PRIME;
	}
	return hash;
}
