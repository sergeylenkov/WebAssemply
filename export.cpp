#include <iostream>
#include <emscripten.h>

#ifdef __cplusplus
extern "C" {
#endif

int EMSCRIPTEN_KEEPALIVE get_sum(int number1, int number2)
{
    int sum;
    sum = number1 + number2;
    return sum; 
}

#ifdef __cplusplus
}
#endif

int main() { 
}
