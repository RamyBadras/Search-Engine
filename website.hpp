//
//  website.hpp
//  Semester Project
//
//  Created by Ramy Gad on 21/04/2022.
//

#ifndef website_hpp
#define website_hpp

#include <stdio.h>
#include <vector>
#include <string>
#include <fstream>
#include <iostream>

using namespace std;


class website{
    
    
public:
    
    static int counter;
    bool inSearch;
    int index;
    string URL;
    vector <string> keyWords;
    vector <website*> linkedFrom;
    double score, CTR, pageRank, outGoingLinks=0, clickThroughs, impressions;
};

inline int website::counter=0;

website* initializeWebsites();
void calculateScore(website* websites);
void calc_pageRank(website* websites);
void display_stats(website* websites);

#endif /* website_hpp */
