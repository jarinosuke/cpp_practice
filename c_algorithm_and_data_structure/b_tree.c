#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#define MAX_CHILD 5
#define HALF_CHILD ((MAX_CHILD + 1) / 2)

typedef int KEY;
typedef int DATA;

typedef struct node {
  int nodekind;
  union {
    struct { //for internal node
      int _nchilds;
      struct node *_child[MAX_CHILD];
      KEY _low[MAX_CHILD];
    } _internal;
    struct { //for leaf
      KEY _leaf_key;
      DATA _your_data;
    } _leaf;
  } _u;
} NODE;


#define INTERNAL 1
#define LEAF 2

#define nchilds _u._internal._nchilds
#define child _u._internal._child
#define low _u._internal._low

#define leaf_key _u._leaf._leaf_key
#define your_data _u._leaf._your_data

NODE *root = NULL;

error (char *s) {
  fprintf(stderr, s);
  exit(1);
}

NODE *alloc_node(void) {
  NODE *p;

  if ((p = malloc(sizeof(NODE))) == NULL) {
    error("out of memory\n");
  }
  return p;
}

int keyequal(KEY a, KEY b) {
  return a == b;
}

int keylt(KEY a, KEY b) {
  if (a < b) {
    return 1;
  } else {
    return 0;
  }
}

int locate_subtree(NODE *p, KEY key) {
  int i;

  for (i = p->nchilds - 1; i > 0; i--) {
    if (key >= p->low[i]) {
      return i;
    }
  }
  return 0;
}

NODE *search(KEY key) {
  NODE *p;
  int i;

  if (root == NULL) {
    return NULL;
  } else {
    p = root;
    while (p->nodekind == INTERNAL) {
      i = locate_subtree(p, key);
      p = p->child[i];
    }

    if (key == p->leaf_key) {
      return p;
    } else {
      return NULL;
    }
  }
}


/*
 *  節 *pnode に対して、キー値 key を持つ要素を挿入する
 *  挿入した要素が置かれる節へのポインタを返す
 *  もし新しい節を作ったなら、それを *newnode にセットして
 *  *newnode の指す部分期中の最小要素を *lowest に返す
 *  新しい節を作らなかったら *newnode には NULL を返す
 */
NODE *insert_aux(NODE **pnode, KEY key, NODE **newnode, KEY *lowest) {
  NODE *node;

  *newnode = NULL;
  node = *pnode;

  if (node->nodekind == LEAF) {
    //この節は葉である
    //すでに登録済みであれば何もしないでNULLを返す
    if (keyequal(node->leaf_key, key)) {
      return NULL;
    } else {
      //登録していなければ、新たに葉を割り当てて、 *newnode, *lowestをセットして割り当てた葉へのポインタを返す
      NODE *new;
      new = alloc_node();
      new->nodekind = LEAF;
      new->leaf_key = key;
      //もし割り当てた葉newの方が小さいなら、newとnodeの位置を入れ替える
      if (key < node->leaf_key) {
        //元のnodeには新しく割り当てた葉newを報告する
        *pnode = new;
        //新たに割り当てた葉としてnodeを報告する
        *lowest = node->leaf_key;
        *newnode = node;
      } else {
        //新たに割り当てた葉としてnewを報告する
        *lowest = key;
        *newnode = new;
      }
      //いずれの場合も、新たに割り当てた葉newが関数値となる
      return new;
    }
  } else {
    //この節は内部節である
    int pos;
    NODE *xnode;
    KEY xlow;
    NODE *retv;
    int i, j;

    //どの部分気に挿入するか決める
    pos = locate_subtree(node, key);

    //部分木に対して自身を再帰呼び出し
    retv = insert_aux(&(node->child[pos]), key, &xnode, &xlow);

    //もし分割が行われていなければそのままリターン
    if (xnode == NULL) {
      return retv;
    }

    //分割が行われていたので、節nodeにそれを挿入
    if (node->nchilds < MAX_CHILD) {
      //追加の余地あり
      for (i = node->nchilds - 1; i > pos; i--) {
        node->child[i+1] = node->child[i];
        node->low[i+1] = node->low[i];
      }
      node->child[pos+1] = xnode;
      node->low[pos+1] = xlow;
      node->nchilds++;
      return retv;
    } else {
      //追加の余地なし,節nodeを2つに分割
      NODE *new;
      //新しい内部節newを割り当てる
      new = alloc_node();
      new->nodekind = INTERNAL;
      //節xnodeがどちらの節に挿入されるかで場合分け
      if (pos < HALF_CHILD - 1) {
        //節xnodeは節node側に挿入
        //まず HALF_CHILD-1~MAX_CHILD-1番目の部分木を節nodeへ,それから節newへ移す
        for (i = HALF_CHILD - 1, j = 0; i < MAX_CHILD; i++, j++) {
          new->child[j] = node->child[i];
          new->low[j] = node->low[i];
        }
        //0~HALF_CHILD-2番目の部分木の間の適切な位置に節xnodeを挿入する
        for (i = HALF_CHILD - 2; i > pos; i--) {
          node->child[i+1] = node->child[i];
          node->low[i+1] = node->low[i];
        }
        node->child[pos+1] = xnode;
        node->low[pos+1] = xlow;
      } else {
        //節xnodeは節new側に挿入
        //HALF_CHILD~MAX_CHILD-1番目の部分木を節newに移動する
        //同時に節xnodeの適切な場所へ挿入する
        j = MAX_CHILD - HALF_CHILD;
        for (i = MAX_CHILD - 1; i >= HALF_CHILD; i--) {
          if (i == pos) {
            new->child[j] = xnode;
            new->low[j--] = xlow;
          }
          new->child[j] = node->child[i];
          new->low[j--] = node->low[i];
        }
        if (pos < HALF_CHILD) {
          new->child[0] = xnode;
          new->low[0] = xlow;
        }
      }
      //子の数nchildsを変更する
      node->nchilds = HALF_CHILD;
      new->nchilds = (MAX_CHILD + 1) - HALF_CHILD;
      //分割して新たに作られた節をパラメータ *newnode に返す
      //また、その最小値をパラメータ *lowest に返す
      *newnode = new;
      *lowest = new->low[0];
      return retv;
    }
  }
}

