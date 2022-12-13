#include "poly.h"

int main()
{
  Polinom *p1 = Polynom_read("data.txt");
  Polinom *p2 = Polynom_parse("1 -7 1");
  Polinom *p3 = Polynom_mul(p1, p2);
  Polynom_destroy(p1);
  Polynom_destroy(p2);
  Polinom *p4 = Polynom_parse("2 2 3");
  Polinom *p5 = Polynom_sum(p3, p4);
  Polynom_destroy(p4);
  Polinom *p6 = Polynom_parse("2 3 1 5 10 3");
  Polinom *p7 = Polynom_sub(p5, p6);
  Polynom_destroy(p5);
  Polynom_destroy(p6);

  Polynom_write("result.txt", p7);

  return 0;
}