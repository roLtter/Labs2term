//
// Created by holer on 2/26/2024.
//

#ifndef LAB4_SLAU_HPP
#define LAB4_SLAU_HPP

#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <fstream>
#include <cmath>
#include <iomanip>

using::std::vector;
using::std::string;
using::std::cout;
using::std::endl;
using::std::cin;

const double eps = 1e-5;

void preparation(){
    std::ofstream fout("answer_data.txt");
    fout.clear();
    fout.close();
}

#endif //LAB4_SLAU_HPP
