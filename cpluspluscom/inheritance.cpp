#include <iostream>
using namespace std;

class Output {
  public:
    static void print (int i);
};

void Output :: print (int i) {
  cout << i << endl;
}

class Polygon {
  protected:
    int width, height;
  public:
    void set_values(int a, int b) {
      width = a;
      height = b;
    }
};

class Rectangle : public Polygon, public Output {
  public:
    int area () {
      return width * height;
    }
};

class Triangle : public Polygon, public Output {
  public:
    int area () {
      return width * height / 2;
    }
};

class Mother {
  public:
    Mother () {
      cout << "Mother: no params" << endl;
    };

    Mother (int a) {
      cout << "Mother: params" << endl;
    };
};

class Daughter : public Mother {
  public:
    Daughter (int a) {
      cout << "Daughter: params" << endl;
    }
};

class Son : public Mother {
  public:
    Son (int a) : Mother (a) {
      cout << "Son: params" << endl;
    }
};

int main ()
{
  Rectangle rect;
  Triangle tri;

  rect.set_values(4, 5);
  tri.set_values(4, 5);

  rect.print(rect.area());
  tri.print(tri.area());

  Daughter kelly(1);
  Son bud(1);

  return 0;
}
