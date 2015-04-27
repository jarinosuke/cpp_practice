#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_HEAP 100

int a[MAX_HEAP + 1];

int n; //ヒープに入っている要素の個数

void downheap () {
  int i, j;
  int val;

  //沈められる要素の値をvalにセット
  val = a[1];

  //根からはじめて、節iが子を持っている限り繰り返し
  i = 1;
  while (i <= n/2) {
    //節iの子のうち小さい方を節jとする
    j = i * 2;
    if (j+1 <= n && a[j] < a[j+1]) {
      j++;
    }

    //もし親が子より大きく無いという関係がなりたてば、ここで終わり
    if (val <= a[j]) {
      break;
    }

    //節iに節jの値を入れて節jに注目
    a[i] = a[j];
    i = j;
  }

  //先頭にあった要素を節iに入れる
  a[i] = val;
}

int delete_min () {
  int val;

  if (n < 1) {
    fprintf(stderr, "ヒープが空です\n");
    exit(1);
  }

  //根の要素をリターン
  val = a[1];

  //ヒープの最後の要素を先頭に移動する
  a[1] = a[n--];

  //根に移動した要素を適当な場所まで沈める
  downheap();

  return val;
}

//ヒープ内のx番目の要素を必要な場所まで浮かび上がらせる
void upheap (int x) {
  int val;

  //浮かび上がらせる要素をvalに入れておく
  val = a[x];

  //要素が根まで浮かび上がっていない、かつ親が子より大きい間はループ
  while (x > 1 && a[x/2] > val) {
    //親の値を子に移す
    a[x] = a[x/2];

    //注目点を親に移す
    x /= 2;
  }

  //最終的に
  a[x] = val;
}

void insert(int elem) {
  //ヒープに登録できる余裕があるか確認
  if (n >= MAX_HEAP) {
    fprintf(stderr, "これ以上登録できません\n");
  }

  //要素をとりあえず最後尾に入れる
  a[++n] = elem;

  upheap(n);
}

int main () {
}
