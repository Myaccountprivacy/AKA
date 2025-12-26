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
    int right=arr.size() - 1;

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
        int mid = left + (right - left) / 2;
        if (arr[mid]==target) return mid;
        if (arr[mid]>target) return binarySearchRecursive(arr,left,mid-1,target);
        return binarySearchRecursive(arr,mid + 1,right,target);
    }
    return -1;
}

// --- Fungsi Bantu untuk Analisis ---

int main() {
    // Ukuran masukan yang akan diuji sesuai ketentuan (10 s.d 10000+) 
    vector<int> inputSizes = {10, 100, 500, 1000, 5000, 10000, 50000, 100000};
    
    cout<<"=================================================================\n";
    cout<<"   Analisis Efisiensi Waktu: Binary Search (Iteratif vs Rekursif)\n";
    cout<<"=================================================================\n";
    cout<<left<<setw(15)<<"Ukuran Data"<<setw(25)<<"Waktu Iteratif (ns)"<<setw(25)<<"Waktu Rekursif (ns)\n";
    cout<<"-----------------------------------------------------------------\n";

    for (int n : inputSizes) {
        // 1. Generate Data Dummy (Kode Barang terurut)
        vector<long long> data(n);
        for (int i=0;i<n;i++) {
            data[i]=100000+i*2; // Contoh kode barang urut
        }

        // Target yang dicari (ditaruh di akhir agar kasus terburuk/worst case)
        long long target=data[n-1]; 

        // 2. Pengukuran Waktu Iteratif
        auto startIter=high_resolution_clock::now();
        binarySearchIterative(data,target);
        auto stopIter=high_resolution_clock::now();
        auto durationIter = duration_cast<nanoseconds>(stopIter - startIter);

        // 3. Pengukuran Waktu Rekursif
        auto startRec=high_resolution_clock::now();
        binarySearchRecursive(data, 0, n - 1, target);
        auto stopRec=high_resolution_clock::now();
        auto durationRec=duration_cast<nanoseconds>(stopRec-startRec);

        // 4. Output Hasil untuk Tabel Laporan 
        cout<<left<<setw(15)<<n<<setw(25)<<durationIter.count()<<setw(25)<<durationRec.count()<<"\n";
    }

    cout<<"-----------------------------------------------------------------\n";
    cout<<"Catatan: Waktu dalam nanoseconds (ns).\n";

    return 0;
}