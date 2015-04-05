#include <iostream>
using namespace std;

class Rectangle
{
  int width, height;
  public:
  Rectangle ();
  Rectangle (int x, int y) : width(x), height(y){};
  int area () {
    return width * height;
  };
};

Rectangle::Rectangle ()
{
  width = 5;
  height = 5;
}

int main ()
{
  Rectangle obj(3, 4);
  Rectangle *a, *b, *c;

  a = &obj;
  b = new Rectangle(5, 6);
  c = new Rectangle[2] {{2, 5}, {3, 6}};

  cout << "obj's area" << obj.area() << endl;
  cout << "a's area" << a->area() << endl;
  cout << "b's area" << b->area() << endl;
  cout << "c[0]'s area" << c[0].area() << endl;
  cout << "c[1]'s area" << c[1].area() << endl;

  delete b;
  delete[] c;
  return 0;
}
