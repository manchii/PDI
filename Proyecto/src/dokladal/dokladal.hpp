
#include <ltiChannel8.h>

// Standard Headers
#include <iostream>
#include <cstdlib>
#include <string>
#include <fstream>
#include <chrono>
#include <vector>
#include <deque>
#include <algorithm>


using std::cout;
using std::cerr;
using std::endl;


void dokladal(lti::channel8 &dst, const lti::channel8 &src, const int wsize);
