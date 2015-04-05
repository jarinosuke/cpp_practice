#include <iostream>
#include <cstdlib>
using namespace std;

int addition(int a, int b)
{
  int r;
  r = a + b;
  return r;
}

int substraction(int a, int b)
{
  int r;
  r = a - b;
  return r;
}

int duplicate(int &x)
{
  return x * 2;
}

int main()
{
  int z;
  z = addition(5, 3);
  cout << "Result is: " << z << endl;
  int x = 5;
  cout << x << "Duplicate is: " << duplicate(x) << endl;
  return EXIT_SUCCESS;
}
