#include <stdlib.h>
#include <stdio.h>
#include <string.h>

void bubble_sort(int a[], int n) {
  int i, j, t;

  for (i = 0; i < n - 1; i++) {
    for (j = n - 1; j > i; j--) {
      if (a[j - 1] > a[j]) {
        t = a[j];
        a[j] = a[j - 1];
        a[j - 1] = t;
      }
    }
  }
}

void selection_sort(int a[], int n) {
  int i, j, t, lowest, lowkey;

  for (i = 0; i < n-1; i++) {
    lowest = i;
    lowkey = a[i];
    for (j = i+1; j < n; j++) {
      if (a[j] < lowkey) {
        lowest = j;
        lowkey = a[j];
      }
    }
    t = a[i];
    a[i] = a[lowest];
    a[lowest] = t;
  }
}

void insertion_sort(int a[], int n) {
  int i, j, t;

  for (i = 1; i < n; i++) {
    j = i;
    while (j >= 1 && a[j-1] > a[j]) {
      t = a[j];
      a[j] = a[j-1];
      a[j-1] = t;
      j--;
    }
  }
}

void shell_sort(int a[], int n) {
  int h, i, j, t;

  for (h = 1; h < n/9; h = h * 3 + 1) {
  };

  for (; h > 0; h /= 3) {
    for (i = h; i < n; i++) {
      j = i;
      while (j >= h && a[j-h] > a[j]) {
        t = a[j];
        a[j] = a[j-h];
        a[j-h] = t;

        j -= h;
      }
    }
  }
}

int main () {
}
