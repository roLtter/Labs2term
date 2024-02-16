//
// Created by roLtter on 15.02.2024.
//

#ifndef LABS_CINTEGRALMACROSES_H
#define LABS_CINTEGRALMACROSES_H

#include <iostream>
#include <cmath>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <numeric>
#include <map>
#include <set>
#include <iomanip>
#include <string>

#define stringify(s)    substringify(s)
#define substringify(s) #s

#define INTEGRAL1 (6 * x - pow(x, 4) + 5)
#define INTEGRAL2 (1 / sqrt(4 - x))
#define INTEGRAL3 (1 / (5 - x))
#define INTEGRAL4 (sin(x) + 2)
#define INTEGRAL5 (pow(x, 2) / (pow(x, 3) - 7))
#define INTEGRAL6 (7 * pow(x, 2) + 9)
#define INTEGRAL7 (1 / (sqrt(3 * pow(x, 2) + 2)))
#define INTEGRAL8 (pow((x + 2), 5))
#define INTEGRAL9 (1 / (3 * sqrt(x)))
#define INTEGRAL10 (1 / (2 * x + 5))
#define INTEGRAL11 (pow(x, 2) - x + 1)
#define INTEGRAL12 (1 / (sqrt(pow(x, 2) - 14)))
#define INTEGRAL13 (5 / (pow(x, 2) - 1))
#define INTEGRAL14 (pow(x, 3) - 9 * x + 8)
#define INTEGRAL15 ((pow(x, 8) + 1) / pow(x, 2))
#define INTEGRAL16 (sqrt(x-2))
#define INTEGRAL17 (1 / sqrt(5 * pow(x, 2) + 7))
#define INTEGRAL18 (-7 * x / (2 * pow(x, 2) + 19))
#define INTEGRAL19 (pow(x, 3) + pow(x, 2) + 5)
#define INTEGRAL20 (5 - pow((x - 1), 3))
#define INTEGRAL21 (5 / (sqrt(x) - 7 * x))
#define INTEGRAL22 (1 / sqrt(x + 9))
#define INTEGRAL23 (7 * pow(x, 4) - pow(x, 5) - 2)
#define INTEGRAL24 (pow(x, 2) / (4 * pow(x, 3) + 1))
#define INTEGRAL25 (sqrt(23 - 5 * x))
#define INTEGRAL26 (15 * x - pow(x, 3))
#define INTEGRAL27 ((2 * x - 1) / sqrt(15 - x))
#define INTEGRAL28 ((1 - x) / (5 - x))
#define INTEGRAL29 (sin(x) + 2 - x)
#define INTEGRAL30 (pow(x, 2) / (pow(x, 3) - 15 * x))
#define INTEGRAL31 (7 * pow(x, 5) + 9 * x)
#define INTEGRAL32 (x / sqrt(3 * pow(x, 2) + 2 * x))
#define INTEGRAL33 (pow((x + 2), 2) + 4 * x - 5)
#define INTEGRAL34 (5 * x / (3 * sqrt(x)))
#define INTEGRAL35 (12 * x / (2 * x + 5))
#define INTEGRAL36 (pow(x, 2) - x + 1)
#define INTEGRAL37 (x/(sqrt(pow(x, 2) - 14)))
#define INTEGRAL38 (12 * x /(pow(x, 2) - 1))
#define INTEGRAL39 (5 * pow(x, 3) - 10 * x)
#define INTEGRAL40 ((pow(x, 7) + 1) / pow(x, 2))   //////////////////////////
#define INTEGRAL41 (sqrt(x-2))
#define INTEGRAL42 ((1)/(sqrt(5*pow(x, 2)+7)))
#define INTEGRAL43 ((-7*x)/(2*pow(x, 2)+19))
#define INTEGRAL44 (pow(x, 3)+pow(x, 2)+5)
#define INTEGRAL45 (5-pow((x-1), 3))
#define INTEGRAL46 ((5)/(sqrt(x)-7*x))
#define INTEGRAL47 ((1)/(sqrt(x+9)))
#define INTEGRAL48 (7*pow(x, 4)-pow(x, 5)-2)
#define INTEGRAL49 ((pow(x, 2))/(4*pow(x, 3)+1))
#define INTEGRAL50 (sqrt(23-5*x))

using namespace std;

const double E = 1e-4;
string chosenIntegral = {};
const map<int, pair<double, double>> integrals{
        {1, {-0.5, 2}},
        {2, {-5, 3.5}},
        {3, {0, 4}},
        {4, {-1, 10}},
        {5, {3, 8}},
        {6, {-2, 1}},
        {7, {2, 8}},
        {8, {1, 2}},
        {9, {0.2, 15}},
        {10, {-2, 6}},
        {11, {-2, 3}},
        {12, {6, 8.5}},
        {13, {-0.75, 0}},
        {14, {-1.5, 1}},
        {15, {0.2, 1}},
        {16, {4, 10.4}},
        {17, {-7.3, 5.2}},
        {18, {-12, -3.8}},
        {19, {-1, 1}},
        {20, {-3, -1.5}},
        {21, {0.36, 0.7}},
        {22, {-8, 15}},
        {23, {2, 6.8}},
        {24, {-0.4, 0.8}},
        {25, {-15, 3}},
        {26, {-0.5, 2}},
        {27, {-5, 3.5}},
        {28, {0, 4}},
        {29, {-1, 10}},
        {30, {3, 8}},
        {31, {-2, 1}},
        {32, {2, 8}},
        {33, {1, 2}},
        {34, {0.2, 15}},
        {35, {-2, 6}},
        {36, {-2, 3}},
        {37, {6, 8.5}},
        {38, {-0.75, 0}},
        {39, {-1.5, 1}},
        {40, {0.2, 1}},
        {41, {4, 10.4}},
        {42, {-7.3, 5.2}},
        {43, {-12, -3.8}},
        {44, {-1, 1}},
        {45, {-3, -1.5}},
        {46, {0.36, 0.7}},
        {47, {-8, 15}},
        {48, {2, 6.8}},
        {49, {-0.4, 0.8}},
        {50, {-15, 3}},
};

