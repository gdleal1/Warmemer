./bin/Linux/main: src/*.cpp include/.
	mkdir -p bin/Linux
	g++ -std=c++11 -Wall -Wno-unused-function -g -I ./include/ -o ./bin/Linux/main src/main.cpp src/Warhammer/Miniatures.cpp src/Warhammer/Armies.cpp src/GastalUtils/shaderUtil.cpp src/Camera/freeCamMove.cpp src/Camera/FreeCamera.cpp src/GastalUtils/ObjModel.cpp src/GastalUtils/SceneBuilder.cpp src/GastalUtils/MatrixStack.cpp src/GastalUtils/glad.c src/Camera/LookAtCamera.cpp src/GastalUtils/textrendering.cpp src/GastalUtils/tiny_obj_loader.cpp src/GastalUtils/stb_image.cpp ./lib-linux/libglfw3.a -lrt -lm -ldl -lX11 -lpthread -lXrandr -lXinerama -lXxf86vm -lXcursor

.PHONY: clean run
clean:
	rm -f bin/Linux/main

run: ./bin/Linux/main
	cd bin/Linux && ./main
