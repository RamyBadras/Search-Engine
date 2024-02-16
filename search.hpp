//
//  search.hpp
//  Semester Project
//
//  Created by Ramy Gad on 24/04/2022.
//

#ifndef search_hpp
#define search_hpp

#include <stdio.h>
#include "website.hpp"
#include "string.h"



vector<website> search(string search, website* websites);
string *list(string main, int n);
int count(string x);

int partition(vector<website>&arr, int low, int high);
void swap(vector<website>& a, vector<website>& b);
void quickSort(vector<website>&, int low, int high);

#endif /* search_hpp */
