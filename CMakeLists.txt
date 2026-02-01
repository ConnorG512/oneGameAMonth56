cmake_minimum_required(VERSION 3.28)
project(OneGameAMoth56 CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(EXEC_NAME oneGameAMoth)

set(SOURCE_FILES 
  src/main.cpp
  src/sdl/init.cpp
)

add_executable(${EXEC_NAME} ${SOURCE_FILES})

target_compile_options(${EXEC_NAME} PRIVATE
  -Wall
  -Wextra
  -Wpedantic
)

if(CMAKE_BUILD_TYPE STREQUAL "Debug" AND UNIX AND NOT APPLE)
  target_compile_options(${EXEC_NAME} PRIVATE 
    -fsanitize=address,undefined
    -ggdb
  )
  target_link_options(${EXEC_NAME} PRIVATE 
    -fsanitize=address,undefined
  )
endif()

find_package(SDL3 REQUIRED)
target_link_libraries(${EXEC_NAME} PRIVATE
  SDL3::SDL3
)


target_include_directories(${EXEC_NAME} PRIVATE "${CMAKE_SOURCE_DIR}/include")

install(TARGETS ${EXEC_NAME} RUNTIME DESTINATION bin)
