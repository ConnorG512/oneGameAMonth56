local-build-release:
	cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release
	cmake --build build

local-build-debug:
	cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Debug
	cmake --build build

docker-build:
	docker build -t onegameamonth56 .

docker-run:
	docker build -t onegameamonth56 .
