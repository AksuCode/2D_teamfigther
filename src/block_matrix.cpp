#include "./block_matrix.hpp"

BlockMatrix::BlockMatrix(size_t rows, size_t cols) : rows_(rows), cols_(cols) {
    size_t block_byte_size = sizeof(Block);
    size_t row_size = cols * block_byte_size;

    // Compute aligned row size
    size_t padding_size = (CACHE_LINE_BYTE_SIZE - (row_size % CACHE_LINE_BYTE_SIZE)) % CACHE_LINE_BYTE_SIZE;
    size_t aligned_row_size = row_size + padding_size;
    stride_ = aligned_row_size / block_byte_size;

    // Allocate aligned memory
    void* raw_memory = std::aligned_alloc(CACHE_LINE_BYTE_SIZE, rows * aligned_row_size);
    if (raw_memory == nullptr) { exit(-1); }
    Block* blocks_ = static_cast<Block*>(raw_memory);
}

BlockMatrix::~BlockMatrix() {
    std::free(blocks_);
}