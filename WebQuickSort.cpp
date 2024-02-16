//
//  WebQuickSort.cpp
//  Semester Project
//
//  Created by Ramy Gad on 27/04/2022.
//

#include "WebQuickSort.hpp"


void swap(website* a, website* b)
{
    website t = *a;
    *a = *b;
    *b = t;
}

int partition(vector<website> &arr, int low, int high){
    
    double pivot = arr[high].score;
    int i = low - 1;
    
    for (int j = low; j <= high; j++){
        if (arr[j].score > pivot){
            i++;
            swap(&arr[i], &arr[j]);
        }
    }
    swap(&arr[i + 1], &arr[high]);
    return (i+1);
}

void quickSort(vector<website>& arr, int low, int high){
    
    if (low < high){
        
    
    
    int pi = partition(arr, low, high);
    
    quickSort(arr, low, pi-1);
    quickSort(arr, pi+1, high);
        
    }
}
