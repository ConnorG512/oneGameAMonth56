# Stage 1 as build
FROM fedora:latest AS builder
RUN dnf install -y \
  gcc \
  gcc-c++ \
  cmake \
  ninja-build \
  pkgconf-pkg-config \
  mingw64-gcc \
  mingw64-gcc-c++ \
  mingw64-SDL3 \
  mingw64-SDL_image \
  #mingw64-SDL_sound \
  mingw64-SDL_ttf \
  #mingw64-lua \
  && dnf clean all

WORKDIR /build-src
COPY . .
RUN mingw64-cmake -B build-win -S . -G Ninja -DCMAKE_BUILD_TYPE=Release  && cmake --build build-win

# Stage 2 as Exporter
FROM scratch AS exporter
COPY --from=builder /build-src/build/oneGameAMonth /

# CMD ["/bin/bash"]
