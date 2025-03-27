#ifndef BLOCK_WORLD_HPP
#define BLOCK_WORLD_HPP

#include <cstdlib>
#include <cmath>

#include "MGL/include/mgl_config.hpp"

#define CHUNCK_BIT_SIZE sizeof(unsigned int)*8;

class SolidsColumnMajorBitmap {
    private:
        int stride_;
        unsigned int * solids_column_m_bitmap_;
    
    public:
        SolidsColumnMajorBitmap(int world_width, int world_heigth);
        ~SolidsColumnMajorBitmap();

        operator()(int i, int j_chunck) {
            return solids_column_m_bitmap_[i * stride_ + j_chunck];
        }

        const operator()(int i, int j_chunck) const {
            return solids_column_m_bitmap_[i * stride_ + j_chunck];
        }
}

class SolidsRowMajorBitmap {
    private:
        int stride_;
        unsigned int * solids_row_m_bitmap_;
    
    public:
        SolidsRowMajorBitmap(int world_width, int world_heigth);
        ~SolidsRowMajorBitmap();

        operator()(int j, int i_chunck) {
            return solids_row_m_bitmap_[j * stride_ + i_chunck];
        }

        const operator()(int j, int i_chunck) const {
            return solids_row_m_bitmap_[j * stride_ + i_chunck];
        }
}

class BlockWorld {
    private:
        const int width_;
        const int heigth_;

        SolidsColumnMajorBitmap * scmb_;
        SolidsRowMajorBitmap * srmb_;
    
    public:
        BlockWorld(int width, int heigth);
        ~BlockWorld();

        SolidsColumnMajorBitmap * getSolidsColumnMajorBitmap();
        SolidsRowMajorBitmap * getSolidsRowMajorBitmap();
}

#endif

/*
* A Block struct data type.
* 
* CONSTANTS:
*   id - Block id. Tells the type of the block. This is a constant.
*
* VARIABLES:
*   hp - Healt point. Variable
*/
/*
struct Block {
    const unsigned short int id;
    unsigned int hp;
};
*/

/*
* Column-major.
*/

/*
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
*/