cmake_minimum_required(VERSION 3.16)

project(Factorial LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

include_directories(./include)

# target_sources(Factorial
#   PRIVATE
#     src/main.cpp
# )

file(GLOB SOURCES "src/*.cpp")

add_executable(Factorial ${SOURCES}
  include/verylong.h)

include(GNUInstallDirs)
install(TARGETS Factorial
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
