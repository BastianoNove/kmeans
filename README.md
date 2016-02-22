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
`./bin/kmeans data/second_sample.txt 5 > data/second_sample_clusters.txt`

`./plot data/second_sample_clusters.txt`
