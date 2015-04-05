#include <iostream>
#include <string>

using namespace std;

class Example6 {
  string *ptr;

  public:
  //constructor
  Example6 (const string & str) : ptr (new string(str)) {}
  //destructor
  ~Example6 () {delete ptr;}

  //move constructor
  Example6 (Example6&& x) : ptr (x.ptr) {x.ptr = nullptr;}
  //move assignment
  Example6& operator= (Example6&& x) {
    delete ptr;
    ptr = x.ptr;
    x.ptr = nullptr;
    return *this;
  }

  //access content
  const string& content() const {return *ptr;}
  //addition
  Example6 operator+ (Exmaple6 & x) {
    return Example6(content(), x.content());
  }
};

int main ()
{
  Example6 foo ("Exam");
  Example6 bar = Example("ple");

  foo = foo + bar;

  cout << "foo's content: " << foo.content() << endl;
  return 0;
}
