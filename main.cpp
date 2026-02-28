#include <iostream>
#include <vector>
#include <random>
#include <chrono>
#include <iomanip>
#include <algorithm>
#include <fstream>

using namespace std;
using namespace std::chrono;

// ==================== ALGORITMI DE SORTARE ====================

// ----------------- 1. Mergesort -----------------
long long merge(vector<int>& arr, int left, int mid, int right) {
    long long counter = 0;
    vector<int> leftArr(arr.begin() + left, arr.begin() + mid + 1);
    vector<int> rightArr(arr.begin() + mid + 1, arr.begin() + right + 1);

    int i = 0, j = 0, k = left;

    while (i < leftArr.size() && j < rightArr.size()) {
        counter++; // comparație
        if (leftArr[i] <= rightArr[j]) {
            arr[k++] = leftArr[i++];
        } else {
            arr[k++] = rightArr[j++];
        }
        counter++; // operație de copiere
    }

    while (i < leftArr.size()) {
        counter++;
        arr[k++] = leftArr[i++];
    }

    while (j < rightArr.size()) {
        counter++;
        arr[k++] = rightArr[j++];
    }

    return counter;
}

long long mergesort(vector<int>& arr, int left, int right) {
    long long counter = 0;

    if (left >= right) {
        counter++; // caz de bază
        return counter;
    }

    counter++; // descompunere
    int mid = left + (right - left) / 2;

    counter += mergesort(arr, left, mid);
    counter += mergesort(arr, mid + 1, right);
    counter += merge(arr, left, mid, right);

    return counter;
}

// ----------------- 2. Quicksort -----------------
long long quicksort(vector<int>& arr, int left, int right) {
    long long counter = 0;

    if (left >= right) {
        counter++; // caz de bază
        return counter;
    }

    // Alegere pivot
    int pivot = arr[left + (right - left) / 2];
    vector<int> leftArr, rightArr, middle;

    // Partiționare
    for (int i = left; i <= right; i++) {
        counter++; // comparație
        if (arr[i] < pivot) {
            leftArr.push_back(arr[i]);
        } else if (arr[i] > pivot) {
            rightArr.push_back(arr[i]);
        } else {
            middle.push_back(arr[i]);
        }
        counter++; // operație de partiționare
    }

    // Reconstruire
    int idx = left;
    for (int val : leftArr) arr[idx++] = val;
    for (int val : middle) arr[idx++] = val;
    for (int val : rightArr) arr[idx++] = val;

    counter += leftArr.size() + middle.size() + rightArr.size();

    // Rezolvare recursivă
    int leftEnd = left + leftArr.size() - 1;
    int rightStart = left + leftArr.size() + middle.size();

    if (leftArr.size() > 0) {
        counter += quicksort(arr, left, leftEnd);
    }
    if (rightArr.size() > 0) {
        counter += quicksort(arr, rightStart, right);
    }

    return counter;
}

// ----------------- 3. Bubble Sort -----------------
long long bubblesort(vector<int>& arr) {
    long long counter = 0;
    int n = arr.size();

    for (int i = 0; i < n; i++) {
        bool swapped = false;
        counter++; // iterație externă

        for (int j = 0; j < n - i - 1; j++) {
            counter++; // comparație
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                swapped = true;
                counter++; // operație de swap
            }
        }

        if (!swapped) {
            counter++;
            break;
        }
    }

    return counter;
}

// ==================== ANALIZĂ EMPIRICĂ ====================

struct AlgorithmResult {
    double time;
    long long operations;
    bool correct;
};

