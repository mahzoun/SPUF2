//
// Created by sauron on 2/11/21.
//

#include "utils.h"

long long utils::choose(int n, int k) {
    if (k == 0)
        return 1;
    return n * choose(n - 1, k - 1) / k;
}