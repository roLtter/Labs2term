#include "cIntegralMacroses.h"

int choice;
double a, b;
class Methods{
public:
    static double methodLeftRectangle(int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; i++) {
            fx = f(choice, a + i * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodRightRectangle(int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx = f(choice, a + (i+1) * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodMiddleRectangle(int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx =  f(choice, a + static_cast<double>(2 * i + 1) / 2 * h);
            sum += fx;
        }
        return sum * h;
    }

    static double methodTrapezoid(int n) {
        double h  = (b - a) / n;
        double sum = 0.0, fx;
        for (int i = 0; i < n; ++i) {
            fx = (f(choice, a + i*h) + f(choice, a + (i+1)*h)) / 2;
            sum += fx;
        }
        return sum * h;
    }

    static double methodSimpson(int n) {
        const double h = (b-a)/n;
        double k1 = 0, k2 = 0;
        for(int i = 1; i < n; i += 2) {
            k1 += f(choice, a + i*h);
            k2 += f(choice, a + (i+1)*h);
        }
        return h/3*(f(choice, a) + 4*k1 + 2*k2);
    }

    static double methodGauss(int n) {
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
     void callLeftRectangle() {
        string methodName = "methodLeftRectangle";
        int n = 10;
        double s1 = Methods::methodLeftRectangle(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodLeftRectangle(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callRightRectangle() {
        string methodName = "methodRightRectangle";
        int n = 10;
        double s1 = Methods::methodRightRectangle(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodRightRectangle(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callMiddleRectangle() {
        string methodName = "methodMiddleRectangle";
        int n = 10;
        double s1 = Methods::methodMiddleRectangle(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodMiddleRectangle(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callTrapezoid() {
        string methodName = "methodTrapezoid";
        int n = 10;
        double s1 = Methods::methodTrapezoid(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodTrapezoid(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callSimpson() {
        string methodName = "methodSimpson";
        int n = 10;
        double s1 = Methods::methodSimpson(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodSimpson(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }

    void callGauss() {
        string methodName = "methodGauss";
        int n = 2;
        double s1 = Methods::methodGauss(n), s;
        do {
            N.push_back(n);
            H.push_back((b - a) / n);
            S1.push_back(s1);
            s = s1;
            n *= 2;
            s1 = Methods::methodGauss(n);
            S1_S.push_back(abs(s1-s));
        }
        while (abs(s1 - s) > E);
        printArrays(methodName);
    }


    void printArrays(const string& methodName){
        ofstream fout("output.txt", ios::app);
        fout << "\t\t\t\t\t\t\t\t\t\t\t  " << methodName << ":" << endl << endl;
        fout << "  Number of divisions(n)\t\t The value of h\t\t\t The integral value s1\t\t\t  The dif |s1-s|" << endl;
        for (int i = 0; i < N.size(); i++) {
            fout << "|        " << left << setw(15) << N[i] << "|        " << setw(20) << H[i] << "|        " << setw(20) << setprecision(10) << S1[i] <<  "|        " << setw(20) << S1_S[i] << "|" << endl;
        }
        double finalCalc = S1[N.size() - 1];
        fout << endl << "Final method result:   " << finalCalc << endl;
        val.insert(finalCalc);
        if (methodName == "methodGauss") {
            fout << endl << endl;
            double average = getAverageValue();
            fout << "Average result:  " << average << endl << endl;

            fout << "In range from " << a << " to " << b << ", { " << chosenIntegral.substr(1, chosenIntegral.size() - 2) << " } ~= " << average << endl;
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

void get_a_b(){
    a = integrals.at(choice).first;
    b = integrals.at(choice).second;
}


void Terminal() {
    ofstream preparation("output.txt");
    preparation.clear();
    cout << "Input the value 1-50 what integral you want to calculate." << endl;
    cin >> choice;
    f(choice);
    get_a_b();
    preparation << "You've chosen Integral №" << choice << ":  " << chosenIntegral.substr(1, chosenIntegral.length() - 2) << " to calculate from " << a << " to " << b << "."<< endl << endl;
    if (choice == 30){
        preparation << chosenIntegral.substr(1, chosenIntegral.length() - 2) << " to calculate from " << a << " to " << b<< " Can't be solved since it's a convergent integral." << endl;
        preparation.close();
        exit(0);
    }
    preparation.close();
    Calls c;
    c.callLeftRectangle();
    c.callRightRectangle();
    c.callMiddleRectangle();
    c.callTrapezoid();
    c.callSimpson();
    c.callGauss();
}

int main() {
    Terminal();
    return 0;
}