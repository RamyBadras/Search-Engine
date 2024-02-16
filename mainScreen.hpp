//
//  mainScreen.hpp
//  Semester Project
//
//  Created by Ramy Gad on 27/04/2022.
//

#ifndef mainScreen_hpp
#define mainScreen_hpp

#include <stdio.h>
#include "mainScreen.hpp"
#include "search.hpp"

void startMain();
void startSearch();
void visitPage(vector<website>& found, website* websites);
void displayResults(vector<website> found, website* websites);

#endif /* mainScreen_hpp */
