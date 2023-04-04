#include <iostream>
#include <cmath> // 7-4
#include "MathFunctions.h"

// a hack square root calculation using simple operations
double mysqrt(double x)
{
  if (x <= 0) 
  {
    return 0;
  }

//7-5: If log and exp are available on the system, then use them to compute the square root in the mysqrt function
#if defined(HAVE_LOG) && defined(HAVE_EXP)
  double result = std::exp(std::log(x) * 0.5);
  std::cout << "Computing sqrt of " << x << " to be " << result
      << " using log and exp" << std::endl;
#else
  double result = x;
#endif

  // do ten iterations
  for (int i = 0; i < 10; ++i) 
  {
    if (result <= 0) {
      result = 0.1;
    }
    double delta = x - (result * result);
    result = result + 0.5 * delta / result;
    std::cout << "Computing sqrt of " << x << " to be " << result << std::endl;
  }
  return result;
}
