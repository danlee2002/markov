#include "src/tensor.hpp"
#include <iostream>

int main() {
  Tensor a = Tensor(5);
  std::vector<std::vector<float>> data = {{1, 2, 3, 4, 5}};

  Tensor b = Tensor(data);
  std::cout << b * b << std::endl;
  return 0;
}
