#include "main.h"

int main() {
  Polynomial* p1 = polynomialRead("input.txt");
  Polynomial* p2 = polynomialMul(p1, polynomialParse("1 -7 1"));
  p2 = polynomialMulInt(p2, 2);
  p2 = polynomialSum(p2, polynomialParse("2 2 3"));
  p2 = polynomialSub(p2, polynomialParse("2 3 1 5 10 3"));

  polynomialWrite("output.txt", p2);

  return 0;
}
