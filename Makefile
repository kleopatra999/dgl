all: make-src
	@echo 'NOTE Maybe you want to `make gears` also.'

make-src: build
	$(MAKE) -C src

build:
	mkdir build

clean:
	rm -rf build src/*.o src/*.d src/libdgl.so src/dgl-server src/*.inc

test-avg-speed: make-src
	./scripts/test-avg-speed.sh

gears: all
	./build/dgl es2gears_x11 & ./build/dgl -s local
