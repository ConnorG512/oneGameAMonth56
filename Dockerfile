# Stage 1 as build
FROM fedora:latest AS builder
RUN dnf install -y \
  gcc \
  gcc-c++ \
  cmake \
  ninja-build \
  pkgconf-pkg-config \
  SDL3-devel \
  SDL3_image-devel \
  SDL3_sound-devel \
  SDL3_ttf-devel \
  lua-devel

WORKDIR /build-src
COPY . .
RUN cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release  && cmake --build build

# Stage 2 as Exporter
FROM scratch AS exporter
COPY --from=builder /build-src/build/oneGameAMonth /

# CMD ["/bin/bash"]
