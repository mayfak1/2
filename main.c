
#include "fiodict.h"
#define DEF 0xffff
#define COUNT_EL 100
int main(int argc, char *argv[])
{
  unsigned int *val = malloc(sizeof(unsigned int));
  *val = DEF;
  FILE *f;

  srand(time(NULL));

  switch (**(argv + 1))
  {
  case 's':
  {
    mkDict *dt = rand_gen_struct_in_container(COUNT_EL, val);

    if (argc > 2)
    {
      f = fopen(*(argv + 2), "w+");
      if (f == NULL)
        exit(EXIT_FAILURE);
    }
    else
      exit(EXIT_FAILURE);
    save_def(f, dt, val);
    dict_free(dt);

    // if (argc > 2)
    // {
    //   f = fopen(*(argv + 2), "wb");
    //   if (f == NULL)
    //     exit(EXIT_FAILURE);
    // }
    // else
    //   exit(EXIT_FAILURE);
    // save_bin(f, dt, val);
    // dict_free(dt);
    break;
  }
  case 'l':
  {
    if (argc > 2)
    {
      f = fopen(*(argv + 2), "r");
      if (f == NULL)
        exit(EXIT_FAILURE);
    }
    else
      exit(EXIT_FAILURE);
    if (*(*(argv + 1) + 1) == 'o')
    {

      mkDict *dict = load_def(f, val, COUNT_EL);
      mkPair *cur = get_head(dict);
      dict_feach(dict);
      printf("%s \t %f\n", (char *)cur->key, ((Point3d *)cur->value)->a);
      printf("remove key0\n");
      dict_remove(dict, "key0");
      dict_feach(dict);
      free(dict);
    }
    if (*(*(argv + 1) + 1) == 'i')
    {
      list_f(f, val, COUNT_EL);
    }

    // if (argc > 2)
    // {
    //   f = fopen(*(argv + 2), "rb");
    //   if (f == NULL)
    //     exit(EXIT_FAILURE);
    // }
    // else
    //   exit(EXIT_FAILURE);
    // mkDict *dt = load_bin(f, val);
    // mkPair *cur = get_head(dt);
    // dict_feach(dt);
    // printf("%s \t %f\n", (char *)cur->key, ((Point3d *)cur->value)->a);
    // printf("remove key0\n");
    // dict_remove(dt, "key0");
    // dict_feach(dt);
    // free(dt);

    break;
  }

  case 'g':
  {
    if (argc > 2)
    {
      f = fopen(*(argv + 3), "r");
      if (f == NULL)
        exit(EXIT_FAILURE);
    }
    else
      exit(EXIT_FAILURE);

    int n = argc > 3 ? atoi(argv[2]) : 0;
    get_element_from_text_file(f, n);

    // if (argc > 2)
    // {
    //   f = fopen(*(argv + 3), "rb");
    //   if (f == NULL)
    //     exit(EXIT_FAILURE);
    // }
    // else
    //   exit(EXIT_FAILURE);
    // int n = argc > 1 ? atoi(argv[2]) : 0;
    // // int el_size = argc > 3 ? atoi(argv[3]) : 0;
    // get_element_from_binar_file(f, n, 64, val, COUNT_EL);
    // break;
  }
  default:
    break;
  }

  if (fclose(f) != 0)
    printf("Ошибка закрытия файла");

  free(val);
  // mkDict *dict2 = dict_create();

  // dict_put(dict, (void *)"afa", (void *)"friendly_thug_52");
  // dict_put(dict, (void *)"hahgasl", (void *)"Whole Lotta Swag");
  // dict_put(dict, (void *)"4hird", (void *)"whole");
  // dict_put(dict, (void *)"2hird", (void *)"whole");
  // dict_put(dict, (void *)"523", (void *)"whole");
  // dict_put(dict, (void *)"5hird", (void *)"SALAM");
  // dict_put(dict2, (void *)"brat", (void *)"what?????????");

  // printf("original dict:----------------------------\n");
  // dict_feach(dict);

  // mkDict *dict3 = dict_copy(dict);
  // printf("copy in dict3:---------------------------------\n");
  // printf("remove second el from coppied dict3\n");
  // dict_remove(dict3, (void *)"hahgasl");
  // dict_feach(dict3);

  // void *val = dict_get_val(dict2, "brat");
  // printf("get_val: %s\n", (char *)val);

  // bool cont_k = dict_cont_key(dict, "2hird");
  // bool empty = dict_is_empty(dict);
  // printf("is_empty: %d\n", empty);
  // printf("cont_k: %d\n", cont_k);

  // dict_merge(dict, dict2);
  // dict_feach(dict2);
  // dict_remove(dict2, (void *)"afa");
  // printf("after remove:\n");
  // dict_feach(dict2);
  // hash(dict2, 1);

  // bool cl = clear(dict);
  // printf("clear:%d\n", cl);
  // dict_put(dict, (void *)"523", (void *)"whole");

  // dict_feach(dict);
  // int sz = return_size(dict2);
  // printf("size:%d\n", sz);

  // void **arrk = dkey(dict2);
  // void **arrv = dval(dict2);

  // printf("check dkey:%s\n", (char *)*(arrk + 4));
  // printf("check dval:%s\n", (char *)*(arrv + 4));

  // mkPair *hd = get_head(dict2);
  // printf("iterator head:%s\n", (char *)hd->value);

  // mkPair *next = get_next(hd);
  // printf("iterator next:%s\n", (char *)next->value);

  // mkPair *v = dict_get_key(dict2, "Whole Lotta Swag");
  // printf("get_key from val:%s\n", (char *)v->value);

  // mkPair *k = dict_get_val_it(dict2, "brat");
  // printf("get_val_it from val:%s\n", (char *)k->value);

  // dict_free(dict2);
  // dict_free(dict3);

  // free(arrv);
  // free(arrk);
  return 0;
}
