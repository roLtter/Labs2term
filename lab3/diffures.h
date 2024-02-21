//
// Created by highl on 17.02.2024.
//

#ifndef LAB3_DIFFURES_H
#define LAB3_DIFFURES_H

#include <iostream>
#include <string>
#include <vector>
#include <algorithm>
#include <cmath>
#include <map>
#include <set>
#include <unordered_set>
#include <fstream>
#include <iomanip>
#define DIFF1 (y/x - 2/pow(x,2))

#define stringify(s) substringify(s)
#define substringify(s) #s
using namespace std;

string chosendiff;

const map <int, pair<double, double>> borders = {
        {1, {1, 1}}
};



double f(double x, double y, int choice){
    switch (choice){
        case 1: chosendiff = stringify(DIFF1); return DIFF1;
    }
   return 0;
}






#endif //LAB3_DIFFURES_H
