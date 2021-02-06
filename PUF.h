//
// Created by Mairon on 2/5/21.
//

#ifndef SPUF2_PUF_H
#define SPUF2_PUF_H

#include <functional>
#include <iostream>
#include <cstdint>
#include <random>
#include <bitset>
#include <chrono>

#define CH_SIZE 100
#define INPUT_SIZE 25
using namespace std;

class PUF {
public:
    uint32_t STAGE1[5][32] = {
            {17, 20, 6,  11, 27, 23, 21, 28, 22, 8,  30, 7,  31, 12, 9,  24, 16, 1,  14, 15, 2,  5,  19, 13, 29, 25, 3,  32, 26, 10, 4,  18},
            {3,  25, 4,  28, 7,  20, 19, 5,  24, 14, 21, 27, 23, 13, 1,  12, 11, 26, 10, 22, 2,  31, 17, 15, 8,  18, 29, 6,  30, 9,  32, 16},
            {26, 6,  2,  21, 19, 29, 9,  20, 14, 15, 27, 28, 1,  16, 8,  11, 5,  3,  12, 31, 25, 13, 24, 30, 23, 4,  7,  32, 10, 18, 22, 17},
            {25, 8,  30, 6,  4,  16, 19, 5,  21, 31, 11, 3,  7,  13, 24, 17, 28, 14, 26, 29, 32, 23, 27, 20, 1,  2,  12, 22, 15, 18, 10, 9},
            {3,  4,  15, 20, 21, 29, 26, 7,  5,  6,  25, 23, 19, 24, 27, 17, 30, 22, 18, 8,  12, 32, 9,  28, 31, 10, 11, 13, 1,  14, 16, 2}
    };

    uint32_t STAGE2[5][32] = {
            {10, 32, 12, 31, 8,  16, 5,  1,  23, 2,  21, 4,  17, 18, 7,  3,  26, 28, 20, 14, 15, 9,  30, 6,  24, 25, 13, 11, 19, 29, 27, 22},
            {7,  24, 4,  10, 17, 28, 32, 5,  13, 3,  19, 22, 15, 31, 29, 1,  20, 16, 26, 21, 30, 12, 25, 11, 23, 18, 27, 9,  14, 6,  2,  8},
            {3,  8,  6,  18, 12, 10, 20, 28, 25, 14, 30, 24, 11, 21, 7,  9,  19, 23, 2,  1,  29, 4,  31, 27, 15, 32, 13, 22, 5,  26, 17, 16},
            {21, 18, 17, 7,  28, 9,  29, 10, 3,  20, 22, 26, 5,  14, 27, 32, 8,  1,  12, 19, 15, 30, 25, 16, 24, 13, 23, 2,  11, 31, 4,  6},
            {5,  25, 32, 18, 14, 30, 4,  2,  27, 10, 12, 9,  29, 21, 28, 7,  24, 31, 22, 3,  13, 8,  20, 11, 17, 6,  26, 15, 23, 19, 16, 1}
    };

    bool STAGE3[5][32] = {
            {0, 1, 1, 0, 0, 1, 1, 1, 0, 1, 0, 1, 0, 1, 1, 0, 0, 0, 1, 1, 1, 1, 0, 1, 0, 0, 0, 1, 0, 1, 1, 1},
            {1, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 0, 0, 1, 1, 0, 0, 0, 0, 1, 1, 1, 0, 1, 1, 0, 0, 1, 0, 1, 0, 1},
            {0, 1, 0, 1, 0, 0, 1, 1, 1, 0, 1, 0, 0, 0, 1, 1, 1, 1, 1, 1, 0, 1, 0, 1, 1, 1, 1, 1, 0, 0, 0, 1},
            {1, 0, 0, 0, 0, 1, 0, 1, 1, 1, 1, 0, 0, 1, 0, 0, 1, 0, 1, 1, 1, 0, 0, 0, 1, 0, 1, 0, 1, 0, 0, 0},
            {0, 0, 0, 1, 1, 0, 0, 1, 1, 0, 1, 1, 1, 0, 0, 1, 1, 1, 0, 1, 1, 0, 1, 0, 0, 0, 0, 0, 0, 0, 1, 1}
    };
    // uncomment the following constructor for generating new randomness with each run
//    uint32_t STAGE1[5][32], STAGE2[5][32];
//    bool STAGE3[5][32];

//    PUF() {
//        mt19937::result_type seed = chrono::high_resolution_clock::now().time_since_epoch().count();
//        auto f_rand = bind(std::uniform_int_distribution<int>(0, 31), mt19937(seed));
//        auto f_rand_bin = bind(std::uniform_int_distribution<int>(0, 1), mt19937(seed));

//        for (int i = 0; i < 5; i++)
//            for (int j = 0; j < 32; j++)
//                STAGE1[i][j] = f_rand();
//        for (int i = 0; i < 5; i++)
//            for (int j = 0; j < 32; j++)
//                STAGE2[i][j] = f_rand();
//        for (int i = 0; i < 5; i++)
//            for (int j = 0; j < 32; j++)
//                STAGE3[i][j] = f_rand_bin();
//    }

    bitset<INPUT_SIZE> phase1(bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE> phase2(bitset<INPUT_SIZE>, bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE / 5> phase3(bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE> stage1(bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE> stage2(bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE> permute(bitset<INPUT_SIZE>);

    bitset<INPUT_SIZE> XOR(bitset<INPUT_SIZE>, bitset<INPUT_SIZE>);

    bitset<CH_SIZE> RANDOM(bitset<CH_SIZE>);

    bool AUTH(bitset<CH_SIZE>);
};


#endif //SPUF2_PUF_H
