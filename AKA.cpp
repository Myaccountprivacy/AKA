#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>

using namespace std;
using namespace std::chrono;

// Iteratif
int binarySearchIterative(const vector<long long>& arr,long long target) {
    int left=0;
    int right=arr.size()-1;
    while (left<=right) {
        int mid=left+(right-left)/2;
        if (arr[mid]==target) return mid;
        if (arr[mid]<target) left=mid+1;
        else right=mid-1;
    }
    return -1;
}

// Rekursif
int binarySearchRecursive(const vector<long long>& arr,int left,int right,long long target) {
    if (right>=left) {
        int mid=left+(right-left)/2;
        if (arr[mid]==target) return mid;
        if (arr[mid] > target) return binarySearchRecursive(arr,left,mid-1,target);
        return binarySearchRecursive(arr,mid+1,right,target);
    }
    return -1;
}

int main() {
    // Ukuran masukan yang diuji
    vector<int> inputSizes = {10, 100, 500, 1000, 5000, 10000, 50000, 100000};
    
    cout<<"==========================================================================================\n";
    cout<<"               Analisis Efisiensi: Best Case vs Worst Case (Binary Search)\n";
    cout<<"==========================================================================================\n";
    cout<<left<<setw(12)<<"Ukuran"<<setw(22)<<"Iteratif BEST (ns)"<<setw(22)<<"Iteratif WORST (ns)"<<setw(22)<<"Rekursif BEST (ns)"<<setw(22)<<"Rekursif WORST (ns)\n";
    cout<<"------------------------------------------------------------------------------------------\n";

    for (int n : inputSizes) {
        // Generate Data (Kode Barang Terurut)
        vector<long long> data(n);
        for (int i = 0; i < n; i++) {
            data[i] = 100000 + i * 2; 
        }

        // --- DEFINISI KASUS ---
        // Best Case: Target ada tepat di tengah (Langsung ketemu)
        long long targetBest = data[(n - 1) / 2];
        
        // Worst Case: Target ada di ujung paling kanan (Harus membelah sampai habis)
        long long targetWorst = data[n - 1]; 

        // --- PENGUKURAN WAKTU ---

        // 1. Iteratif BEST
        auto startIB = high_resolution_clock::now();
        binarySearchIterative(data, targetBest);
        auto stopIB = high_resolution_clock::now();
        auto timeIB = duration_cast<nanoseconds>(stopIB - startIB);

        // 2. Iteratif WORST
        auto startIW = high_resolution_clock::now();
        binarySearchIterative(data, targetWorst);
        auto stopIW = high_resolution_clock::now();
        auto timeIW = duration_cast<nanoseconds>(stopIW - startIW);

        // 3. Rekursif BEST
        auto startRB = high_resolution_clock::now();
        binarySearchRecursive(data, 0, n - 1, targetBest);
        auto stopRB = high_resolution_clock::now();
        auto timeRB = duration_cast<nanoseconds>(stopRB - startRB);

        // 4. Rekursif WORST
        auto startRW = high_resolution_clock::now();
        binarySearchRecursive(data, 0, n - 1, targetWorst);
        auto stopRW = high_resolution_clock::now();
        auto timeRW = duration_cast<nanoseconds>(stopRW - startRW);

        // --- OUTPUT HASIL ---
        cout<<left<<setw(12)<<n<<setw(22)<<timeIB.count()<<setw(22)<<timeIW.count()<<setw(22)<<timeRB.count()<<setw(22)<<timeRW.count()<<"\n";
    }
    cout<<"------------------------------------------------------------------------------------------\n";
    cout<<"Keterangan:\n";
    cout<<"Best Case  : Target berada tepat di tengah array (O(1)).\n";
    cout<<"Worst Case : Target berada di ujung array, butuh pembagian maksimal (O(log n)).\n";
    return 0;
}