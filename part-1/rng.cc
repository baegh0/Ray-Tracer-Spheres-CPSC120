
#include "rng.h"

// See the header file for documentation

// Secret global variable that is used by random_double_01()
static RandomNumberGenerator rng01{0, 1};

// Secret global variable that is used by random_double_11()
static RandomNumberGenerator rng11{-1, 1};

double RandomDouble(double min, double max) {
  RandomNumberGenerator rng(min, max);
  return rng.next();
}

double RandomDouble01() { return rng01.next(); }

double RandomDouble11() { return rng11.next(); }
