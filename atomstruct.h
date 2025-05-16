#ifndef ATOMSTRUCT_H
#define ATOMSTRUCT_H
#include <stdalign.h>
#include <mach/mach_time.h>
#define NUMBER_MASK 0x007f
#define GROUP_MASK 0x0f80
#define LINE_MASK 0x7000
#define METAL_MASK 0x8000

#define NUMBER_MASK_SHIFT 0
#define GROUP_MASK_SHIFT 7
#define LINE_MASK_SHIFT 12
#define METAL_MASK_SHIFT 15
// 0000 0000 0000 0000

typedef struct
{
  unsigned int number : 7;
  unsigned int group : 5;
  unsigned int line : 3;
  unsigned int metal : 1;
} Atom;

Atom *constructor_atom(unsigned int *, unsigned int, unsigned int, unsigned int,
                       unsigned int);
void destructor_atom(Atom *);
int set_number_atom(unsigned int *, int);
int set_group_atom(unsigned int *, int);
int set_line_atom(unsigned int *, int);
int set_metals_atom(unsigned int *, int);
double wtime();
void rand_atom(unsigned int *val);
#endif