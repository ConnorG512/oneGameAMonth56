FROM fedora:latest

RUN dnf install -y \
  gcc \
  cmake \
  ninja-build \
  pkgconf-pkg-config \
  SDL3-devel \
  SDL3_image-devel \
  SDL3_sound-devel \
  SDL3_ttf-devel \
  lua

WORKDIR /app

COPY . .

RUN cmake -B build -S . -DCMAKE_BUILD_TYPE=Release 
RUN cmake --build build

CMD ["/bin/bash"]
