#include "cIntegralMacroses.h"

int choice;

class Methods{
public:
    static double methodLeftRectangle(double a, double b, int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; i++) {
            fx = f(choice, a + i * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodRightRectangle(double a, double b, int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx = f(choice, a + (i+1) * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodMiddleRectangle(double a, double b, int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx =  f(choice, a + static_cast<double>(2 * i + 1) / 2 * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodTrapezoid(double a, double b, int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx = (f(choice, a + i*h) + f(choice, a + (i+1)*h)) / 2;
            sum += fx;
        }
        return sum * h;
    }

    static double methodSimpson(double a, double b, int n) {
        const double h = (b-a)/n;
        double k1 = 0, k2 = 0;
        for(int i = 1; i < n; i += 2) {
            k1 += f(choice, a + i*h);
            k2 += f(choice, a + (i+1)*h);
        }
        return h/3*(f(choice, a) + 4*k1 + 2*k2);
    }

    static double methodGauss(double a, double b, int n) {
        double h = (b - a) / n,
               c = h / sqrt(3),
               d = h - c,
               x = a + d/2,
               s = 0;

        for (int i = 0; i<n; i++) {
            s+=f(choice, x); x+=c;
            s+=f(choice, x); x+=d;
        }
        return s*h/2;
    }
};

class Calls{
public:
     void callLeftRectangle(double a, double b) {
        string methodName = "methodLeftRectangle";
        int n = 10;
        double s1 = Methods::methodLeftRectangle(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodLeftRectangle(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callRightRectangle(double a, double b) {
        string methodName = "methodRightRectangle";
        int n = 10;
        double s1 = Methods::methodRightRectangle(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodRightRectangle(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callMiddleRectangle(double a, double b) {
        string methodName = "methodMiddleRectangle";
        int n = 10;
        double s1 = Methods::methodMiddleRectangle(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodMiddleRectangle(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callTrapezoid(double a, double b) {
        string methodName = "methodTrapezoid";
        int n = 10;
        double s1 = Methods::methodTrapezoid(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodTrapezoid(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callSimpson(double a, double b) {
        string methodName = "methodSimpson";
        int n = 10;
        double s1 = Methods::methodSimpson(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodSimpson(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callGauss(double a, double b) {
        string methodName = "methodGauss";
        int n = 2;
        double s1 = Methods::methodGauss(a, b, n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodGauss(a, b, n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }


    void printArrays(const string& methodName){
        ofstream fout("output.txt", ios::app);
        fout << "\t\t\t\t\t\t\t\t\t\t\t  " << methodName << ":" << endl << endl;
        fout << "   Number of divisions\t\t   The value of h\t\t\t The integral value s1\t\t\t  The dif |s1-s|" << endl;
        for (int i = 0; i < N.size(); i++) {
            fout << "|        " << left << setw(15) << N[i] << "|        " << setw(20) << H[i] << "|        " << setw(20) << setprecision(10) << S1[i] <<  "|        " << setw(20) << S1_S[i] << "|" << endl;
        }
        double finalCalc = S1[N.size() - 1];
        fout << endl << "Final method result:   " << finalCalc << endl;
        val.insert(finalCalc);
        if (methodName == "methodGauss") {
            fout << endl << endl;
            fout << "Average value: " << getAverageValue() << endl;
            exit(0);
        }
        fout.close();
        N.clear();
        H.clear();
        S1.clear();
        S1_S.clear();
    }

    double getAverageValue(){
        return accumulate(val.begin(), val.end(), 0.0) / static_cast<double>(val.size());
     }

private:
    vector<double> N;
    vector<double> H;
    vector<double> S1;
    vector<double> S1_S;

    set<double> val;
};

void Terminal() {
    ofstream preparation("output.txt");
    preparation.clear();
    cout << "Input the value 1-50 what integral you want to calculate." << endl;
    cin >> choice;
    f(choice);
    double a = integrals.at(choice).first;
    double b = integrals.at(choice).second;
    preparation << "You've chosen Integral №" << choice << ":  " << chosenIntegral.substr(1, chosenIntegral.length() - 2) << " to calculate from " << a << " to " << b << "."<< endl << endl;
    if (choice == 30){
        preparation << chosenIntegral.substr(1, chosenIntegral.length() - 2) << " to calculate from " << a << " to " << b<< " Can't be solved since it's a convergent integral." << endl;
        preparation.close();
        exit(0);
    }
    preparation.close();
    Calls c;
    c.callLeftRectangle(a, b);
    c.callRightRectangle(a, b);
    c.callMiddleRectangle(a, b);
    c.callTrapezoid(a, b);
    c.callSimpson(a, b);
    c.callGauss(a, b);
}

int main() {
    Terminal();
    return 0;
}