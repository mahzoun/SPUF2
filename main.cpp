#include <iostream>
#include <bitset>
#include "PUF.h"

using namespace std;

int main() {
    PUF puf;
    bitset<100> input = 0;
    for (int i = 0; i < 100; i++) {
        input = puf.RANDOM(input);
        cout << input << "\t" << puf.AUTH(input) << endl;
    }
    return 0;
}
