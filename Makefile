all: make-src

make-src: build
	$(MAKE) -C src

build:
	mkdir build

clean:
	rm -rf build src/*.o src/*.d src/libdgl.so src/dgl-server src/*.inc

test-avg-speed: make-src
	./scripts/test-avg-speed.sh
