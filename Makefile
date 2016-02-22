all:
	@mkdir -p bin
	llvm-g++ src/kmeans.cpp -o bin/kmeans

clean:
	rm bin/*
