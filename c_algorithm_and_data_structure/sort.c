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

#define MAX_ELEMENTS 10000

int b[MAX_ELEMENTS];

//配列版マージソート
//a[low]~a[high]の要素を整列する

void merge_sort_array(int a[], int low, int high) {
  int mid, i, j, k;

  //要素が一つしかなければ、即座に終了
  if (low >= high) {
    return;
  }

  //列を2つに分割するmidを決定
  mid = (low + high) / 2;

  //前半の要素a[low]~a[mid]を整列
  merge_sort_array(a, low, mid);

  //後半の要素a[mid+1]~a[high]を整列
  merge_sort_array(a, mid+1, high);

  //前半の要素をそのまま作業用配列にコピー
  for (i = low; i <= mid; i++) {
    b[i] = a[i];
  }

  //後半の要素を逆順にbにコピー
  for (i = mid+1, j = high; i <= high; i++, j--) {
    b[i] = a[j];
  }

  //作業用配列bの両端から取り出したデータをマージしてaに入れる
  i = low;
  j = high;
  for (k = low; k <= high; k++) {
    if (b[i] <= b[j]) {
      a[k] = b[i++];
    } else {
      a[k] = b[j--];
    }
  }
}

//連結リストのセル
struct node {
  int value; //キーとなる値
  struct node *next; //次のセルへのポインタ
};

//2つの連結リストa, bをマージする マージされた連結リストの先頭要素へのポインタを返す
struct node *merge_list(struct node *a, struct node *b) {
  struct node head, *p;

  //ポインタpがダミーの要素を指すようにする
  p = &head;

  //連結リストa, bのいずれかが空になるまで繰り返す
  while (a != NULL && b != NULL) {
    //連結リストa, bの先頭の要素を比較する
    if (a->value <= b->value) {
      //連結リストaの先頭の要素を取り除き、マージ済み連結リストの末尾に連結する
      p->next = a;
      p = a;
      a = a->next;
    } else {
      //連結リストbの先頭の要素を取り除き、マージ済み連結リストの末尾に連結する
      p->next = b;
      p = b;
      b = b->next;
    }
  }

  //残っている要素をマージ済み連結リストの最後尾に連結する
  if (a == NULL) {
    p->next = b;
  } else {
    p->next = a;
  }

  return head.next;
}

//連結リスト版マージソート
struct node *merge_sort_list(struct node *x) {
  struct node *a, *b, *p;

  //連結リストに要素が無いか、1つしか無いときはそのまま返す
  if (x == NULL || x->next == NULL) {
    return x;
  }

  //連結リストをスキャンするポインタ初期化

  //aは1番目の要素を示す
  a = x;

  //bは3番目の要素（もし連結リストの長さが2なら2)を指す
  b = x->next;
  if (b != NULL) {
    b = b->next;
  }

  //ポインタbが連結リストの末尾に到達するまでポインタaを1つ進め、ポインタbを2つ進める
  //ポインタbが末尾に到達した時、ポインタaは連結リストのほぼ中央の要素をさしているはずである
  while (b != NULL) {
    a = a->next;
    b = b->next;
    if (b != NULL) {
      b = b->next;
    }
  }

  //連結リストをポインタaが指す要素の直後で2つに切断する
  p = a->next;
  a->next = NULL;

  //切断した連結リストを個別に整列して、その結果をマージする
  return merge_list(merge_sort_list(x), merge_sort_list(p));
}

int main () {
}
