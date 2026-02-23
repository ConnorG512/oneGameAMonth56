cmake_minimum_required(VERSION 3.28)
project(OneGameAMonth56 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC_NAME oneGameAMonth)

set(SOURCE_FILES 
  src/main.cpp
  src/sdl/init.cpp
  src/sdl/text/text.cpp
  src/sdl/display/window.cpp
  src/sdl/display/renderer.cpp
  src/sdl/display/display.cpp
  src/sdl/image/texture.cpp
  src/sdl/rectangle.cpp
  src/sdl/event-handler.cpp
  src/sdl/input/mouse.cpp
  src/sdl/audio/audio.cpp
  src/file-out/logger.cpp
  src/file-out/binary.cpp
  src/game/player.cpp
  src/game/enemy.cpp
  src/game/projectile.cpp
  src/lua/lua.cpp
  src/filesystem/file-check.cpp
  src/game/rules.cpp
  src/game/score.cpp
  src/game/ui-layout.cpp
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
pkg_check_modules(SDL3_TTF_PKG REQUIRED
  sdl3-ttf
)

target_link_libraries(${EXEC_NAME} PRIVATE
  SDL3::SDL3
  SDL3_image::SDL3_image
  ${LUA_PKG_LIBRARIES}
  ${SDL3_TTF_PKG_LIBRARIES}
)

target_include_directories(${EXEC_NAME} PRIVATE 
  "${CMAKE_SOURCE_DIR}/include"
  ${LUA_PKG_INCLUDE_DIRS}
  ${SDL3_TTF_PKG_INCLUDE_DIRS}
)

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
