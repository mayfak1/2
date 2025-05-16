
#include "point3d.h"
Atom *constructor_atom(unsigned int *val, unsigned int n, unsigned int g,
                       unsigned int l, unsigned int m)
{
  Atom *atom1 = malloc(sizeof(Atom));
  set_number_atom(val, n);
  set_group_atom(val, g);
  set_line_atom(val, l);
  set_metals_atom(val, m);
  atom1->number = (*val) & NUMBER_MASK;
  atom1->group = ((*val) & GROUP_MASK) >> GROUP_MASK_SHIFT;
  atom1->line = ((*val) & LINE_MASK) >> LINE_MASK_SHIFT;
  atom1->metal = ((*val) & METAL_MASK) >> METAL_MASK_SHIFT;

  return atom1;
}

int set_number_atom(unsigned int *full_val, int num_val)
{
  if (num_val > 118 || num_val < 0)
  {
    printf("некорректные данные для n диапазон 0..118");
    return 1;
  }
  *full_val = ((*full_val & ~NUMBER_MASK) | ((num_val)&NUMBER_MASK));
  return 0;
}
int set_group_atom(unsigned int *full_val, int num_val)
{
  if (num_val > 18 || num_val < 0)
  {
    printf("некорректные данные для g диапазон 0..18");
    return 1;
  }
  *full_val = ((*full_val & ~GROUP_MASK)) |
              ((num_val << GROUP_MASK_SHIFT) & GROUP_MASK);
  return 0;
}
int set_line_atom(unsigned int *full_val, int num_val)
{
  if (num_val > 7 || num_val < 0)
  {
    printf("некорректные данные для l диапазон 0..7");
    return 1;
  }
  *full_val =
      ((*full_val & ~LINE_MASK)) | ((num_val << LINE_MASK_SHIFT) & LINE_MASK);
  return 0;
}
int set_metals_atom(unsigned int *full_val, int num_val)
{
  if (num_val > 1 || num_val < 0)
  {
    printf("некорректные данные для l диапазон 0..1");
    return 1;
  }
  *full_val = ((*full_val & ~METAL_MASK)) |
              ((num_val << METAL_MASK_SHIFT) & METAL_MASK);
  return 0;
}
void destructor_atom(Atom *atom1)
{
  atom1->number = 0;
  atom1->group = 0;
  atom1->line = 0;
  atom1->metal = 0;
  free(atom1);
}

void leveling_atom(Point3d *p)
{
  printf("Size: %zu\n", sizeof(Point3d));
  // printf("atom align%zu\n",_Alignof(Atom));
  // printf("Atom number:%zu байт \n", sizeof(Atom));

  printf("Size A : %zu\n", sizeof(Atom));
  printf("atom:%zu байт \n", sizeof(p->atom));
  printf("a:%zu байт \n", sizeof(p->a));
  printf("t:%zu байт \n", sizeof(p->t));
  printf("q:%zu байт \n", sizeof(p->q));
  printf("b:%zu байт \n", sizeof(p->b));
  printf("c:%zu байт \n", sizeof(p->c));
  // sprintf("atom:%p\n", &(p->atom))c;
  printf("atom:%p\n", &((p->atom)));
  printf("a:%p\n", &((p->a)));
  printf("t:%p\n", &(p->t));
  printf("q:%p\n", &(p->q));
  printf("b:%p\n", &(p->b));

  printf("c:%p\n", &(p->c));
}

// int show_atom(int def){
//     if ()
// }

void rand_atom(unsigned int *val)
{

  set_number_atom(val, (rand() % 118));
  set_group_atom(val, rand() % 18);
  set_line_atom(val, rand() % 7);
}