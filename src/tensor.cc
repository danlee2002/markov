#include "tensor.hpp"

Tensor::Tensor(int m, int n) {
  this->data = std::vector<float>(m * n, 0.0f);
  this->m = m;
  this->n = n;
}

Tensor::Tensor(int m) {
  this->m = m;
  this->n = m;
  this->data = std::vector<float>(m * m, 0.0f);
  for (size_t i = 0; i < m; i++) {
    this->data[m * i + i] = 1.0f;
  }
}

Tensor::Tensor(std::vector<std::vector<float>> data) {
  this->m = data.size();
  this->n = data[0].size();
  this->data = std::vector<float>(this->m * this->n, 0.0f);
  for (size_t i = 0; i < m; i++) {
    for (size_t j = 0; j < n; j++) {
      this->data[i * n + j] = data[i][j];
    }
  }
}

Tensor Tensor::operator+(Tensor const &val) {
  assert(this->m == val.m);
  assert(this->n == val.n);
  Tensor out = Tensor(this->m, this->n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      out.data[m * i + j] = this->data[m * i + j] + val.data[m * i + j];
    }
  }
  return out;
}

Tensor Tensor::operator-(Tensor const &val) {
  assert(this->m == val.m);
  assert(this->n == val.n);
  Tensor out = Tensor(this->m, this->n);
  for (int i = 0; i < m; i++) {
    for (int j = 0; j < n; j++) {
      out.data[m * i + j] = this->data[m * i + j] - val.data[m * i + j];
    }
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const Tensor &val) {
  for (size_t i = 0; i < val.m; i++) {
    for (size_t j = 0; j < val.n; j++) {
      out << val.data[val.m * i + j];
    }
    out << "\n";
  }
  return out;
}
