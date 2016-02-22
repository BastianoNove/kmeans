K-Means
-----

Implementation of k-means algorithm.

## Running
Build using `make`.

`./bin/kmeans <data_file> number_of_clusters > cluster_assignments.txt`

## Plotting clusters
Requires gnuplot.

`./plot cluster_assignments.txt`


## Example

5 Clusters:
`./bin/kmeans data/points.txt 3 > data/points_clusters.txt

`./plot data/points_clusters.txt

![plot](https://raw.githubusercontent.com/BastianoNove/kmeans/master/data/third_sample.png)
