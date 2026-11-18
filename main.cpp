
#include <algorithm>
#include <chrono>
#include <fstream>
#include <iostream>
#include <random>
#include <vector>
using namespace std;

void insertion_sort(vector<int>& v) {
    for (int i = 0; i < v.size(); i++) {
        int j = i - 1;
        while (j >= 0 && v[j] > v[j + 1]) {
            int temp = v[j];
            v[j] = v[j + 1];
            v[j + 1] = temp;
            j--;
        }
    }
}

void shell_sort(vector<int>& v) {
    int h = v.size() / 2;
    while (h > 0) {
        for (int i = h; i < v.size(); i++) {
            int j = i - h;
            while (j >= 0 && v[j] > v[j + h]) {
                int temp = v[j];
                v[j] = v[j + h];
                v[j + h] = temp;
                j -= h;
            }
        }
        h /= 2;
    }
}

void generate_random_data(vector<int>& arr) {
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<int> distrib(1, 1000000);
    for (int i = 0; i < arr.size(); i++) {
        arr[i] = distrib(gen);
    }
}

void copy_vec(vector<int>& arr1, vector<int>& arr2) {
    for (int i = 0; i < arr1.size(); i++) {
        arr1[i] = arr2[i];
    }
}

void is_sorted(vector<int>& arr) {
    for (int i = 0; i < arr.size() - 1; i++) {
        if (arr[i] > arr[i + 1]) throw runtime_error("Array is not sorted!");
    }
}

void add_to_file(const vector<double>& res, int n, ofstream& file) {
    file << n << ";";
    for (size_t k = 0; k < res.size(); k++) file << int(res[k]) << ";";  
    file << "\n";
}

int main() {
    const int TEST_RUNS = 100;
    ofstream file("results_curs.csv");
    file << "size;insertion_sort;shell_sort;sort\n";
    int arr[] = {50, 100, 200, 500, 1000, 2000, 5000, 10000, 15000, 20000};
    for (int i = 0; i < 10; i++) {
        vector<int> arr1(arr[i]), arr2(arr[i]), arr3(arr[i]);

        double sum[3] = {0};
        for (int j = 0; j < TEST_RUNS; j++) {
            generate_random_data(arr1);
            copy_vec(arr2, arr1);
            copy_vec(arr3, arr1);

            auto start_insert = chrono::high_resolution_clock::now();
            insertion_sort(arr1);
            auto end_insert = chrono::high_resolution_clock::now();
            double time_insert =
                chrono::duration_cast<chrono::microseconds>(end_insert - start_insert).count();
            is_sorted(arr1);

            auto start_shell = chrono::high_resolution_clock::now();
            shell_sort(arr2);
            auto end_shell = chrono::high_resolution_clock::now();
            double time_shell = chrono::duration_cast<chrono::microseconds>(end_shell - start_shell).count();
            is_sorted(arr2);

            auto start_sort = chrono::high_resolution_clock::now();
            sort(arr3.begin(), arr3.end());
            auto end_sort = chrono::high_resolution_clock::now();
            double time_sort = chrono::duration_cast<chrono::microseconds>(end_sort - start_sort).count();
            is_sorted(arr3);

            sum[0] += time_insert;
            sum[1] += time_shell;
            sum[2] += time_sort;
        }
        add_to_file({sum[0] / TEST_RUNS, sum[1] / TEST_RUNS, sum[2] / TEST_RUNS}, arr[i], file);
    }
    return 0;
}
