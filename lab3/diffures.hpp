//
// Created by highl on 17.02.2024.
//

#ifndef LAB3_DIFFURES_HPP
#define LAB3_DIFFURES_HPP

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <fstream>
#include <iomanip>
#define DIFF (sin(x) - cos(x)*(2*y+1))
#define DIFF1 (y/x - 2/pow(x,2))

#define stringify(s) substringify(s)
#define substringify(s) #s

using std::string;
using std::vector;
using std::cout;
using std::cin;
using std::endl;
using std::pair;

double f(double x, double y){
   return DIFF;
}

#endif //LAB3_DIFFURES_HPP
