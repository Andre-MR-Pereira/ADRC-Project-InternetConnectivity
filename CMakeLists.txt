cmake_minimum_required(VERSION 3.17)
project(ADRC_Project_InternetConnectivity C)

set(CMAKE_C_STANDARD 11)

add_executable(ADRC_Project_InternetConnectivity main.c lib/Graph_module/ISPs.c lib/Graph_module/graph.c lib/Algorithm_modules/Search.c lib/Graph_module/Stacks.c lib/Algorithm_modules/SearchCommercial.c lib/Algorithm_modules/Connected.c lib/Algorithm_modules/biconnected.c menus.c lib/Algorithm_modules/FindCycles.c lib/Algorithm_modules/FindCycles.h lib/Graph_module/Heap.c lib/Graph_module/Heap.h lib/Algorithm_modules/PathType.c lib/Algorithm_modules/PathLength.c)
