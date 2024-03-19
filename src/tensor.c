#include <assert.h>
#include <stdio.h>
#include <stdlib.h>
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

Tensor *add(Tensor *a, Tensor *b) {
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
