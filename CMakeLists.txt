cmake_minimum_required(VERSION 3.9)
project(Huffman_compression_Decompression)

set(CMAKE_CXX_STANDARD 11)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_SOURCE_DIR})

add_executable(Huffman_compression_Decompression main.cpp Huffman.cpp Huffman.h Node.h Files.cpp Files.h)
