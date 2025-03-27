#include "./block_world.hpp"

SolidsColumnMajorBitmap::SolidsColumnMajorBitmap(int world_width, int world_heigth) {

    int column_size_in_int_sized_blocks = static_cast<int>(std::ceil(float(world_heigth) / float(sizeof(unsigned int) * 8)));
    int column_size = column_size_in_int_sized_blocks * sizeof(unsigned int);       // In bytes

    int padding_size = (CACHE_LINE_BYTE_SIZE - (column_size % CACHE_LINE_BYTE_SIZE)) % CACHE_LINE_BYTE_SIZE;
    int aligned_column_size = column_size + padding_size;
    stride_ = aligned_column_size / sizeof(unsigned int);

    // Allocate aligned memory
    void* raw_memory = std::aligned_alloc(CACHE_LINE_BYTE_SIZE, world_width * aligned_column_size);
    if (raw_memory == nullptr) { exit(-1); }
    solids_column_m_bitmap_ = static_cast<unsigned int>(raw_memory);
}

SolidsColumnMajorBitmap::~SolidsColumnMajorBitmap() {
    std::free(solids_column_m_bitmap_);
}

SolidsRowMajorBitmap::SolidsRowMajorBitmap(int world_width, int world_heigth) {

    int row_size_in_int_sized_blocks = static_cast<int>(std::ceil(float(world_width) / float(sizeof(unsigned int) * 8)));
    int row_size = row_size_in_int_sized_blocks * sizeof(unsigned int);       // In bytes

    int padding_size = (CACHE_LINE_BYTE_SIZE - (row_size % CACHE_LINE_BYTE_SIZE)) % CACHE_LINE_BYTE_SIZE;
    int aligned_row_size = row_size + padding_size;
    stride_ = aligned_row_size / sizeof(unsigned int);

    // Allocate aligned memory
    void* raw_memory = std::aligned_alloc(CACHE_LINE_BYTE_SIZE, world_heigth * aligned_row_size);
    if (raw_memory == nullptr) { exit(-1); }
    solids_row_m_bitmap_ = static_cast<unsigned int>(raw_memory);
}

SolidsRowMajorBitmap::~SolidsRowMajorBitmap() {
    std::free(solids_row_m_bitmap_);
}

BlockWorld::BlockWorld(int width, int heigth) : width_(width), heigth_(heigth) {
    scmb_ = new SolidsColumnMajorBitmap(width_, heigth_);
    srmb_ = new SolidsRowMajorBitmap(width_, heigth_);
}

BlockWorld::~BlockWorld() {
    delete scmb_;
    delete srmb_;
}

SolidsColumnMajorBitmap * BlockWorld::getSolidsColumnMajorBitmap() {
    return scmb_;
}

SolidsRowMajorBitmap * BlockWorld::getSolidsRowMajorBitmap() {
    return srmb_;
}


/*
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
*/