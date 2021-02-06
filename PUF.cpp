//
// Created by Mairon on 2/5/21.
//

#include <algorithm>
#include <iostream>
#include <random>
#include <bitset>
#include "PUF.h"

using namespace std;

bitset<INPUT_SIZE> PUF::stage1(bitset<INPUT_SIZE> input) {
    bitset<INPUT_SIZE> output;
    for (int idx = 0; idx < INPUT_SIZE; idx += 5) {
        bitset<5> current_block;
        for (int j = 0; j < 5; j++) {
            current_block[j] = input[idx + j];
        }
        unsigned long cur_block_val = current_block.to_ulong();
        uint32_t cur_block_res = STAGE1[idx / 5][cur_block_val];
        current_block = cur_block_res;
        for (int j = 0; j < 5; j++) {
            output[idx + j] = current_block[j];
        }
    }
    return output;
}

bitset<INPUT_SIZE> PUF::stage2(bitset<INPUT_SIZE> input) {
    bitset<INPUT_SIZE> output;
    for (int idx = 0; idx < INPUT_SIZE; idx += 5) {
        bitset<5> current_block;
        for (int j = 0; j < 5; j++) {
            current_block[j] = input[idx + j];
        }
        unsigned long cur_block_val = current_block.to_ulong();
        uint32_t cur_block_res = STAGE2[idx / 5][cur_block_val];
        current_block = cur_block_res;
        for (int j = 0; j < 5; j++) {
            output[idx + j] = current_block[j];
        }
    }
    return output;
}

bitset<INPUT_SIZE> PUF::permute(bitset<INPUT_SIZE> input) {
    bitset<INPUT_SIZE> output;
    for (int block = 0; block < 5; block++) {
        for (int pos = 0; pos < 5; pos++) {
            output[block * 5 + pos] = input[pos * 5 + block];
        }
    }
    return output;
}

bitset<INPUT_SIZE> PUF::XOR(bitset<INPUT_SIZE> first, bitset<INPUT_SIZE> second) {
    bitset<INPUT_SIZE> output = first ^second;
    return output;
}

bitset<INPUT_SIZE> PUF::phase1(
        bitset<INPUT_SIZE> input) { // return the permuted output of phase 1, permute function is involution in the design
    bitset<INPUT_SIZE> output;
    output = stage1(input);
    output = permute(output);
    output = stage2(output);
    output = permute(output);
    return output;
}

bitset<INPUT_SIZE> PUF::phase2(bitset<INPUT_SIZE> input,
                               bitset<INPUT_SIZE> prev_round_output) { //XOR the output of previous phase and new 25-bit of inout
    bitset<INPUT_SIZE> output;
    input = XOR(input, prev_round_output);
    output = stage1(input);
    output = permute(output);
    output = stage2(output);
    output = permute(output);
    return output;
}

bitset<5> PUF::phase3(bitset<INPUT_SIZE> input) {
    bitset<5> output;
    for (int idx = 0; idx < INPUT_SIZE; idx += 5) {
        bitset<5> current_block;
        for (int j = 0; j < 5; j++) {
            current_block[j] = input[idx + j];
        }
        unsigned long cur_block_val = current_block.to_ulong();
        bool cur_block_res = STAGE3[idx / 5][cur_block_val];
        output[idx / 5] = cur_block_res;
    }
    return output;
}

bool PUF::AUTH(bitset<CH_SIZE> challenge) {
//   cout << "input:\t " << challenge << endl;
   bitset<INPUT_SIZE> input, output;
   bitset<5> result;
   for(int i = 0; i < 25; i++)
       input[i] = challenge[i];
//   cout << "input of phase 1:\t" << input << endl;
   output = phase1(input);
   for(int mult = 1; mult < 4; mult++) { // run phase 2 for n = 25, 50, 75 (n = mult * 25)
       for (int i = 0; i < 25; i++)
           input[i] = challenge[25 * mult + i];
//       cout << "input of phase 2 for n = " << mult * 25 << "\t" << input << endl;
       output = phase2(input, output);
//       cout << "output of phase2 for n = " << mult * 25 << "\t" << output << endl;
   }
   result = phase3(output);
//   cout << "result is:\t" << result << endl;
   return result.count() % 2;
}

bitset<CH_SIZE> PUF::RANDOM(bitset<100> input) {
    for(int i = 0; i < CH_SIZE; i++)
        input[i] = rand() %2;
    return input;
}

