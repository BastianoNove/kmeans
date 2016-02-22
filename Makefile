all:
	@mkdir -p bin
	llvm-g++ kmeans.cpp -o bin/kmeans
