#include "./block_matrix.hpp"

BlockMatrix::BlockMatrix(int width, int heigth) : width_(width), heigth_(heigth) {
    int block_byte_size = sizeof(Block);
    int column_size = heigth * block_byte_size;

    int padding_size = (CACHE_LINE_BYTE_SIZE - (column_size % CACHE_LINE_BYTE_SIZE)) % CACHE_LINE_BYTE_SIZE;
    int aligned_column_size = column_size + padding_size;
    stride_ = aligned_column_size / block_byte_size;

    // Allocate aligned memory
    void* raw_memory = std::aligned_alloc(CACHE_LINE_BYTE_SIZE, width * aligned_column_size);
    if (raw_memory == nullptr) { exit(-1); }
    Block* blocks_ = static_cast<Block*>(raw_memory);
}

BlockMatrix::~BlockMatrix() {
    std::free(blocks_);
}