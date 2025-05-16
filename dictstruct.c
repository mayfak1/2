#include "dictstruct.h"

mkDict *dict_create()
{
  mkDict *dt = (mkDict *)malloc(sizeof(mkDict));
  if (!dt)
  {
    printf("ALARM from create");
    exit(EXIT_FAILURE);
  }
  dt->head = NULL;
  dt->size = 0;

  return dt;
}
void dict_free(mkDict *dt)
{
  if (!dt)
  {

    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  while (begin)
  {
    mkPair *temp = begin;
    begin = begin->next;
    free(temp->key);
    if (((Point3d *)temp->value)->a != -3)
    {
      destructor_atom((((Point3d *)temp->value)->atom));
      destructor((Point3d *)temp->value);
    }
    else
    {
      free(temp->value);
    }
    free(temp);
  }
  free(dt);
}
void dict_put(mkDict *dt, void *key, void *val)
{
  if (!dt)
  {

    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;

  while (begin)
  {
    if ((begin->key == key) || (!strcmp((char *)begin->key, (char *)key)))
    {
      begin->value = val;
      return;
    }
    begin = begin->next;
  }
  mkPair *new_pair = (mkPair *)malloc(sizeof(mkPair));
  if (!new_pair)
  {
    printf("ALARM from new_pair");
    exit(EXIT_FAILURE);
  }
  new_pair->key = key;
  new_pair->value = val;
  new_pair->next = dt->head;
  dt->head = new_pair;
  dt->size++;

  hash(dt, 0);
}
void *dict_get_val(mkDict *dt, void *key)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;

  if (dict_cont_key(dt, key))
  {
    while (begin)
    {
      if ((begin->key == key) || (!strcmp((char *)begin->key, (char *)key)))
      {
        return begin->value;
      }

      begin = begin->next;
    }
  }
  else
    return NULL;
  return NULL;
}

bool dict_cont_key(mkDict *dt, void *key)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  while (begin)
  {
    if ((begin->key == key) || (!strcmp((char *)begin->key, (char *)key)))
    {
      return true;
    }
    begin = begin->next;
  }
  return false;
}
bool dict_is_empty(mkDict *dt)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  if (dt->size == 0)
    return true;
  return false;
}

void dict_remove(mkDict *dt, void *key)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  mkPair *previous = NULL;
  if (dict_cont_key(dt, key))
  {

    while (begin)
    {
      if ((begin->key == key) || (!strcmp((char *)begin->key, (char *)key)))
      {
        if (previous)
        {
          previous->next = begin->next;
        }
        else
        {
          dt->head = begin->next;
        }
        free(begin);
        dt->size--;
        return;
      }
      previous = begin;
      begin = begin->next;
    }
  }
  else
    return;
}

bool clear(mkDict *dt)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  if (begin)
  {

    while (begin)
    {
      mkPair *temp = begin;
      begin = begin->next;
      free(temp);
      dt->size--;
    }

    dt->head = NULL;
  }
  else
    return 1;

  return 0;
}

int return_size(mkDict *dt)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  return dt->size;
}

void **dkey(mkDict *dt)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  void **arr = malloc(dt->size * sizeof(void *));
  if (!arr)
  {
    exit(EXIT_FAILURE);
  }
  else
  {
    for (int i = 0; i < dt->size; i++)
    {
      *(arr + i) = begin->key;
      begin = begin->next;
    }
  }

  return arr;
}

void **dval(mkDict *dt)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  void **arr = malloc(dt->size * sizeof(void *));
  if (!arr)
  {
    exit(EXIT_FAILURE);
  }
  else
  {
    for (int i = 0; i < dt->size; i++)
    {
      *(arr + i) = begin->value;
      begin = begin->next;
    }
  }

  return arr;
}

int hash(mkDict *dt, int f)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  int ar[dt->size];
  mkPair *begin = dt->head;
  // int count = 0;
  // unsigned int h = 0, hash_mul = 31;
  // for (int i = 0; i < dt->size; i++)
  // {
  //   while (*(char *)begin->key)
  //     h = h * hash_mul + (unsigned int)*(char *)begin->key++;
  //   ar[i] = h % dt->size;
  //   begin = begin->next;
  // }
  for (int i = 0; i < dt->size; i++)
  {
    int res = (uintptr_t)begin->key % dt->size;
    while (1)
    {
      int uniq = 1;
      for (int j = 0; j < i; j++)
      {
        if (ar[j] == res)
        {
          uniq = 0;
          break;
        }
      }
      if (uniq)
        break;
      res = (res + 1) % dt->size;
    }
    ar[i] = res;
  }
  if (f)
  {
    for (int i = 0; i < dt->size; i++)
    {
      printf("%d", ar[i]);
    }
    printf("\n");
  }
  return 0;
}
void dict_merge(mkDict *dt1, mkDict *dt2)
{
  if (!dt1 || !dt2)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt1->head;
  if (begin)
  {
    for (int i = 0; i < dt1->size; i++)
    {
      dict_put(dt2, (void *)begin->key, (void *)begin->value);
      begin = begin->next;
    }
  }
  else
    return;
  clear(dt1);
}
void dict_feach(mkDict *dt)
{
  if (!dt || dt->size == 0)
  {
    exit(EXIT_FAILURE);
  }
  void **val = dval(dt);
  void **key = dkey(dt);
  for (int i = 0; i < dt->size; i++)
  {
    printf("key: %s\t - \t val: %p \n", (char *)*(key + i), (char *)*(val + i));
  }
  free(val);
  free(key);
}
mkDict *dict_copy(mkDict *dt1)
{
  if (!dt1)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt1->head;

  mkDict *dt2 = dict_create();

  if (begin)
  {
    for (int i = 0; i < dt1->size; i++)
    {
      dict_put(dt2, (void *)begin->key, (void *)begin->value);
      begin = begin->next;
    }
  }
  else
    return NULL;

  return dt2;
}
mkPair *get_head(mkDict *dt)
{
  if (!dt || !dt->head)
  {
    exit(EXIT_FAILURE);
  }

  return dt->head;
}
mkPair *get_next(mkPair *current)
{
  if (!current || !current->next)
  {
    exit(EXIT_FAILURE);
  }
  return current->next;
}
mkPair *dict_get_key(mkDict *dt, void *val)
{
  if (!dt)
  {

    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  while (begin)
  {
    if ((begin->value == val) || (!strcmp((char *)begin->value, (char *)val)))
    {
      return begin;
    }
    begin = begin->next;
  }

  return NULL;
}
mkPair *dict_get_val_it(mkDict *dt, void *k)
{
  if (!dt)
  {
    exit(EXIT_FAILURE);
  }
  mkPair *begin = dt->head;
  while (begin)
  {
    if ((begin->key == k) || (!strcmp((char *)begin->key, (char *)k)))
    {
      return begin;
    }
    begin = begin->next;
  }

  return NULL;
}