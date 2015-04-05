#include <iostream>
using namespace std;

template <class T> T sum (T a, T b)
{
  return a + b;
}

template <class T>  bool are_equal(T a, T b)
{
  return a == b;
}

int main ()
{
  cout << sum(2, 3) << endl;
  cout << sum(2.5, 1.2) << endl;

  cout << are_equal(2, 2) << endl;
  cout << are_equal(5.0, 3.0) << endl;
}
