#include <iostream>
using namespace std;

int main ()
{
  int firstValue, secondValue;
  int * myPointer;

  myPointer = &firstValue;
  *myPointer = 10;
  myPointer = &secondValue;
  *myPointer = 20;

  cout << firstValue << endl;
  cout << secondValue << endl;


  int v3 = 5, v4 = 15;
  int * p1, * p2;

  p1 = &v3;
  p2 = &v4;

  *p1 = 10; //v3 = 10, v4 = 15
  *p2 = *p1; //v3 = 10, v4 = 10
  p1 = p2; 
  *p1 = 20; //v3 = 10, v4 = 20

  cout << v3 << endl;
  cout << v4 << endl;
}
