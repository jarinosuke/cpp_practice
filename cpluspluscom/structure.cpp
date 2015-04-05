#include <iostream>
#include <string>
#include <sstream>

using namespace std;

struct movie_t {
  string title;
  int year;
};

void print_movie(movie_t movie);

int main ()
{
  string mystr;

  movie_t amovie;
  movie_t * pmovie;
  pmovie = &amovie;

  cout << "Enter Title: ";
  getline(cin, pmovie->title);
  cout << "Enter Year: ";
  getline(cin, mystr);
  stringstream(mystr) >> pmovie->year;

  return 0;
}

void print_movie(movie_t movie)
{
  cout << movie.title;
  cout << "(" << movie.year << ")";
}
