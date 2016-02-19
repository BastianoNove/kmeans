#include <vector>

struct DataPoint {
  int n;            // dimensions
  double* attr;     // attributes
  int k;            // cluster id
  double distance;  // distance to k
};

double euclidean_distance(const DataPoint x, const DataPoint y);

void print_data_point(const DataPoint);

void print_data_points(const std::vector<DataPoint>);

void kmeans(std::vector<DataPoint>, int k);

std::vector<DataPoint> initial_centroids(const std::vector<DataPoint>, int k);

void assign_closest(std::vector<DataPoint>, DataPoint&, int&);

bool same_attributes(DataPoint, DataPoint);

std::vector<DataPoint> recompute_centroids(std::vector<DataPoint>,
                                           std::vector<DataPoint>);
void initialize(DataPoint&, int, int);