/*
 * B木に要素を挿入する
 * 挿入した要素が置かれる節のポインタを返す
 * すでに要素が登録されている場合は何もしないでNULLを返す
 * key : 挿入データ
 * 実際にB木を辿って要素を挿入するのはinsert_aux関数
 */
NODE *insert(KEY key) {
 if (root == NULL) {
   //木が空の場合は葉を作ってそれを返す
    root = alloc_node();
    root->nodekind = LEAF;
    root->leaf_key = key;
    return root;
  } else {
    //木が空でない場合は関数insert_auxを呼び出して要素を挿入
    NODE *retv, *new, *newnode;
    KEY lowest;

    retv = insert_aux(&root, key, &newnode, &lowest);
    //もし分割が行われたなら木の高さを一段高くする
    if (newnode != NULL) {
      new = alloc_node();
      new->nodekind = INTERNAL;
      new->nchilds = 2;
      new->child[0] = root;
      new->child[1] = newnode;
      new->low[1] = lowest;
      root = new;
    }
    return retv;
  }
}

/*
 * 節pのx番目とx+1番目の部分木とを再編成する
 * もし併合が必要なら全ての要素をx番目の部分木に集めて1を返す。そうでなければ0
 */

int merge_nodes(NODE *p, int x) {
  NODE *a; //x番目の部分木
  NODE *b; //x+1番目の部分木
  int an; //部分木aの子の数
  int bn; //部分木bの子の数
  int i;

  a = p->child[x];
  b = p->child[x+1];
  b->low[0] = p->low[x+1];
  an = a->nchilds;
  bn = b->nchilds;
  
  if (an + bn <= MAX_CHILD) {
    //部分木a, bとを併合
    //bの子を全てaに移動
    for (i = 0; i < bn; i++) {
      a->child[i+an] = b->child[i];
      a->low[i+an] = b->low[i];
    }
    a->nchilds += bn;
    free(b);
    return 1;
  } else {
    //部分木a, bで節を再分配
    int n; //部分木aに分配すべき子の点
    int move; //移動する要素の個数

    n = (an + bn) / 2;
    if (an > n) {
      //部分木aから部分木bに移動する
      move = an - n; //move個の子をa->bに移す
      for (i = bn -1; i >= 0; i--) {
        b->child[i+move] = b->child[i];
        b->low[i+move] = b->low[i];
      }
      for (i = 0; i < move; i++) {
        b->child[i] = a->child[i+n];
        b->low[i] = a->low[i+n];
      }
    } else {
      //部分木bから部分木aに移動する
      move = n -an;
      for (i = 0; i < move; i++) {
        a->child[i+an] = b->child[i];
        a->low[i+an] = b->low[i];
      }
      for (i = 0; i < bn - move; i++) {
        b->child[i] = b->child[i+move];
        b->low[i] = b->low[i+move];
      }
    }
    //子の個数を更新
    a->nchilds = n;
    b->nchilds = an + bn - n;
    //部分木bの最小値を節pにセット
    p->low[x+1] = b->low[0];
    return 0;
  }
}

