#include <emscripten.h>

extern "C" {

int EMSCRIPTEN_KEEPALIVE get_sum(int number1, int number2)
{
    int sum;
    sum = number1 + number2;
    return sum; 
}

}

int main() { 
}
