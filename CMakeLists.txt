cmake_minimum_required(VERSION 3.28)
project(OneGameAMonth56 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC_NAME oneGameAMonth)

set(SOURCE_FILES 
  src/main.cpp
  src/sdl/init.cpp
  src/sdl/window-renderer/window.cpp
  src/sdl/window-renderer/renderer.cpp
  src/sdl/window-renderer/window-renderer.cpp
  src/sdl/image/texture.cpp
  src/sdl/rectangle.cpp
  src/sdl/event-handler.cpp
  src/sdl/input/mouse.cpp
  src/file-output/logging/logger.cpp
  src/file-output/binary/binary.cpp
  src/game/player.cpp
  src/game/enemy.cpp
  src/lua/lua.cpp
)

add_executable(${EXEC_NAME} ${SOURCE_FILES})

target_compile_options(${EXEC_NAME} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND UNIX AND NOT APPLE)
  target_compile_options(${EXEC_NAME} PRIVATE 
    -fsanitize=address,undefined,leak
    -ggdb
  )
  target_link_options(${EXEC_NAME} PRIVATE 
    -fsanitize=address,undefined,leak
  )
endif()

find_package(SDL3 REQUIRED)
find_package(SDL3_image REQUIRED)
find_package(PkgConfig REQUIRED)

pkg_check_modules(LUA_PKG REQUIRED
  lua
)

target_link_libraries(${EXEC_NAME} PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
  ${LUA_PKG_LIBRARIES}
)

target_include_directories(${EXEC_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  ${LUA_PKG_INCLUDE_DIRS}
)

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
