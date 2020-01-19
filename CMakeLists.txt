cmake_minimum_required( VERSION 3.7)
project (mygame)
list(APPEND CMAKE_MODULE_PATH ${CMAKE_CURRENT_SOURCE_DIR}/cmake/sdl2)
find_package (SDL2 REQUIRED)
find_package (ZLIB REQUIRED)
find_package (SDL2_image REQUIRED)
include_directories (
  ${PROJECT_SOURCE_DIR}/2D
  ${PROJECT_SOURCE_DIR}/Armory
  ${PROJECT_SOURCE_DIR}/Fuzzy
  ${PROJECT_SOURCE_DIR}/Game
  ${PROJECT_SOURCE_DIR}/Goals
  ${PROJECT_SOURCE_DIR}/Graph
  ${PROJECT_SOURCE_DIR}/Messaging
  ${PROJECT_SOURCE_DIR}/misc
  ${PROJECT_SOURCE_DIR}/Navigation
  ${PROJECT_SOURCE_DIR}/Time
  ${PROJECT_SOURCE_DIR}/Triggers)

file(GLOB all_SRCS
  "${PROJECT_SOURCE_DIR}/*.h"
  "${PROJECT_SOURCE_DIR}/*.cpp"
  "${PROJECT_SOURCE_DIR}/2D/*.h"
  "${PROJECT_SOURCE_DIR}/2D/*.cpp"
  "${PROJECT_SOURCE_DIR}/Armory/*.h"
  "${PROJECT_SOURCE_DIR}/Armory/*.cpp"
  "${PROJECT_SOURCE_DIR}/Fuzzy/*.h"
  "${PROJECT_SOURCE_DIR}/Fuzzy/*.cpp"
  "${PROJECT_SOURCE_DIR}/Game/*.h"
  "${PROJECT_SOURCE_DIR}/Game/*.cpp"
  "${PROJECT_SOURCE_DIR}/Goals/*.h"
  "${PROJECT_SOURCE_DIR}/Goals/*.cpp"
  "${PROJECT_SOURCE_DIR}/Graph/*.h"
  "${PROJECT_SOURCE_DIR}/Graph/*.cpp"
  "${PROJECT_SOURCE_DIR}/Messaging/*.h"
  "${PROJECT_SOURCE_DIR}/Messaging/*.cpp"
  "${PROJECT_SOURCE_DIR}/misc/*.h"
  "${PROJECT_SOURCE_DIR}/misc/*.cpp"
  "${PROJECT_SOURCE_DIR}/Navigation/*.h"
  "${PROJECT_SOURCE_DIR}/Navigation/*.cpp"
  "${PROJECT_SOURCE_DIR}/Time/*.h"
  "${PROJECT_SOURCE_DIR}/Time/*.cpp"
  "${PROJECT_SOURCE_DIR}/Triggers/*.h"
  "${PROJECT_SOURCE_DIR}/Triggers/*.cpp"
  )
add_executable(mygame ${all_SRCS})
target_compile_options (mygame PRIVATE -g -w)
target_link_libraries (mygame SDL2::Main SDL2::Image ${ZLIB_LIBRARIES} -ggdb3)
