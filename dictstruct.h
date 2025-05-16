#pragma once
#include "point3d.h"
#include <stdbool.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
typedef struct mkPair
{
  void *key;
  void *value;
  struct mkPair *next;
} mkPair;

typedef struct
{
  mkPair *head;
  int size;
} mkDict;

mkDict *dict_create();
void dict_free(mkDict *);
void dict_put(mkDict *, void *, void *);
void *dict_get_val(mkDict *, void *);
bool dict_cont_key(mkDict *, void *);
bool dict_is_empty(mkDict *);
void dict_remove(mkDict *, void *);
bool clear(mkDict *);
int return_size(mkDict *);
void **dkey(mkDict *);
void **dval(mkDict *);
int hash(mkDict *, int);
void dict_merge(mkDict *, mkDict *);
void dict_feach(mkDict *);
mkDict *dict_copy(mkDict *);

mkPair *get_head(mkDict *);
mkPair *get_next(mkPair *);
mkPair *dict_get_key(mkDict *, void *);
mkPair *dict_get_val_it(mkDict *, void *);
