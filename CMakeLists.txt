cmake_minimum_required(VERSION 3.16)

project(MyApp VERSION 0.1.0 LANGUAGES CXX)

add_executable(myapp
  main.cpp
)

target_compile_features(myapp PRIVATE cxx_std_17)

# fmt (via package manager zoals vcpkg / system package)
find_package(fmt CONFIG REQUIRED)

# pigpio
find_library(PIGPIO_LIB NAMES pigpio REQUIRED)

target_link_libraries(myapp PRIVATE
  fmt::fmt
  ${PIGPIO_LIB}
  pthread
  rt
)