/*
 * 節nodeに対してキーkeyを持つ要素を削除する
 * 削除による節nodeの変化を*resultに返す
 */

#define OK 1
#define REMOVED 2
#define NEED_REORG 3

int delete_aux(NODE *node, KEY key, int *result) {
  *result = OK;
  if (node->nodekind == LEAF) {
    //葉
    if (keyequal(node->leaf_key, key)) {
      //キーが同じであれば削除
      *result = REMOVED;
      free(node);
      return 1;
    } else {
      //キーが一致しない、つまり与えられたキーは存在しない
      return 0;
    }
  } else {
    //内部節
    int pos; //何番目の部分木から削除するか
    int condition; //部分木に何が起こったか
    int retv; //部分木の削除の結果
    int sub; //部分木subとsub+1とを再編成する
    int joined; //再編成の結果、部分木が併合されたか
    int i;

    //どの部分木から削除するか
    pos = locate_subtree(node, key);
    //部分木に対して自身を再帰呼び出し
    retv = delete_aux(node->child[pos], key, &condition);
    //部分木に何の変化もなければリターン
    if (condition == OK) {
      return retv;
    }

    //部分木posを再編成する必要あるか
    if (condition == NEED_REORG) {
      sub = (pos == 0) ? 0 : pos - 1;
      //部分木subとsub+1を再編成する
      joined = merge_nodes(node, sub);
      //もしsubとsub+1が併合されたら部分木sub+1をnodeから削除する必要あり
      if (joined) {
        pos = sub + 1;
      }
    }
    //部分木posが削除された
    if (condition == REMOVED || joined) {
      //node の部分木を詰め合わせる
      for (i = pos; i < node->nchilds - 1; i++) {
        node->child[i] = node->child[i+1];
        node->low[i] = node->low[i+1];
      }
      //もしnodeの部分木の数がHALF_CHILDより小さいなら再編成が必要
      if (--node->nchilds < HALF_CHILD) {
        *result = NEED_REORG;
      }
    }
    return retv;
  }
}

int delete(KEY key) {
  int retv, result;
  NODE *p;

  if (root == NULL) {
    return 0;
  } else {
    retv = delete_aux(root, key, &result);
    if (result == REMOVED) {
      root = NULL;
    } else if (result == NEED_REORG && root->nchilds == 1) {
      p = root;
      root = root->child[0];
      free(p);
    }
    return retv;
  }
}

printtree(NODE *p) {
  int i;

  if (p->nodekind == LEAF) {
    printf("%04x leaf val=%d\n", p, p->leaf_key);
  } else {
    printf("%04x %02d [%04x]   %d[%04x] %d[%04x] %d[%04x] %d[%04x]\n", p, p->nchilds, p->child[0],
        p->low[1], p->child[1],p->low[2], p->child[2],p->low[3], p->child[3],p->low[4], p->child[4]);
    for (i = 0; i < p->nchilds; i++) {
      printtree(p->child[i]);
    }
  }
}

int main () {
  //static int data[] = {10, 20, 30, 40, 50};
  static int data[] = {13, 5, 2, 7, 6, 21, 15};
  int i, x;
  char str[100];

  for (i = 0; i < sizeof(data)/sizeof(data[0]); i++) {
    insert(data[i]);
  }

  printf("+n: nを挿入する\n-n : nを削除する\nn : nを探索する\n");
  printtree(root);
  printf("\n>");

  while(gets(str) != NULL) {
    x = abs(atoi(str));
    switch (str[0]) {
      case '+':
        if (insert(x) != NULL) {
          printf("%d inserted\n", x);
        } else {
          printf("%d not inserted\n", x);
        }
        break;
      case '-':
        if (delete(x)) {
          printf("%d deleted\n", x);
        } else {
          printf("%d not deleted\n", x);
        }
        break;
      default:
        if (search(x) != NULL) {
          printf("%d found\n", x);
        } else {
          printf("%d not found\n", x);
        }
        break;
    }
    printtree(root);
    printf("\n>");
  }
}
