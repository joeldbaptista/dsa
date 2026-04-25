#ifndef HASHTAB_H
#define HASHTAB_H
#include <stddef.h>

typedef struct hashtab Hashtab;

Hashtab *ht_new(size_t nbuckets);
void     ht_free(Hashtab *h);
int      ht_insert(Hashtab *h, const char *key);
int      ht_search(const Hashtab *h, const char *key);
int      ht_delete(Hashtab *h, const char *key);
size_t   ht_size(const Hashtab *h);

#endif
