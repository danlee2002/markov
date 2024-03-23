#include "src/tensor.hpp"
#include <iostream>

int main() {

  Tensor a = Tensor(3);
  std::cout << a + a;
  return 0;
}
