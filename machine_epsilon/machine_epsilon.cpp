#include <limits> 
#include <string>
#include <iostream>

typedef union
{
  long long ll;
  double d;
} data;

int main()
{
  data s;
  s.d = 1.0;
  s.ll++;
  double ep = s.d - 1.0;
  std::cout << "manual: \t" << ep << std::endl;
  std::cout << "limits: \t" << std::numeric_limits<double>::epsilon() << std::endl;
}
