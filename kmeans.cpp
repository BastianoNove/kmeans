#include <math.h>
#include <iostream>
#include <vector>

#include "kmeans.h"

double euclidean_distance(double *x, double *y) {
  double result = 0;

  for (int i = 0; i < sizeof(x); i++) {
    result += (x[i] - y[i]) * (x[i] - y[i]);
  }

  return sqrt(result);
}

int main() {
  double a[] = {1, 2, 0, 4, 5, 6, 7, 8, 0};
  double b[] = {1, 2, 3, 4, 5, 6, 99, 8, 9};

  double dist = euclidean_distance(a, b);
  std::cout << "distance is " << dist << std::endl;
}
