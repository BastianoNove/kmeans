#include <math.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <limits>

#include <string.h>

#include "kmeans.h"

bool verbose = false;

double euclidean_distance(const DataPoint x, const DataPoint y) {
  double result = 0;

  for (int i = 0; i < x.n; i++) {
    result += (x.attr[i] - y.attr[i]) * (x.attr[i] - y.attr[i]);
  }

  return sqrt(result);
}

void print_data_point(const DataPoint point) {
  std::ostringstream stream;
  stream << point.attr[0];
  for (int i = 1; i < point.n; i++) {
    stream << ", ";
    stream << point.attr[i];
  }

  std::cout << stream.str() << ", " << point.k << std::endl;
}

void print_data_points(const std::vector<DataPoint> points) {
  for (std::vector<DataPoint>::const_iterator it = points.begin();
       it != points.end(); it++) {
    print_data_point(*it);
  }
}

void kmeans(std::vector<DataPoint> data_points, int k) {
  std::vector<DataPoint> centroids = initial_centroids(data_points, k);

  int changed = data_points.size();
  double done_threshold = (k * 0.10 * data_points.size());

  while (changed > done_threshold) {
    changed = 0;

    for (std::vector<DataPoint>::iterator it = data_points.begin();
         it != data_points.end(); ++it) {
      assign_closest(centroids, *it, changed);
    }

    // Memory leak. Delete attr of old, synthetic, centroids
    centroids = recompute_centroids(data_points, centroids);
  }

  print_data_points(centroids);
  print_data_points(data_points);
}

std::vector<DataPoint> initial_centroids(std::vector<DataPoint> points, int k) {
  // Build a sample of points
  std::random_shuffle(points.begin(), points.end());
  int sample_size =
      (points.size() * 0.20) > k ? (points.size() * 0.20) : points.size();
  std::vector<DataPoint>::const_iterator first = points.begin();
  std::vector<DataPoint>::const_iterator last = points.begin() + sample_size;
  std::vector<DataPoint> sample(first, last);

  std::vector<DataPoint> centroids;

  // Pick a random centroid first
  int index = std::rand() % sample.size();
  DataPoint centroid = sample[index];
  sample.erase(sample.begin() + index);
  centroids.push_back(centroid);

  // Build list of centroids by always choosing the point
  // farthest apart from the current centroid
  while (centroids.size() < k) {
    std::vector<DataPoint>::iterator max = sample.begin();
    double maxDistance = euclidean_distance(centroid, *max);

    for (std::vector<DataPoint>::iterator it = sample.begin() + 1;
         it != sample.end(); ++it) {
      double distance = euclidean_distance(centroid, *it);
      if (distance > maxDistance) {
        max = it;
        maxDistance = distance;
      }
    }
    centroid = *max;
    centroids.push_back(centroid);
    sample.erase(max);
  }

  for (std::vector<DataPoint>::iterator it = centroids.begin();
       it != centroids.end(); ++it) {
    int index = std::distance(centroids.begin(), it);
    it->k = index + 1;
  }

  if (verbose) {
    std::cout << "Initial Centroids " << std::endl;
    print_data_points(centroids);
  }

  return centroids;
}

void assign_closest(std::vector<DataPoint> centroids, DataPoint &point,
                    int &changed) {
  for (std::vector<DataPoint>::iterator it = centroids.begin();
       it != centroids.end(); ++it) {
    if (same_attributes(point, *it)) {
      point.distance = 0;
      point.k = it->k;
      continue;
    }

    double distance = euclidean_distance(point, *it);
    if (point.distance > distance) {
      point.k = it->k;
      point.distance = distance;
      changed++;
    }
  }
}

bool same_attributes(DataPoint x, DataPoint y) {
  for (int i = 0; i < x.n; i++) {
    if (x.attr[i] != y.attr[i]) {
      return false;
    }
  }

  return true;
}

std::vector<DataPoint> recompute_centroids(std::vector<DataPoint> data_points,
                                           std::vector<DataPoint> centroids) {
  std::vector<DataPoint> new_centroids;

  for (std::vector<DataPoint>::iterator centroid_it = centroids.begin();
       centroid_it != centroids.end(); ++centroid_it) {
    DataPoint new_centroid;
    initialize(new_centroid, centroid_it->k, centroid_it->n);

    int points_assigned_k = 0;
    for (std::vector<DataPoint>::iterator point_it = data_points.begin();
         point_it != data_points.end(); ++point_it) {
      if (new_centroid.k == point_it->k) {
        points_assigned_k++;
        for (int i = 0; i < new_centroid.n; ++i) {
          new_centroid.attr[i] += point_it->attr[i];
        }
      }
    }

    // normalize new centroid
    if (points_assigned_k != 0) {
      for (int i = 0; i < new_centroid.n; ++i) {
        new_centroid.attr[i] = new_centroid.attr[i] / points_assigned_k;
      }
    }

    new_centroids.push_back(new_centroid);
  }

  if (verbose) {
    std::cout << std::endl << "New centroids " << std::endl;
    print_data_points(new_centroids);
  }

  return new_centroids;
}

void initialize(DataPoint &point, int k, int n) {
  point.k = k;
  point.n = n;
  point.distance = 0;
  point.attr = new double[point.n];

  for (int i = 0; i < point.n; ++i) {
    point.attr[i] = 0;
  }
}

void print_usage(char *name) {
  std::cout << "Incorrect number of arguments" << std::endl;
  std::cout << "Correct usage: " << name << " <data_file> <clusters>"
            << std::endl;
  std::cout << "Example: " << name << " points.txt 3" << std::endl;
  std::cout << "For verbose output use -v or -verbose: " << name
            << " points.txt 3 -verbose" << std::endl;
}

int main(int argc, char *argv[]) {
  if (argc < 3) {
    print_usage(argv[0]);
    exit(1);
  }

  if (argc == 4) {
    if (strncmp(argv[3], "-verbose", 8) == 0 ||
        strncmp(argv[3], "-v", 2) == 0) {
      verbose = true;
    } else {
      print_usage(argv[0]);
      exit(1);
    }
  }

  std::fstream data_file(argv[1]);

  if (data_file.peek() == std::fstream::traits_type::eof()) {
    exit(1);
  }

  int dimensions;
  int number_of_points;
  int clusters = atoi(argv[2]);

  data_file >> dimensions;
  data_file >> number_of_points;

  std::vector<DataPoint> points;

  for (int n = 0; n < number_of_points; ++n) {
    double *attributes = new double[dimensions];
    for (int i = 0; i < dimensions; ++i) {
      data_file >> attributes[i];
    }

    DataPoint point;
    point.n = dimensions;
    point.attr = attributes;
    point.distance = std::numeric_limits<double>::infinity();
    points.push_back(point);
  }

  if (verbose) {
    std::cout << "Finding  " << clusters << " clusters" << std::endl;
    std::cout << "Points read: " << points.size() << std::endl;
    print_data_points(points);
  }

  kmeans(points, clusters);
}
