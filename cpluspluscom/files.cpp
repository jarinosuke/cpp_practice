#include <iostream>
#include <fstream>

using namespace std;


int main ()
{
  /*
  ofstream myfile;
  myfile.open("example.txt");
  myfile << "Write something.\n";
  myfile.close();
  */

  string line;
  ifstream myfile("example.txt");
  if (myfile.is_open()) {
    while (getline(myfile, line)) {
      cout << line << endl;
    }
    myfile.close();
  } else {
    cout << "Unable to open file." << endl;
  }
  return 0;
}
