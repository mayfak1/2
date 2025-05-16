#include "point3d.h"

void set_point(Point3d *p3, double new_a, double new_b, double new_c)
{
  p3->a = new_a;
  p3->b = new_b;
  p3->c = new_c;
}
void print_point(Point3d *p3, unsigned int *val)
{
  printf("%p: A - %f\tB - %f\tC - %f\natom:\tnumber:%d - group:%d - line:%d - "
         "metal:%d \n",
         p3, p3->a, p3->b, p3->c, (*val) & NUMBER_MASK,
         ((*val) & GROUP_MASK) >> GROUP_MASK_SHIFT,
         ((*val) & LINE_MASK) >> LINE_MASK_SHIFT,
         ((*val) & METAL_MASK) >> METAL_MASK_SHIFT);
}
void comparison_points(Point3d *p1, Point3d *p2)
{

  if ((p1->a == p2->a) && (p1->b == p2->b) && (p1->c == p2->c))
  {
    printf("p1==p2\n");
  }
  else
  {
    printf("p1!=p2\n");
  }
}
Point3d *constructor(double a, double b, double c)
{
  Point3d *p1 = malloc(sizeof(Point3d));
  p1->a = a;

  p1->b = b;
  p1->c = c;

  return (p1);
}
Point3d *constructor_def()
{
  Point3d *p1 = malloc(sizeof(Point3d));
  p1->atom = NULL;
  p1->a = 0;
  p1->b = 0;
  p1->c = 0;
  return p1;
}
void destructor(Point3d *p)
{
  p->atom = NULL;
  p->a = 0;
  p->b = 0;
  p->c = 0;
  free(p);
}

Point3d *point_in()
{
  Point3d *p1 = malloc(sizeof(Point3d));
  scanf("%lf", &(p1->a));
  scanf("%lf", &(p1->b));
  scanf("%lf", &(p1->c));
  return (p1);
}

Point3d *copy_point(Point3d *p)
{
  Point3d *p1 = malloc(sizeof(Point3d));
  p1->a = p->a;
  p1->b = p->b;
  p1->c = p->c;
  return p1;
}
void search_distance(Point3d *p1, Point3d *p2)
{

  double d = pow(((p2->a) - (p1->a)), 2) + pow(((p2->b) - (p1->b)), 2) +
             pow(((p2->c) - (p1->c)), 2);

  double res = sqrt(d);
  printf("distance : %lf\n", res);
}
void displacement_point(Point3d *p, double a, double b, double c)
{
  printf("before: a:%f b:%f c:%f\n", p->a, p->b, p->c);
  p->a = a;
  p->b = b;
  p->c = c;
  printf("after: a:%f b:%f c:%f\n", p->a, p->b, p->c);
}
Point3d *rand_point()
{
  Point3d *p1 = malloc(sizeof(Point3d));

  p1->a = rand() % 1000;
  p1->b = rand() % 1000;
  p1->c = rand() % 1000;
  return (p1);
}
