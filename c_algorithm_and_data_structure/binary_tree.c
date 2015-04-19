#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef long KEY;

typedef struct node {
  KEY data;
  struct node *left;
  struct node *right;
} NODE;

NODE *root = NULL;

int keyequal(KEY a, KEY b) {
  if (a == b) {
    return 1;
  } else {
    return 0;
  }
}

int keylt(KEY a, KEY b) {
  if (a < b) {
    return 1;
  } else {
    return 0;
  }
}

NODE *search(KEY key) {
  NODE *p;

  p = root;
  while (p != NULL) {
    if (keyequal(key, p->data)) { //return key if they're same
      return p;
    }
    else if (keylt(key, p->data)) {
      p = p->left; //go left
    }
    else {
      p = p->right; //go right
    }
  }
  return NULL;
}

NODE *insert(KEY key) {
  NODE **p;
  NODE *new_p;

  p = &root;
  while (*p != NULL) { //loop until point for insert
    if (keyequal(key, (*p)->data)) {
      return NULL; //key is already inserted
    }
    else if (keylt(key, (*p)->data)) {
      p = &(*p)->left; //go to left part
    }
    else {
      p = &(*p)->right; //go to right part
    }
  }

  if ((new_p = malloc(sizeof(NODE))) == NULL) {
    //out of memory
    exit(0);
  }

  new_p->left = NULL;
  new_p->right = NULL;
  new_p->data = key;
  *p = new_p;
  return new_p;
}

int delete(KEY key) {
  NODE **p;
  NODE *x;

  p = &root;
  while (*p != NULL) {
    if (keyequal(key, (*p)->data)) { //found key
      x = *p;

      if (x->left == NULL && x->right == NULL) { //x is leaf
        *p = NULL;
      }
      else if (x->left == NULL) { //right only
        *p = x->right;
      }
      else if (x->right == NULL) { //left only
        *p = x->left;
      }
      else { //right & left
        *p = deletemin(&x->right);
        (*p)->right = x->right;
        (*p)->left = x->left;
      }
      free(x);
      return 1;
    } 
    else if (keylt(key, (*p)->data)) {
      p = &(*p)->left;
    } else {
      p = &(*p)->right;
    }
  }
  return 0;
}

NODE *deletemin(NODE **p) {
  NODE *x;

  while ((*p)->left != NULL) {
    p = &(*p)->left;
  }
  x = *p;
  *p = (*p)->right;
  return x;
}

int main () {
}
