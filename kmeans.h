
double euclidean_distance(double x[], double y[]);

struct DataPoint {
  int n;         // dimensions
  double* attr;  // attributes
  int k;         // cluster id
};

void print_data_point(DataPoint);
