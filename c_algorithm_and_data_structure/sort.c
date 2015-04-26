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

//配列a[l]~a[r]を分割する、枢軸の添え字を返す
int partition(int a[], int l, int r) {
  int i, j, pivot, t;

  i = l - 1;
  j = r;

  //一番右端の要素を枢軸とする
  pivot = a[r];

  //ポインタiとjがぶつかるまで繰り返す
  for (;;) {
    //ポインタiを右に進める
    while(a[++i] < pivot) {
      //ポインタjを左に進める
      while(i < --j && pivot < a[j]) {
        //i, jがぶつかったら抜ける
        if (i >= j) {
          break;
        }

        //iとjの指す要素を交換
        t = a[i];
        a[i] = a[j];
        a[j] = t;
      }
    }
  }

  //a[i]と枢軸の要素を交換する
  t = a[i];
  a[i] = a[r];
  a[r] = t;
  return i;
}

void quick_sort_1(int a[], int l, int r) {
  //整列する要素が一つなら終わり
  int v;
  if (l >= r) {
    return;
  }
  v = partition(a, l, r);
  quick_sort_1(a, l, v-1);
  quick_sort_1(a, v+1, r);
}

void quick_sort(int a[], int n) {
  quick_sort_1(a, 0, n-1);
}

int main () {
}
