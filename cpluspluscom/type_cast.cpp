#include <iostream>
#include <exception>

using namespace std;

class Dummy {
  double i, j;
};

class Addition {
  int x, y;
  public:
    Addition (int a, int b) {
      x = a;
      y = b;
    }
    int result () {
      return x * y;
    }
};

class Base {
  virtual void dummy() {
  };
};

class Derived : public Base {
  int a;
};

int main ()
{
  Dummy d;
  Addition *addition;

  addition = (Addition *)&d;

  cout << addition->result() << endl;

  try {
    Base *pba = new Derived;
    Base *pbb = new Base;
    Derived *pd;

    pd = dynamic_cast<Derived *>(pba);
    if (pd == 0) {
      cout << "Null pointer on first type-cast" << endl;
    }

    pd = dynamic_cast<Derived *>(pbb);
    if (pd == 0) {
      cout << "Null pointer on second type-cast" << endl;
    }
  } catch (exception &e) {
    cout << "Exception: " << e.what() << endl;
  }
  return 0;
}
