#ifndef BLOCK_MATRIX_HPP
#define BLOCK_MATRIX_HPP

#include <cstdlib>

#include "MGL/include/mgl_config.hpp"

/*
* A Block struct data type.
* 
* CONSTANTS:
*   id - Block id. Tells the type of the block. This is a constant.
*
* VARIABLES:
*   hp - Healt point. VAriable
*/
struct Block {
    const unsigned short int id;
    unsigned int hp;
};

/*
* Column-major.
*/
class BlockMatrix {
    private:
        const size_t rows_;
        const size_t cols_;
        size_t stride_;
        Block* blocks_;
    
    public:
        BlockMatrix(size_t rows, size_t cols);
        ~BlockMatrix();

        // Override () operator for matrix-style access
        Block& operator()(size_t r, size_t c) {
            return blocks_[r * stride_ + c];
        }

        // Const overload for read-only access
        const Block& operator()(size_t r, size_t c) const {
            return blocks_[r * stride_ + c];
        }
}

#endif