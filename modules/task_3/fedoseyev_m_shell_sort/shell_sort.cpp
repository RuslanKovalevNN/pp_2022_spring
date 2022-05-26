// Copyright 2022 Fedoseyev Mikhail

#include "../../../modules/task_3/fedoseyev_m_shell_sort/shell_sort.h"

#include <tbb/tbb.h>

int *generate_vector(int n) {
  std::random_device dev;
  static std::mt19937 gen(dev());

  int *data = new int[n];
  for (int i = 0; i < n; i++) data[i] = gen() % 100;

  return data;
}

void insertion_sort(int a[], int n, int stride) {
  for (int j = stride; j < n; j += stride) {
    int key = a[j];
    int i = j - stride;
    while (i >= 0 && a[i] > key) {
      a[i + stride] = a[i];
      i -= stride;
    }
    a[i + stride] = key;
  }
}

void shell_sort(int a[], int n, bool parallel) {
  tbb::task_group task_group;

  if (parallel) {
    for (int m = n / 2; m > 0; m /= 2) {
      task_group.run([&a, n, m]() {
        for (int i = 0; i < m; i++) {
          insertion_sort(&(a[i]), n - i, m);
        }
      });
    }
    task_group.wait();
  } else {
    for (int m = n / 2; m > 0; m /= 2) {
      for (int i = 0; i < m; i++) insertion_sort(&(a[i]), n - i, m);
    }
  }
}

void print_list(int a[], int n) {
  for (int i = 0; i < n; i++) {
    printf("%d ", a[i]);
  }
  printf("\n");
}

int check_list(int a[], int n) {
  int result = 0;
  for (int i = 0; i < n - 1; i++) {
    if (a[i] > a[i + 1]) {
      result++;
    }
  }
  return result;
}
