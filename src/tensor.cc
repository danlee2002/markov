#include "tensor.hpp"

Tensor::Tensor(int m, int n) {
  this->data = new float[m * n];
  std::fill_n(data, m * n, 0.0f);
  this->m = m;
  this->n = n;
}

Tensor::Tensor(int m) {
  this->m = m;
  this->n = m;
  this->data = new float[m * n];
  for (size_t i = 0; i < m; i++) {
    this->data[m * i + i] = 1.0f;
  }
}

Tensor::Tensor(std::vector<std::vector<float>> data) {
  this->m = data.size();
  this->n = data[0].size();
  this->data = new float[m * n];
  std::fill_n(this->data, m * n, 0.0f);
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
  size_t i = 0;
  while (i + 8 <= m * n) {
    __m256 a = _mm256_loadu_ps(this->data + i);
    __m256 b = _mm256_loadu_ps(val.data + i);
    __m256 sum = _mm256_add_ps(a, b);
    _mm256_storeu_ps(out.data + i, sum);
    i += 8;
  }
  while (i < m * n) {
    out.data[i] = data[i] - val.data[i];
    i++;
  }

  return out;
}

Tensor Tensor::operator-(Tensor const &val) {
  assert(this->m == val.m);
  assert(this->n == val.n);
  Tensor out = Tensor(this->m, this->n);
  size_t i = 0;
  while (i + 8 <= m * n) {
    __m256 a = _mm256_loadu_ps(this->data + i);
    __m256 b = _mm256_loadu_ps(val.data + i);
    __m256 sum = _mm256_sub_ps(a, b);
    _mm256_storeu_ps(out.data + i, sum);
    i += 8;
  }
  while (i < m * n) {
    out.data[i] = data[i] - val.data[i];
    i++;
  }
  return out;
}

Tensor Tensor::operator*(Tensor const &val) {
  assert(this->m == val.m);
  assert(this->n == val.n);
  Tensor out = Tensor(this->m, this->n);
  size_t i = 0;
  while (i + 8 <= m * n) {
    __m256 a = _mm256_loadu_ps(this->data + i);
    __m256 b = _mm256_loadu_ps(val.data + i);
    __m256 sum = _mm256_mul_ps(a, b);
    _mm256_storeu_ps(out.data + i, sum);
    i += 8;
  }
  for (; i < m * n; ++i) {
    out.data[i] = this->data[i] * val.data[i];
  }
  return out;
}

std::ostream &operator<<(std::ostream &out, const Tensor &val) {
  for (size_t i = 0; i < val.m; i++) {
    for (size_t j = 0; j < val.n; j++) {
      if (j == 0) {
        out << "[" << val.data[i] << ", ";

      } else if (j == val.n - 1) {
        out << val.data[i] << "]\n";
      } else {
        out << val.data[val.n * i + j] << ", ";
      }
    }
  }
  return out;
}
