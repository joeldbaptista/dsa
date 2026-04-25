#include <stdlib.h>
#include <string.h>

#include "hashfn.h"
#include "hashtab.h"

struct node {
	char        *key;
	struct node *next;
};

struct hashtab {
	struct node **buckets;
	size_t        nbuckets;
	size_t        nitems;
};

Hashtab *
ht_new(size_t nbuckets)
{
	Hashtab *h;

	if (nbuckets == 0)
		return NULL;
	h = malloc(sizeof(*h));
	if (!h)
		return NULL;
	h->buckets = calloc(nbuckets, sizeof(*h->buckets));
	if (!h->buckets) {
		free(h);
		return NULL;
	}
	h->nbuckets = nbuckets;
	h->nitems = 0;
	return h;
}

void
ht_free(Hashtab *h)
{
	size_t i;
	struct node *n, *next;

	if (!h)
		return;
	for (i = 0; i < h->nbuckets; i++) {
		for (n = h->buckets[i]; n; n = next) {
			next = n->next;
			free(n->key);
			free(n);
		}
	}
	free(h->buckets);
	free(h);
}

static struct node **
find_slot(const Hashtab *h, const char *key, size_t *idx)
{
	struct node **pp;

	*idx = fnv1a(key) % h->nbuckets;
	for (pp = (struct node **)&h->buckets[*idx]; *pp; pp = &(*pp)->next) {
		if (strcmp((*pp)->key, key) == 0)
			return pp;
	}
	return NULL;
}

int
ht_insert(Hashtab *h, const char *key)
{
	size_t idx;
	struct node *n;

	if (find_slot(h, key, &idx))
		return 0; /* already present */

	n = malloc(sizeof(*n));
	if (!n)
		return -1;
	n->key = strdup(key);
	if (!n->key) {
		free(n);
		return -1;
	}
	n->next = h->buckets[idx];
	h->buckets[idx] = n;
	h->nitems++;
	return 1;
}

int
ht_search(const Hashtab *h, const char *key)
{
	size_t idx;
	return find_slot(h, key, &idx) != NULL;
}

int
ht_delete(Hashtab *h, const char *key)
{
	size_t idx;
	struct node **pp, *victim;

	pp = find_slot(h, key, &idx);
	if (!pp)
		return 0;
	victim = *pp;
	*pp = victim->next;
	free(victim->key);
	free(victim);
	h->nitems--;
	return 1;
}

size_t
ht_size(const Hashtab *h)
{
	return h ? h->nitems : 0;
}
