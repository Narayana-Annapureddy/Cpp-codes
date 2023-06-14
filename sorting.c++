#include<bits/stdc++.h>  // c++ uses introSort  (combination of Insertion sort, Quick sort and heap sort)
using namespace std;

// stable sort means order preserve for ex: if 2 5 2 then after sorting 2 2 5  (2's order must not change)
// Merge, insertion, selection and counting sort are stable sort algorithms

// Best sorting algorithm based on scenarios  .First check if the data can be fit into RAM  
//   i) NO ->  Merge sort is best bcz it will split the data into half so fit in RAM
//  ii) Yes means check if swaps are expensive 

// Swap expensive means selection sort is best bcz it is O(n) swaps

// If swap is not much expensive then check if data is mostly sorted or not

//  If mostly sorted then insertion sort is best

// If not mostly sorted then check if we can use extra space then yes means use Quick sort (no extra space needed)

// If extra space can be used and stable sorting algo needed then go with Merge otherwise Quick sort


void selectionSort() {

    // Not stable sorting algorithm  ex:  4a, 2, 3, 4b, 1  (after 1st iteration:  1, 2, 3, 4b, 4a) (4 occured 2 times )

    // keep min element in it's position for every iteration
    // for ex in iteration 1 keep first min element in index 0, ... iteration n-1 second max element in n-2 index..
    vector<int> v = {3, 30, 2, 9, 5, 19};

    for (int i=0; i<v.size(); i++) {
        int min = i;
        for (int j=i+1; j<v.size(); j++) {
            if (v[min] > v[j])
                min = j;
        }
        swap(v[min], v[i]);
    }
    
}


void bubbleSort() {
    
    // bubble sort is stable sorting algorithm

    // keep max element in it's correct pos for every iteration
    vector<int> v = {3, 30, 22, 9, 5, 19};

    for (int i=0; i<v.size(); i++) {
        bool isSorted = true;
        for (int j=0; j<v.size()-i-1; j++) {
            if (v[j] > v[j+1]) {
                swap(v[j], v[j+1]);
                isSorted = false;
            }
        }
        if (isSorted)  // modified bubble sort
            break;
    }
}

void insertionSort() {

    // insertion sort is stable it maintains relative order of elements

    // Inserting element into sorted array every time
    vector<int> v = {3, 30, 22, 9, 5, 19};

    for (int i=1; i<v.size(); i++) {
        int key = v[i], j;
        for (j=i-1;  j>=0;  j--) {
            if (v[j] > key)
                v[j+1] = v[j];
            else
                break;
        }
        v[j+1] = key;
    }
}

// Quick sort is  inplace algorithm but not stable 
int Partition(vector<int> &v, int low, int high) {

    // Start from  (i = low)  every time check the example [-5, 19]
    // if u start from i=low+1 then i, j point at 19 and i < j is false so swap v[low], v[j] i.e 19 and -5 swapped

    int piv = low,  i = low,  j = high;
    while (i < j) {

        while (i < high && v[i] <= v[piv])
            i++;

        while (j > low && v[j] > v[piv])
            j--;

        if (i < j)
            swap(v[i], v[j]);
    }

    swap(v[low], v[j]);
    return j;
}


void quickSort(vector<int> &v, int low, int high) {

    if (low < high) {
        int piv = Partition(v, low, high);
        quickSort(v, low, piv-1);
        quickSort(v, piv+1, high);
    }
}

int main() {
    bubbleSort();
}
