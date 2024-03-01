#include "slau.hpp"

class Solution{
private:
    static vector<vector<double>> readData() {
        std::ifstream fin("input_data.txt");
        vector<vector<double>> mat;
        for (int i = 0; i < 5; ++i) {
            vector<double> row;
            for (int j = 0; j < 6; ++j) {
                string temp;
                fin >> temp;
                row.push_back(stod(temp));
            }
            mat.push_back(row);
        }
        return mat;
    }

    class GaussMethod{
    private:
        static auto gaussianElimination(vector<vector<double>> m) {
            auto rows = m.size();
            auto cols = m[0].size();

            for (auto i = 0; i < rows; ++i) {
                auto maxRowIndex = i;
                for (auto j = i + 1; j < rows; ++j) {
                    if (std::abs(m[j][i]) > std::abs(m[maxRowIndex][i])) {
                        maxRowIndex = j;
                    }
                }

                swap(m[i], m[maxRowIndex]);

                for (auto j = i + 1; j < rows; ++j) {
                    auto factor = m[j][i] / m[i][i];
                    for (auto k = i; k < cols; ++k) {
                        m[j][k] -= factor * m[i][k];
                    }
                }
            }
            return m;
        }
    public:
        static auto backSubstitution() {
            auto m = gaussianElimination(readData());
            auto rows = static_cast<int>(m.size());
            auto cols = static_cast<int>(m[0].size());

            vector<double> solution(rows);

            for (auto i = rows - 1; i >= 0; --i) {
                solution[i] = m[i][cols - 1];
                for (auto j = i + 1; j < rows; ++j) {
                    solution[i] -= m[i][j] * solution[j];
                }
                solution[i] /= m[i][i];
            }

            return solution;
        }
    };

    class GaussZeidelMethod{
    private:
        auto fun1(double x2, double x3, double x4, double x5){
            return (-mat[0][1]*x2 - mat[0][2]*x3 - mat[0][3]*x4 - mat[0][4]*x5 + mat[0][5]) / mat[0][0];
        }
        auto fun2(double x1, double x3, double x4, double x5){
            return (-mat[1][0]*x1 - mat[1][2]*x3 - mat[1][3]*x4 - mat[1][4]*x5 + mat[1][5]) / mat[1][1];
        }
        auto fun3(double x1, double x2, double x4, double x5){
            return (-mat[2][0]*x1 - mat[2][1]*x2 - mat[2][3]*x4 - mat[2][4]*x5 + mat[2][5]) / mat[2][2];
        }
        auto fun4(double x1, double x2, double x3, double x5){
            return (-mat[3][0]*x1 - mat[3][1]*x2 - mat[3][2]*x3 - mat[3][4]*x5 + mat[3][5]) / mat[3][3];
        }
        auto fun5(double x1, double x2, double x3, double x4) {
            return (-mat[4][0] * x1 - mat[4][1] * x2 - mat[4][2] * x3 - mat[4][3] * x4 + mat[4][5]) / mat[4][4];
        }
        vector<vector<double>> mat = readData();
    public:
        vector<double> calculate() {
            double x1 = 0, x2 = 0, x3 = 0, x4 = 0, x5 = 0;
            double x1temp;
            do {
                x1temp = x1;
                x1 = fun1(x2, x3, x4, x5);
                x2 = fun2(x1, x3, x4, x5);
                x3 = fun3(x1, x2, x4, x5);
                x4 = fun4(x1, x2, x3, x5);
                x5 = fun5(x1, x2, x3, x4);
            }
            while (std::abs(x1 - x1temp) > eps);
            return {x1, x2, x3, x4, x5};
        }
    };

    class CramerMethod{
    private:
        static auto det_2x2(vector<vector<double>> mat) {
            return mat[0][0] * mat[1][1] - mat[0][1] * mat[1][0];
        }

        static auto det_3x3(vector<vector<double>> mat) {
            return mat[0][0] * det_2x2({{mat[1][1], mat[1][2]}, {mat[2][1], mat[2][2]}})
                   - mat[0][1] * det_2x2({{mat[1][0], mat[1][2]}, {mat[2][0], mat[2][2]}})
                   + mat[0][2] * det_2x2({{mat[1][0], mat[1][1]}, {mat[2][0], mat[2][1]}});
        }

