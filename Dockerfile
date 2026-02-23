FROM fedora:latest

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

WORKDIR /app

COPY . .

RUN cmake -B build -S . -G Ninja -DCMAKE_BUILD_TYPE=Release  && cmake --build build

# Finaly command when running the container.
CMD ["/bin/bash"]
