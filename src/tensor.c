#include <assert.h>
#include <immintrin.h>
#include <stdlib.h>
#include <stdio.h>
typedef struct {
  int x;
  int y;
  float **data;

} Tensor;

Tensor *tensor(int x, int y, float data[x][y]) {
  Tensor *a = malloc(sizeof(Tensor));
  a->x = x;
  a->y = y;
  a->data = (float **)malloc(x * sizeof(float *));
  for (int i = 0; i < x; i++) {
    a->data[i] = (float *)malloc(y * sizeof(float));
    for (int j = 0; j < y; j++) {
      a->data[i][j] = data[i][j];
    }
  }

  return a;
};

Tensor *zeros(int x, int y) {
  Tensor *a = malloc(sizeof(Tensor));
  a->x = x;
  a->y = y;
  a->data = (float **)malloc(x * sizeof(float *));
  for (int i = 0; i < x; i++) {
    a->data[i] = (float *)malloc(y * sizeof(float));
    for (int j = 0; j < y; j++) {
      a->data[i][j] = 0;
    }
  }

  return a;
};

Tensor *mult(Tensor *a, Tensor *b) {
  assert(a->y == b->x);
  float transposed[b->x][b->y];
  for (int i = 0; i < b->x; i++) {
    for (int j = 0; j < b->y; j++) {
      transposed[i][j] = b->data[j][i];
    }
  }
  Tensor* out = zeros(a->x, b->y);
  for (int i = 0; i < a->x; i++) {
    for (int j = 0; j < b->y; j++) {
      float accsum = 0;
      for (int k = 0; k < b->x; k++) {
        accsum += a->data[i][k] * transposed[j][k];
      }
      out->data[i][j] = accsum;
    }
  }
  return out;
};

Tensor* add(Tensor *a, Tensor *b) {
  assert(a->x == b->x);
  assert(a->y == b->y);
  Tensor *out = zeros(a->x, a->y);
  int x = a->x;
  int y = a->y;
  for (int i = 0; i < x; i++) {
    for (int j = 0; j < y; j++) {
      out->data[i][j] = a->data[i][j] + b->data[i][j];
    }
  };
  return out;
};

int main() {
  float test[2][2] = {{1.0f, 1.0f}, {1.0f, 0.0f}};
  Tensor* a = tensor(2,2, test);
  Tensor* out = mult(a,a);
  out = mult(out,a);
  for (int i =0; i < 2;i++) {
    for (int j =0; j < 2; j++) {
      printf("%f ", out -> data[i][j]);
     

    }
    printf("\n");
  }

  return 0;
}
