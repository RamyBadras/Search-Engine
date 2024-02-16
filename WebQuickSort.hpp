//
//  WebQuickSort.hpp
//  Semester Project
//
//  Created by Ramy Gad on 27/04/2022.
//

#ifndef WebQuickSort_hpp
#define WebQuickSort_hpp

#include <stdio.h>
#include "website.hpp"

void swap(website* a, website* b);
void quickSort(vector<website>& arr, int low, int high);
int partition(vector<website> &arr, int low, int high);

#endif /* WebQuickSort_hpp */