        static auto det_4x4(std::vector<std::vector<double>> mat) {
            return mat[0][0] * det_3x3({{mat[1][1], mat[1][2], mat[1][3]}, {mat[2][1], mat[2][2], mat[2][3]}, {mat[3][1], mat[3][2], mat[3][3]}})
                   - mat[0][1] * det_3x3({{mat[1][0], mat[1][2], mat[1][3]}, {mat[2][0], mat[2][2], mat[2][3]}, {mat[3][0], mat[3][2], mat[3][3]}})
                   + mat[0][2] * det_3x3({{mat[1][0], mat[1][1], mat[1][3]}, {mat[2][0], mat[2][1], mat[2][3]}, {mat[3][0], mat[3][1], mat[3][3]}})
                   - mat[0][3] * det_3x3({{mat[1][0], mat[1][1], mat[1][2]}, {mat[2][0], mat[2][1], mat[2][2]}, {mat[3][0], mat[3][1], mat[3][2]}});
        }

        static auto det_5x5(vector<vector<double>> mat) {
            return mat[0][0] * det_4x4({{mat[1][1], mat[1][2], mat[1][3], mat[1][4]}, {mat[2][1], mat[2][2], mat[2][3], mat[2][4]}, {mat[3][1], mat[3][2], mat[3][3], mat[3][4]}, {mat[4][1], mat[4][2], mat[4][3], mat[4][4]}})
                   - mat[0][1] * det_4x4({{mat[1][0], mat[1][2], mat[1][3], mat[1][4]}, {mat[2][0], mat[2][2], mat[2][3], mat[2][4]}, {mat[3][0], mat[3][2], mat[3][3], mat[3][4]}, {mat[4][0], mat[4][2], mat[4][3], mat[4][4]}})
                   + mat[0][2] * det_4x4({{mat[1][0], mat[1][1], mat[1][3], mat[1][4]}, {mat[2][0], mat[2][1], mat[2][3], mat[2][4]}, {mat[3][0], mat[3][1], mat[3][3], mat[3][4]}, {mat[4][0], mat[4][1], mat[4][3], mat[4][4]}})
                   - mat[0][3] * det_4x4({{mat[1][0], mat[1][1], mat[1][2], mat[1][4]}, {mat[2][0], mat[2][1], mat[2][2], mat[2][4]}, {mat[3][0], mat[3][1], mat[3][2], mat[3][4]}, {mat[4][0], mat[4][1], mat[4][2], mat[4][4]}})
                   + mat[0][4] * det_4x4({{mat[1][0], mat[1][1], mat[1][2], mat[1][3]}, {mat[2][0], mat[2][1], mat[2][2], mat[2][3]}, {mat[3][0], mat[3][1], mat[3][2], mat[3][3]}, {mat[4][0], mat[4][1], mat[4][2], mat[4][3]}});
        }
    public:
        static auto solveUsingCramer5x5() {
            auto A = readData();
            vector<double> B;
            for (auto& row : A) {
                B.push_back(row.back());
                row.erase(row.end());
            }

            auto n = A.size();
            auto detA = det_5x5(A);

            if (detA == 0) {
                cout << "Determinant is zero. No solution exists." << endl;
                exit(1);
            }
            vector<vector<double>> tempA = A;
            vector<double> solutions;

            for (auto i = 0; i < n; ++i) {
                for (auto j = 0; j < n; ++j) {
                    tempA[j][i] = B[j];
                }
                auto detAi = det_5x5(tempA);
                solutions.push_back(detAi / detA);
                for (auto j = 0; j < n; ++j) {
                    tempA[j][i] = A[j][i];
                }
            }

            return solutions;
        }
    };

public:
    static auto toFile(){
        GaussZeidelMethod method;
        std::ofstream fs("answer_data.txt", std::ios::app);
        fs << "Gauss method:" << endl;
        auto iter = 1;
        for (auto g : GaussMethod::backSubstitution()) {
            fs << std::setprecision(20) << "x" << iter << " = " << g << endl;
            ++iter;
        }
        iter = 1;
        fs << endl << endl;
        fs << "Gauss Zeidel method:" << endl;
        for (auto g : method.calculate()) {
            fs << std::setprecision(20) << "x" << iter << " = " << g << endl;
            ++iter;
        }
        iter = 1;
        fs << endl << endl;
        fs << "Cramer method:" << endl;
        for (auto g : CramerMethod::solveUsingCramer5x5()) {
            fs << std::setprecision(20) << "x" << iter << " = " << g << endl;
            ++iter;
        }
        fs.close();
    }
};

int main(){
    preparation();
    Solution::toFile();
    return 0;
}