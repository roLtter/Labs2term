#include <iostream>
#include <cstdlib>
#include <ctime>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>

using namespace std;

enum class Decision {
    SIMPLE_SORT,
    QUICK_SORT,
    BUBBLE_SORT,
    HEAP_SORT,
    COMB_SORT,
};

class MySort {
private:
    unsigned long long int iterations = 0;
public:
    void heapify(vector<int> &arr, int size, int i) {
        int max = i;
        int left = 2 * i + 1;
        int right = 2 * i + 2;

        if (left < size && arr[left] > arr[max]) {
            max = left;
        }

        if (right < size && arr[right] > arr[max]) {
            max = right;
        }

        if (max != i) {
            int temp = arr[i];
            arr[i] = arr[max];
            arr[max] = temp;
            ++iterations;
            heapify(arr, size, max);
        }
    }

    void heapSorting(vector<int> &arr) {
        int size = static_cast<int>(arr.size());
        for (int i = size / 2 - 1; i >= 0; i--) {
            heapify(arr, size, i);
        }

        for (int i = size - 1; i >= 0; i--) {
            int temp = arr[0];
            arr[0] = arr[i];
            arr[i] = temp;
            ++iterations;
            heapify(arr, i, 0);
        }
    }

    unsigned long long int getIterations() const {
        return iterations;
    }
};

class Solution {
public:
    explicit Solution(int n) : N(n) {
        N = n;
    }

    void Generation() {
        ofstream input_file_stream(name_file_input);
        for (int i = 0; i < N - 1; ++i) {
            input_file_stream << left_border + (2 * rand()) % (right_border - left_border + 1) << " ";
        }
        input_file_stream << left_border + (2 * rand()) % (right_border - left_border + 1);
        input_file_stream.close();
        ReadFile();
    }

    void simpleSortMethod() {
        string name_sort = "Simple sort: "s;
        int min_index;
        unsigned long long int count = 0,
                                             start_time = clock();

        for (int k = 0; k < N - 1; k++) {
            min_index = k;
            for (int i = 1 + k; i < N; i++) {
                if (random_numbers_simple[i] < random_numbers_simple[min_index]) {
                    min_index = i;
                }
            }
            swap(random_numbers_simple[k], random_numbers_simple[min_index]);
            count++;
        }
        long double search_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
        cout << name_sort << "DONE" << endl;
        writeTimes(search_time, count, name_sort);

    }

    void bubbleSortMethod() {
        string name_sort = "Bubble sort: "s;
        int length = N;
        unsigned long long int count = 0,
                                             start_time = clock();
        while (length != 0) {
            int max_index = 0;
            for (int i = 1; i < length; ++i) {
                if (random_numbers_bubble[i - 1] > random_numbers_bubble[i]) {
                    swap(random_numbers_bubble[i - 1], random_numbers_bubble[i]);
                    ++count;
                    max_index = i;
                }
            }
            length = max_index;
        }
        long double search_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
        cout << name_sort << "DONE" << endl;
        writeTimes(search_time, count, name_sort);
    }

    void combSortMethod() {
        string name_sort = "Comb sort: "s;
        double factor = 1.2473309,
                step = N - 1;
        unsigned long long int count = 0,
                                             start_time = clock();
        while (step >= 1) {
            for (int i = 0; i + step < N; ++i) {
                if (random_numbers_comb[i] > random_numbers_comb[i + static_cast<int>(step)]) {
                    swap(random_numbers_comb[i], random_numbers_comb[i + static_cast<int>(step)]);
                    ++count;
                }
            }
            step /= factor;
        }
        long double search_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
        cout << name_sort << "DONE" << endl;
        writeTimes(search_time, count, name_sort);

    }

    void quickSortMethod() {
        string name_sort = "Quick Sort: "s;
        unsigned long long int count_iterations = 0,
                start_time = clock();
        sort(random_numbers_quick.begin(), random_numbers_quick.end(), [&count_iterations](auto el1, auto el2) -> bool {
            if (el1 < el2) {
                ++count_iterations;
                return true;
            }
            return false;
        });
        long double search_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
        cout << name_sort << "DONE" << endl;
        writeTimes(search_time, count_iterations, name_sort);
    }

