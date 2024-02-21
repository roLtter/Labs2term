#include "diffures.h"

int choice;

class Solution {
public:
    void methodEuler(double h, double x0, double y0){
        string methodName = "Euler";
        double x = x0, y = y0;
        double xtemp = x0;
        int iteration = 0;
        do {
            cout << x << "   " << y << endl;
            valuesX.push_back(x);
            valuesY.push_back(y);
            y = y0 + h * f(x0, y0, choice);
            x0 = x;
            y0 = y;
            x += h;
            iteration++;
        }
        while (x <= xtemp + 10);
        printToFile(methodName);
    }







    static void preparation(){
        ofstream file ("data.txt");
        file.clear();
        file << "Government" << endl << endl;
        file << endl;
    }

private:
    vector<double> valuesY;
    vector<double> valuesX;
    void printToFile(const string& methodName){
        fstream file ("data.txt", ios::app);
        if (methodName == "Euler"){
            file << "      ";
            for (auto i : valuesX){
                file << setw(10) << i << "   ";
            }
        }
        file << endl << methodName << "  ";
        for (auto i : valuesY){
            file << setw(10) << i << "     ";
        }
        valuesY.clear();
        file << endl;
    }
};

int main(){
    cin >> choice;
    Solution sol;
    double x0 = borders.at(choice).first;
    double y0 = borders.at(choice).second;
    double step[3] = {0.5, 0.1, 0.01};
    Solution::preparation();
    for(auto h : step){
        sol.methodEuler(h, x0, y0);
    }
    return 0;
}