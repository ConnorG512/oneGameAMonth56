local-build-release:
	cmake -B build-release -S . -G Ninja -DCMAKE_BUILD_TYPE=Release
	cmake --build build

local-build-debug:
	cmake -B build-debug -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

docker-build:
	mkdir -p docker-out
	docker build --target exporter --output ./docker-out . 

