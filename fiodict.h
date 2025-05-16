#pragma once
#include <stdio.h>
#include "ctest.h"
#include "point3d.h"
#include "dictstruct.h"
mkDict *rand_gen_struct_in_container(size_t, unsigned int *);
Point3d **rand_gen_struct(size_t, unsigned int *);
void save_def(FILE *f, mkDict *dt, unsigned int *val);
mkDict *load_def(FILE *f, unsigned int *val, int count_el);
mkDict *load_struct_dict(char **, int, unsigned int *);
void get_element_from_text_file(FILE *, int);
void get_element_from_binar_file(FILE *f, int index, size_t element_size, unsigned int *val, int);
void list_f(FILE *f, unsigned int *val, int);
void save_bin(FILE *f, mkDict *dt, unsigned int *val);
mkDict *load_bin(FILE *f, unsigned int *val);