double f(int choice, double x = 0) {
    switch (choice) {
        case 1: chosenIntegral = stringify(INTEGRAL1); return INTEGRAL1;
        case 2: chosenIntegral = stringify(INTEGRAL2); return INTEGRAL2;
        case 3: chosenIntegral = stringify(INTEGRAL3); return INTEGRAL3;
        case 4: chosenIntegral = stringify(INTEGRAL4); return INTEGRAL4;
        case 5: chosenIntegral = stringify(INTEGRAL5); return INTEGRAL5;
        case 6: chosenIntegral = stringify(INTEGRAL6); return INTEGRAL6;
        case 7: chosenIntegral = stringify(INTEGRAL7); return INTEGRAL7;
        case 8: chosenIntegral = stringify(INTEGRAL8); return INTEGRAL8;
        case 9: chosenIntegral = stringify(INTEGRAL9); return INTEGRAL9;
        case 10: chosenIntegral = stringify(INTEGRAL10); return INTEGRAL10;
        case 11: chosenIntegral = stringify(INTEGRAL11); return INTEGRAL11;
        case 12: chosenIntegral = stringify(INTEGRAL12); return INTEGRAL12;
        case 13: chosenIntegral = stringify(INTEGRAL13); return INTEGRAL13;
        case 14: chosenIntegral = stringify(INTEGRAL14); return INTEGRAL14;
        case 15: chosenIntegral = stringify(INTEGRAL15); return INTEGRAL15;
        case 16: chosenIntegral = stringify(INTEGRAL16); return INTEGRAL16;
        case 17: chosenIntegral = stringify(INTEGRAL17); return INTEGRAL17;
        case 18: chosenIntegral = stringify(INTEGRAL18); return INTEGRAL18;
        case 19: chosenIntegral = stringify(INTEGRAL19); return INTEGRAL19;
        case 20: chosenIntegral = stringify(INTEGRAL20); return INTEGRAL20;
        case 21: chosenIntegral = stringify(INTEGRAL21); return INTEGRAL21;
        case 22: chosenIntegral = stringify(INTEGRAL22); return INTEGRAL22;
        case 23: chosenIntegral = stringify(INTEGRAL23); return INTEGRAL23;
        case 24: chosenIntegral = stringify(INTEGRAL24); return INTEGRAL24;
        case 25: chosenIntegral = stringify(INTEGRAL25); return INTEGRAL25;
        case 26: chosenIntegral = stringify(INTEGRAL26); return INTEGRAL26;
        case 27: chosenIntegral = stringify(INTEGRAL27); return INTEGRAL27;
        case 28: chosenIntegral = stringify(INTEGRAL28); return INTEGRAL28;
        case 29: chosenIntegral = stringify(INTEGRAL29); return INTEGRAL29;
        case 30: chosenIntegral = stringify(INTEGRAL30); return INTEGRAL30;
        case 31: chosenIntegral = stringify(INTEGRAL31); return INTEGRAL31;
        case 32: chosenIntegral = stringify(INTEGRAL32); return INTEGRAL32;
        case 33: chosenIntegral = stringify(INTEGRAL33); return INTEGRAL33;
        case 34: chosenIntegral = stringify(INTEGRAL34); return INTEGRAL34;
        case 35: chosenIntegral = stringify(INTEGRAL35); return INTEGRAL35;
        case 36: chosenIntegral = stringify(INTEGRAL36); return INTEGRAL36;
        case 37: chosenIntegral = stringify(INTEGRAL37); return INTEGRAL37;
        case 38: chosenIntegral = stringify(INTEGRAL38); return INTEGRAL38;
        case 39: chosenIntegral = stringify(INTEGRAL39); return INTEGRAL39;
        case 40: chosenIntegral = stringify(INTEGRAL40); return INTEGRAL40;
        case 41: chosenIntegral = stringify(INTEGRAL41); return INTEGRAL41;
        case 42: chosenIntegral = stringify(INTEGRAL42); return INTEGRAL42;
        case 43: chosenIntegral = stringify(INTEGRAL43); return INTEGRAL43;
        case 44: chosenIntegral = stringify(INTEGRAL44); return INTEGRAL44;
        case 45: chosenIntegral = stringify(INTEGRAL45); return INTEGRAL45;
        case 46: chosenIntegral = stringify(INTEGRAL46); return INTEGRAL46;
        case 47: chosenIntegral = stringify(INTEGRAL47); return INTEGRAL47;
        case 48: chosenIntegral = stringify(INTEGRAL48); return INTEGRAL48;
        case 49: chosenIntegral = stringify(INTEGRAL49); return INTEGRAL49;
        case 50: chosenIntegral = stringify(INTEGRAL50); return INTEGRAL50;
        default: cout << "Invalid input" << endl; exit(1); // unreachable code, will 100% throw an instance of std::out_of_range because of map::at.
    }
}

#endif //LABS_CINTEGRALMACROSES_H
