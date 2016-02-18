#include <math.h>
#include <iostream>
#include <sstream>

#include "kmeans.h"

double euclidean_distance(double *x, double *y) {
  double result = 0;

  for (int i = 0; i < sizeof(x); i++) {
    result += (x[i] - y[i]) * (x[i] - y[i]);
  }

  return sqrt(result);
}

void print_data_point(DataPoint point) {
  std::ostringstream stream;
  stream << point.attr[0];
  for (int i = 1; i < point.n; i++) {
    stream << ", ";
    stream << point.attr[i];
  }

  std::cout << "Dimensions: " << point.n << " Attributes: " << stream.str()
            << " Cluster id: " << point.k << std::endl;
}

int main() {
  double a[] = {1, 2, 0, 4, 5, 6, 7, 8, 0};
  double b[] = {1, 2, 3, 4, 5, 6, 99, 8, 9};

  double dist = euclidean_distance(a, b);
  std::cout << "distance is " << dist << std::endl;
}
