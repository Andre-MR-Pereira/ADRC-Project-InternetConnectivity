cmake_minimum_required(VERSION 3.17)
project(ADRC_Project_InternetConnectivity C)

set(CMAKE_C_STANDARD 11)

add_executable(ADRC_Project_InternetConnectivity main.c lib/Graph_module/ISPs.c lib/Graph_module/graph.c lib/Graph_module/Search.c lib/Graph_module/Stacks.c lib/Graph_module/SearchCommercial.c lib/Graph_module/SearchCommercial.h)