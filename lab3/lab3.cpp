#include "diffures.hpp"

class Solution {
public:
    explicit Solution(double x0, double y0) : y0(y0), x0(x0) {
        this->x0 = x0;
        this->y0 = y0;
    }

    void methodEuler(double h){
        string methodName = "Euler";
        double x = x0, y = y0;
        do {
            valuesX.push_back(x);
            valuesY.push_back(y);
            y += h * f(x, y);
            x += h;
        }
        while (x <= this->x0 + 10);
        printToFile(methodName, h);
    }

    void modifiedEulerMethod(double h) {
        string methodName = "Modified Euler";
        double x = x0;
        double y = y0;
        do {
            valuesY.push_back(y);
            double k1 = h * f(x, y);
            double k2 = h * f(x + h / 2, y + k1 / 2);

            y += k2;
            x += h;
        }
        while (x <= this->x0 + 10);
        printToFile(methodName);
    }

    void improvedEulerMethod(double h) {
        string methodName = "Improved Euler";
        double x = x0;
        double y = y0;
        do{
            valuesY.push_back(y);
            double k1 = h * f(x, y);
            double k2 = h * f(x + h, y + k1);

            y += 0.5 * (k1 + k2);
            x += h;
        }
        while (x <= this->x0 + 10);
        printToFile(methodName);
    }

    void rungeKuttaMethod(double h) {
        string methodName = "Runge Kutta";
        double x = x0;
        double y = y0;
        do {
            valuesY.push_back(y);
            double k1 = h * f(x, y);
            double k2 = h * f(x + h / 2, y + k1 / 2);
            double k3 = h * f(x + h / 2, y + k2 / 2);
            double k4 = h * f(x + h, y + k3);

            y += (k1 + 2 * k2 + 2 * k3 + k4) / 6;
            x += h;
        }while (x <= this->x0 + 10);
        printToFile(methodName);
    }

    void backwardEulerMethod(double h) {
        string methodName = "Backward Euler";
        double x = this->x0;
        double y = this->y0;
        do {
            valuesY.push_back(y);
            y += h * f(x + h, y);
            x += h;
        }
        while (x <= this->x0 + 10);
        printToFile(methodName);
    }

    static void preparation(){
        std::ofstream file ("output.txt");
        file.clear();
        file << "Origin equation:" << endl;
        file << "y' = " << stringify(DIFF);
        file << " with initial condition: y(1) = 0.5" << endl;
        file.close();
    }

private:
    vector<double> valuesY;
    vector<double> valuesX;
    double x0;
    double y0;

    void printToFile(const string& methodName, double stepValue = 0){
        std::fstream file ("output.txt", std::ios::app);
        if (methodName == "Euler"){
            file << endl << endl << "\t\t";
            if (stepValue != 0.01){
                file << " ";
            }
            file << "The step value is: " << stepValue << endl << "x values:       |";
            for (auto i : valuesX){
                file << std::setprecision(10) << std::setw(15) << i << "   |";
            }
            file << endl;
        }
        file << methodName << "  ";
        if (methodName == "Runge Kutta"){
            file << "   ";
        }
        if (methodName == "Euler"){
            file << "         ";
        }
        file << "|";
        for (auto i : valuesY){
            file << std::setprecision(10) << std::setw(15) << i << "   |";
        }
        valuesX.clear();
        valuesY.clear();
        file << endl;
    }
};

int main(){
    Solution sol(1, 0.5);
    vector<double> step = {0.5, 0.1, 0.01};
    Solution::preparation();
    for(auto h : step){
        sol.methodEuler(h);
        sol.modifiedEulerMethod(h);
        sol.improvedEulerMethod(h);
        sol.rungeKuttaMethod(h);
        sol.backwardEulerMethod(h);
    }
    return 0;
}