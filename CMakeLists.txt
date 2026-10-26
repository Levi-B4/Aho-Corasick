cmake_minimum_required(VERSION 3.16)

project(AhoCSearch LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

add_executable(AhoCSearch main.cpp
    ahoCorasick.h ahoCorasick.cpp)

include(GNUInstallDirs)
install(TARGETS AhoCSearch
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
