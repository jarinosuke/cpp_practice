#include <stdlib.h>
#include <stdio.h>
#include <ctype.h>

typedef long ELEM;

#define STACK_SIZE 100

ELEM stack[STACK_SIZE];
int n;

void error(char *s)
{
  fprintf(stderr, s);
  exit(1);
}

void init()
{
  n = 0;
}

void push(ELEM x)
{
  if (n  >= STACK_SIZE) {
    error("stack overflow\n");
  }
  stack[n++] = x;
}

ELEM pop()
{
  if (n <= 0) {
    error("stack underflow\n");
  }
  return stack[--n];
}

int empty()
{
  return n == 0;
}

int main ()
{
  int c;
  int x, a, b;

  init();
  while((c = getchar()) != EOF) {
    if (isdigit(c)) {
      ungetc(c, stdin);
      scanf("%ld", &x);
      push(x);
    } else {
      switch (c) {
        case '+':
          b = pop();
          a = pop();
          push(a + b);
          break;
        case '-':
          b = pop();
          a = pop();
          push(a - b);
          break;
        case '*':
          b = pop();
          a = pop();
          push(a * b);
          break;
        case '/':
          b = pop();
          a = pop();
          push(a / b);
          break;
        case '\n':
          if (!empty()) {
            printf("answer is %ld\n", pop());
          }
          break;
        case ' ':
        case '\t':
          //skip
          break;
        default:
          printf("invalid value\n");
          break;
      }
    }
  }
}