void testAlgorithms() {
    int n;
    cout << "Introduceți dimensiunea vectorului pentru test: ";
    cin >> n;

    // Generare vector de test
    vector<int> testVector(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(1, 1000);

    for (int i = 0; i < n; i++) {
        testVector[i] = dis(gen);
    }

    cout << "\nVector de test (primele 10 elemente): ";
    for (int i = 0; i < min(10, n); i++) {
        cout << testVector[i] << " ";
    }
    cout << endl;

    // Vector de referință sortat
    vector<int> sortedReference = testVector;
    sort(sortedReference.begin(), sortedReference.end());

    // 1. Mergesort
    vector<int> mergeVec = testVector;
    auto start = high_resolution_clock::now();
    long long mergeOps = mergesort(mergeVec, 0, n - 1);
    auto end = high_resolution_clock::now();
    double mergeTime = duration<double>(end - start).count();
    bool mergeCorrect = (mergeVec == sortedReference);

    // 2. Quicksort
    vector<int> quickVec = testVector;
    start = high_resolution_clock::now();
    long long quickOps = quicksort(quickVec, 0, n - 1);
    end = high_resolution_clock::now();
    double quickTime = duration<double>(end - start).count();
    bool quickCorrect = (quickVec == sortedReference);

    // 3. Bubble Sort
    vector<int> bubbleVec = testVector;
    start = high_resolution_clock::now();
    long long bubbleOps = bubblesort(bubbleVec);
    end = high_resolution_clock::now();
    double bubbleTime = duration<double>(end - start).count();
    bool bubbleCorrect = (bubbleVec == sortedReference);

    // Afișare rezultate
    cout << "\n" << string(60, '=') << endl;
    cout << "REZULTATE PENTRU n = " << n << endl;
    cout << string(60, '=') << endl;
    cout << left << setw(15) << "Algoritm" << setw(15) << "Timp (s)"
         << setw(15) << "Operații" << setw(10) << "Corect" << endl;
    cout << string(60, '-') << endl;
    cout << setw(15) << "Mergesort" << setw(15) << fixed << setprecision(6) << mergeTime
         << setw(15) << mergeOps << setw(10) << (mergeCorrect ? "DA" : "NU") << endl;
    cout << setw(15) << "Quicksort" << setw(15) << quickTime
         << setw(15) << quickOps << setw(10) << (quickCorrect ? "DA" : "NU") << endl;
    cout << setw(15) << "Bubble Sort" << setw(15) << bubbleTime
         << setw(15) << bubbleOps << setw(10) << (bubbleCorrect ? "DA" : "NU") << endl;
}

void performanceAnalysis() {
    vector<int> sizes = {10, 50, 100, 500, 1000, 5000};

    vector<double> mergeTime, quickTime, bubbleTime;
    vector<long long> mergeOps, quickOps, bubbleOps;

    cout << "\n" << string(80, '=') << endl;
    cout << "ANALIZĂ DE PERFORMANȚĂ PE MULTIPLE DIMENSIUNI" << endl;
    cout << string(80, '=') << endl;
    cout << "Notă: Bubble Sort este testat până la n=5000 din cauza complexității O(n²)" << endl;

    random_device rd;
    mt19937 gen(rd());

    for (int size : sizes) {
        cout << "\nTestare pentru n = " << size << "..." << endl;

        // Generare vector de test
        vector<int> testVector(size);
        uniform_int_distribution<> dis(1, 10000);
        for (int i = 0; i < size; i++) {
            testVector[i] = dis(gen);
        }

        // Mergesort
        vector<int> vec = testVector;
        auto start = high_resolution_clock::now();
        long long ops = mergesort(vec, 0, size - 1);
        auto end = high_resolution_clock::now();
        mergeTime.push_back(duration<double>(end - start).count());
        mergeOps.push_back(ops);

        // Quicksort
        vec = testVector;
        start = high_resolution_clock::now();
        ops = quicksort(vec, 0, size - 1);
        end = high_resolution_clock::now();
        quickTime.push_back(duration<double>(end - start).count());
        quickOps.push_back(ops);

        // Bubble Sort
        vec = testVector;
        start = high_resolution_clock::now();
        ops = bubblesort(vec);
        end = high_resolution_clock::now();
        bubbleTime.push_back(duration<double>(end - start).count());
        bubbleOps.push_back(ops);
    }

    // Afișare rezultate comparative
    cout << "\n" << string(80, '=') << endl;
    cout << "REZULTATE COMPARATIVE (Timp de execuție)" << endl;
    cout << string(80, '=') << endl;
    cout << left << setw(12) << "Dimensiune" << setw(20) << "Mergesort"
         << setw(20) << "Quicksort" << setw(20) << "Bubble Sort" << endl;
    cout << string(80, '-') << endl;

    for (size_t i = 0; i < sizes.size(); i++) {
        cout << setw(12) << sizes[i]
             << setw(20) << fixed << setprecision(6) << mergeTime[i]
             << setw(20) << quickTime[i]
             << setw(20) << bubbleTime[i] << endl;
    }

    // Salvare date pentru grafice (format CSV pentru gnuplot sau Python)
    ofstream outFile("results.csv");
    outFile << "Size,Mergesort_Time,Quicksort_Time,Bubble_Time,Mergesort_Ops,Quicksort_Ops,Bubble_Ops\n";
    for (size_t i = 0; i < sizes.size(); i++) {
        outFile << sizes[i] << ","
                << mergeTime[i] << "," << quickTime[i] << "," << bubbleTime[i] << ","
                << mergeOps[i] << "," << quickOps[i] << "," << bubbleOps[i] << "\n";
    }
    outFile.close();

    cout << "\nRezultatele au fost salvate în 'results.csv' pentru vizualizare!" << endl;
}

// ==================== MAIN ====================

int main() {
    cout << "ANALIZĂ EMPIRICĂ A ALGORITMILOR DE SORTARE" << endl;
    cout << "Algoritmi implementați:" << endl;
    cout << "1. Mergesort (Divide et Impera) - O(n log n)" << endl;
    cout << "2. Quicksort - O(n log n) în medie" << endl;
    cout << "3. Bubble Sort (Referință) - O(n²)" << endl;

    while (true) {
        cout << "\n" << string(50, '=') << endl;
        cout << "MENIU PRINCIPAL" << endl;
        cout << "1. Testare pe o dimensiune specifică" << endl;
        cout << "2. Analiză de performanță completă" << endl;
        cout << "3. Ieșire" << endl;

        int choice;
        cout << "Alegeți o opțiune (1-3): ";
        cin >> choice;

        switch (choice) {
            case 1:
                testAlgorithms();
                break;
            case 2:
                performanceAnalysis();
                break;
            case 3:
                cout << "La revedere!" << endl;
                return 0;
            default:
                cout << "Opțiune invalidă! Încercați din nou." << endl;
        }
    }

    return 0;
}