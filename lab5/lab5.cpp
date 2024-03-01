#include "mnk.hpp"

class Solution {
private:
    static auto leastSquaresMethod(const vector<double>& x, const vector<double>& y) {
        auto n = static_cast<int>(x.size());
        auto degree = 5;
        vector<double> coefficients(6);
        vector<vector<double>> matrix(degree + 1, vector<double>(degree + 2, 0.0));
        for (auto i = 0; i <= degree; ++i) {
            for (auto j = 0; j <= degree; ++j) {
                for (auto k = 0; k < n; ++k) {
                    matrix[i][j] += pow(x[k], i + j);
                }
            }
            for (auto k = 0; k < n; ++k) {
                matrix[i][degree + 1] += pow(x[k], i) * y[k];
            }
        }

        for (auto i = 0; i < degree; ++i) {
            for (auto j = i + 1; j <= degree; ++j) {
                auto ratio = matrix[j][i] / matrix[i][i];

                for (auto k = i; k <= degree + 1; ++k) {
                    matrix[j][k] -= ratio * matrix[i][k];
                }
            }
        }

        for (auto i = degree; i >= 0; --i) {
            coefficients[i] = matrix[i][degree + 1];

            for (auto j = degree; j > i; --j) {
                coefficients[i] -= matrix[i][j] * coefficients[j];
            }

            coefficients[i] /= matrix[i][i];
        }
        return coefficients;
    }

    static auto gaussianElimination(const vector<double>& x, const vector<double>& y) {
        auto n = 6;
        vector<vector<double>> matrix(n, vector<double>(n + 1, 0));

        for (auto i = 0; i < n; ++i) {
            for (auto j = 0; j < n; ++j) {
                auto sum_x = 0.0;
                for (double xi : x)
                    sum_x += pow(xi, i + j);
                matrix[i][j] = sum_x;
            }

            auto sum_yx = 0.0;
            for (auto j = 0; j < x.size(); ++j)
                sum_yx += y[j] * pow(x[j], i);
            matrix[i][n] = sum_yx;
        }

        n = static_cast<int>(matrix.size());
        for (auto i = 0; i < n; ++i) {
            auto pivotRow = i;
            for (auto j = i + 1; j < n; ++j) {
                if (std::abs(matrix[j][i]) > std::abs(matrix[pivotRow][i]))
                    pivotRow = j;
            }

            if (pivotRow != i)
                swap(matrix[i], matrix[pivotRow]);

            for (auto j = i + 1; j < n; ++j) {
                auto factor = matrix[j][i] / matrix[i][i];
                for (auto k = i; k < n + 1; ++k)
                    matrix[j][k] -= factor * matrix[i][k];
            }
        }

        vector<double> coefficients(n);
        for (auto i = n - 1; i >= 0; --i) {
            coefficients[i] = matrix[i][n] / matrix[i][i];
            for (auto j = i - 1; j >= 0; --j)
                matrix[j][n] -= matrix[j][i] * coefficients[i];
        }
        return coefficients;
    }
public:
    static void toFile() {
        vector<double> x;
        vector<double> y;
        string xStr;
        string yStr;
        std::ifstream file("input_data.txt");
        for (auto i = 0; i < 9; ++i) {
            file >> xStr;
            x.push_back(stod(xStr));
        }
        for (auto i = 0; i < 9; ++i) {
            file >> yStr;
            y.push_back(stod(yStr));
        }
        file.close();
        std::ofstream output("output_data.txt");
        output.clear();
        auto i = 5;
        auto coefficients = leastSquaresMethod(x, y);
        reverse(coefficients.begin(), coefficients.end());
        output << "MNK method:" << endl;
        for (auto elem : coefficients){
            output << "x^" << i << " = " << std::setprecision(20) << elem << endl;
            --i;
        }
        output << "final equation:" << endl;
        i = 5;
        for (auto elem : coefficients) {
            isPositive(elem) ? output << " + " << std::setprecision(10) << elem : output << " - " << std::setprecision(10) << -1*elem;
            output << "x^" << i;
            --i;
        }
        output << " = 0" << endl << endl << endl;
        coefficients = gaussianElimination(x, y);
        reverse(coefficients.begin(), coefficients.end());
        i = 5;
        output << "Gauss Elimination method:" << endl;
        for (auto elem : coefficients){
            output << "x^" << i << " = " << std::setprecision(20) << elem << endl;
            --i;
        }
        output << "final equation:" << endl;
        i = 5;
        for (auto elem : coefficients) {
            isPositive(elem) ? output << " + " << std::setprecision(10) << elem : output << " - " << std::setprecision(10) << -1*elem;
            output << "x^" << i;
            --i;
        }
        output << " = 0";
        output.close();
    }
};

int main(){
    Solution::toFile();
    return 0;
}