#ifndef TENSOR_H
#define TENSOR_H
#include <algorithm>
#include <cassert>
#include <immintrin.h>
#include <iostream>
#include <math.h>
#include <vector>
class Tensor {
public:
  Tensor(int m, int n);
  Tensor(int m);
  Tensor(std::vector<std::vector<float>>);

  Tensor operator+(Tensor const &val);
  Tensor operator-(Tensor const &val);
  Tensor operator*(Tensor const &val);
  std::vector<float> operator[](int i);
  friend std::ostream &operator<<(std::ostream &out, const Tensor &val);

private:
  float *data;
  int m;
  int n;
  bool requires_grad = true;
};

#endif
