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
        const int width_;
        const int heigth_;
        int stride_;
        Block* blocks_;
    
    public:
        BlockMatrix(int width, int heigth);
        ~BlockMatrix();

        Block& operator()(int i, int j) {
            return blocks_[i * stride_ + j];
        }

        const Block& operator()(int i, int j) const {
            return blocks_[i * stride_ + j];
        }
}

#endif