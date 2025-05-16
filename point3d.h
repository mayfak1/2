#ifndef POINT3D_H
#define POINT3D_H
#include "atomstruct.h"
#include <math.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

typedef struct {

  alignas(8) Atom *atom;
  alignas(8) double a;
  alignas(8) char t;
  alignas(8) int q;
  alignas(8) double b;
  alignas(8) double c;
} Point3d;

void print_point(Point3d *, unsigned int *);
void set_point(Point3d *, double, double, double);
void comparison_points(Point3d *, Point3d *);
Point3d *constructor(double, double, double);
Point3d *constructor_def();
void destructor(Point3d *);
Point3d *point_in();
Point3d *copy_point(Point3d *);
void search_distance(Point3d *, Point3d *);
void displacement_point(Point3d *, double, double, double);
Point3d *rand_point();
void leveling_atom(Point3d *);
#endif