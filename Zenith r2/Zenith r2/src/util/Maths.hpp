#pragma once

#include <algorithm>

namespace zenmath{
    template<typename T>
    T min(T a, T b) {
        return (a < b) ? a : b;
    }
    
    template<typename T>
    T max(T a, T b) {
        return (a > b) ? a : b;
    }

    int abs(int val) { return (val < 0)? -val : val; }

    /* Loss of precision but very fast */
    float Qsqrt(float val) {
        int tmp = *(int *)&val;
        tmp -= 1 << 23;
        tmp = tmp >> 1;
        tmp += 1 << 29;
        return *(float *)&tmp;
    }
}