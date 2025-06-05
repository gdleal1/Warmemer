./bin/Linux/main: src/*.cpp include/*.h
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/GastalUtils/FreeCamera.cpp src/GastalUtils/ObjModel.cpp src/GastalUtils/SceneBuilder.cpp src/GastalUtils/MatrixStack.cpp src/GastalUtils/glad.c src/GastalUtils/LookAtCamera.cpp src/GastalUtils/textrendering.cpp src/GastalUtils/tiny_obj_loader.cpp src/GastalUtils/stb_image.cpp ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
