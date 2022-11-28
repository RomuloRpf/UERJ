#include <string>
#include <iostream>

int main()
{
  std::string a = "x", b = "y";
  int c = 3;

#pragma omp parallel firstprivate(a, c) shared(b)
  {
    a += "k";
    c += 7;
    std::cout << "A becomes (" << a << "), b is (" << b << ")" << std::endl;
  }
}