    void heapSortMethod() {
        string name_sort = "Heap Sort: "s;
        MySort heapSort;
        unsigned long long int start_time = clock();
        heapSort.heapSorting(random_numbers_heap);
        long double search_time = static_cast<double>(clock() - start_time) / CLOCKS_PER_SEC;
        cout << name_sort << "DONE" << endl;
        writeTimes(search_time, heapSort.getIterations(), name_sort);
    }

    void Commander() {
        cout << endl << "Available decisions to print: " << endl;
        for (const auto &[name, decision]: decisions) {
            cout << name << endl;
        }
        cout << "Or type 1 to exit" << endl;
        string input;
        cout << "----------------------------------" << endl;
        cin >> input;
        if (input == "1") {
            exit(0);
        }
        switch (decisions.at(input)) {
            case Decision::QUICK_SORT: writeElems("Quick Sort", random_numbers_quick); break;
            case Decision::BUBBLE_SORT: writeElems("Bubble Sort", random_numbers_bubble); break;
            case Decision::HEAP_SORT: writeElems("Heap Sort", random_numbers_heap); break;
            case Decision::COMB_SORT: writeElems("Comb Sort", random_numbers_comb); break;
            case Decision::SIMPLE_SORT: writeElems("Simple Sort", random_numbers_simple); break;
            default: cout << "Invalid input" << endl; break; // never reached, throwing an instance of 'std::out_of_range' because of map::at
        }
        decisions.erase(input);
    }

private:
    int N;
    const string name_file_input = "input.txt",
                        name_file_times = "times.txt";
    const int left_border = -25000,
                   right_border = 25000;
    vector<int> random_numbers = {}; // main array of numbers to sort
    vector<int> random_numbers_heap = {};   // heap sort
    vector<int> random_numbers_quick = {}; // quick sort
    vector<int> random_numbers_simple = {}; // simple sort
    vector<int> random_numbers_bubble = {}; // bubble sort
    vector<int> random_numbers_comb = {}; // comb sort

    map<string, Decision> decisions = {
            {"QUICK_SORT",  Decision::QUICK_SORT},
            {"BUBBLE_SORT", Decision::BUBBLE_SORT},
            {"HEAP_SORT",   Decision::HEAP_SORT},
            {"COMB_SORT",   Decision::COMB_SORT},
            {"SIMPLE_SORT", Decision::SIMPLE_SORT},
    };

    void ReadFile() {
        ifstream read_file_stream(name_file_input);
        for (int i = 0; i < N; ++i) {
            string temp;
            read_file_stream >> temp;
            random_numbers.push_back(stoi(temp));
        }
        random_numbers_heap = random_numbers;
        random_numbers_quick = random_numbers;
        random_numbers_simple = random_numbers;
        random_numbers_bubble = random_numbers;
        random_numbers_comb = random_numbers;
        random_numbers.clear();
    }

    void writeTimes(long double &search_time, unsigned long long int iterations_count, string &name_sort) {
        ofstream file_stream(name_file_times, ios::app);

        file_stream << name_sort << " Затраченное время: " << search_time << " Количество итераций: "s
                    << iterations_count << endl;
        file_stream.close();
    }

    static void writeElems(const string &name_sort, vector<int> &arr) {
        cout << "Sorted array by: " << name_sort << ":" << endl;
        for (auto i: arr) {
            cout << i << " ";
        }
        cout << endl;
        arr.clear();
    }
};

int main() {
    srand(time(nullptr));
    int N;
    cout << "Enter number of elements: ";
    cin >> N;
    cout << "Processing..." << endl;
    Solution solution(N);
    solution.Generation();
    solution.simpleSortMethod();
    solution.bubbleSortMethod();
    solution.combSortMethod();
    solution.quickSortMethod();
    solution.heapSortMethod();
    while (true) {
        solution.Commander();
    }
}
