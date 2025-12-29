#include <iostream>
#include <vector>
#include <algorithm>
#include <chrono>
#include <iomanip>
#include <cstdlib> // Untuk rand()
#include <ctime>   // Untuk time()

using namespace std;
using namespace std::chrono;

// Binary Search Iteratif
int binarySearchIterative(const vector<long long>& arr,long long target) {
    int left=0;
    int right=arr.size()-1;
    while (left<=right) {
        int mid=left+(right-left)/2;
        if (arr[mid]==target) return mid;
        if (arr[mid]<target) left=mid +1;
        else right=mid-1;
    }
    return -1;
}

// Binary Search Rekursif
int binarySearchRecursive(const vector<long long>& arr,int left,int right,long long target) {
    if (right>=left) {
        int mid=left+(right-left)/2;
        if (arr[mid]==target) return mid;
        if (arr[mid]>target) return binarySearchRecursive(arr,left,mid-1,target);
        return binarySearchRecursive(arr,mid+1,right,target);
    }
    return -1;
}

int main() {
    // Inisialisasi random seed
    srand(time(0));

    vector<int> inputSizes={10,100,500,1000,5000,10000,50000,100000};
    
    cout<<"=======================================================================================================\n";
    cout<<"                            Best, Average, & Worst Case (Binary Search)\n";
    cout<<"=======================================================================================================\n";
    cout<<left<<setw(10)<<"Ukuran"<<setw(18)<<"Iter BEST"<<setw(18)<<"Iter AVG"<<setw(18)<<"Iter WORST"<<setw(18)<<"Rec BEST"<<setw(18)<<"Rec AVG"<<setw(18)<<"Rec WORST\n";
    cout<<"-------------------------------------------------------------------------------------------------------\n";

    for (int n : inputSizes) {
        vector<long long> data(n);
        for (int i=0;i<n;i++) {
            data[i]=100000+i*2; 
        }
        
        // Best Case: Target di tengah (1x cek)
        long long targetBest=data[(n-1) / 2];
        // Average Case: Target diambil secara acak dari data yang ada
        long long targetAvg=data[rand()%n];
        // Worst Case: Target di ujung akhir atau tidak ada (cek s/d habis)
        long long targetWorst=data[n-1]; 

        // ITERATIF
        // Best Case
        auto startIB=high_resolution_clock::now();
        binarySearchIterative(data,targetBest);
        auto stopIB=high_resolution_clock::now();
        // Average Case
        auto startIA=high_resolution_clock::now();
        binarySearchIterative(data,targetAvg);
        auto stopIA=high_resolution_clock::now();
        // Worst Case
        auto startIW=high_resolution_clock::now();
        binarySearchIterative(data,targetWorst);
        auto stopIW=high_resolution_clock::now();

        // REKURSIF
        // Best Case
        auto startRB=high_resolution_clock::now();
        binarySearchRecursive(data,0,n-1,targetBest);
        auto stopRB=high_resolution_clock::now();
        // Average Case
        auto startRA=high_resolution_clock::now();
        binarySearchRecursive(data,0,n-1,targetAvg);
        auto stopRA=high_resolution_clock::now();
        // Worst Case
        auto startRW=high_resolution_clock::now();
        binarySearchRecursive(data,0,n-1,targetWorst);
        auto stopRW=high_resolution_clock::now();

        // Konversi ke nanoseconds
        // Iteratif
        auto tIB=duration_cast<nanoseconds>(stopIB-startIB).count();
        auto tIA=duration_cast<nanoseconds>(stopIA-startIA).count();
        auto tIW=duration_cast<nanoseconds>(stopIW-startIW).count();
        // Rekursif
        auto tRB=duration_cast<nanoseconds>(stopRB-startRB).count();
        auto tRA=duration_cast<nanoseconds>(stopRA-startRA).count();
        auto tRW=duration_cast<nanoseconds>(stopRW-startRW).count();

        // Output
        cout<<left<<setw(10)<<n<<setw(18)<<tIB<<setw(18)<<tIA<<setw(18)<<tIW<<setw(18)<<tRB<<setw(18)<<tRA<<setw(18)<<tRW<<"\n";
    }

    cout<<"-------------------------------------------------------------------------------------------------------\n";
    cout<<"Satuan: Nanoseconds (ns)\n";
    cout<<"Keterangan:\n";
    cout<<"- Best Case : Target indeks tengah.\n";
    cout<<"- Avg Case  : Target acak (Random Index).\n";
    cout<<"- Worst Case: Target indeks terakhir.\n";
    return 0;
}