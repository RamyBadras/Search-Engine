//
//  website.cpp
//  Semester Project
//
//  Created by Ramy Gad on 21/04/2022.
//

#include "website.hpp"



website* initializeWebsites(){
    
    // Reading the CSV file that contains the initial number of impressions.
    // Setting the websites' URL.
    
    ifstream impressionFile("impressions.csv");
    vector <website> websitesVec;
    
    while(impressionFile.good()){
        string empty;
        website* temp = new website;
        getline(impressionFile, temp->URL, ',');
        impressionFile >> temp->impressions;
        getline(impressionFile, empty, '\n');
        websitesVec.push_back(*temp);
    }
    
    int websiteNum = websitesVec.size();
    website::counter=websiteNum;
    website* arr = new website[websiteNum];
    
    // Setting the websites' keywords, and clickthroughs then calculating CTR, instead of creating a separate loop.
    
    ifstream keyFile("keyWords.csv");
    ifstream clickFile("clickthroughs.csv");
    
    for (int i=0; i < websiteNum; i++) {
        
        arr[i] = websitesVec[i];
        arr[i].index=i;
        clickFile >> arr[i].clickThroughs;
        arr[i].CTR = arr[i].clickThroughs/arr[i].impressions;
        arr[i].inSearch=false;
        
        string line;
        string currentKW="";
        getline(keyFile, line, ',');
        getline(keyFile, line, '\n');

        int j=0;
        while (true) {
            currentKW+=line[j];
            j++;
            if (line[j]==',') {
                arr[i].keyWords.push_back(currentKW);
                currentKW="";
                j++;
            }
            if (line[j]=='\0') {
                arr[i].keyWords.push_back(currentKW);
                break;
            }
        }
        
    }
    
    // Setting links.
    
    ifstream hyperlinks("hyperlinks.csv");
    
    vector<string> linkFrom;
    vector<string> linkTo;
    
    while (!hyperlinks.eof()) {
        string temp;
        getline(hyperlinks, temp, ',');
        linkFrom.push_back(temp);
        getline(hyperlinks, temp, '\n');
        linkTo.push_back(temp);
    }
    
    string sourceURL;
    
    for (int i=0; i<websiteNum; i++) {
        for (int j=0; j<linkFrom.size(); j++) {
            
            if (arr[i].URL==linkTo[j]) {
                sourceURL=linkFrom[j];
                
                for (int k=0; k<websiteNum; k++) {
                    if (sourceURL==arr[k].URL) {
                        website* temp = new website;
                        temp = &arr[k];
                        arr[i].linkedFrom.push_back(temp);
                    }
                }
                
            }
            
            if (arr[i].URL==linkFrom[j]) {
                arr[i].outGoingLinks++;
            }
            
        }
    }
    
    hyperlinks.close();
    keyFile.close();
    
    calculateScore(arr);
    
    return arr;
}

void calculateScore(website* websites){
    
    int n = website::counter;
    
    // calculating page rank for each website.
    
    calc_pageRank(websites);
    
    double pr;
    double imp;
    
    
    for (int i=0; i<n; i++) {
        
        pr = websites[i].pageRank;
        imp = websites[i].impressions;
        
        // Formula for calculating final score for each website.
        
        websites[i].score = 0.4*pr + ((1-(0.1*imp)/(1+0.1*imp))*pr + (0.1*imp)/(1+0.1*imp)*websites[i].CTR);
        
    }
    
    
}

void calc_pageRank(website* websites){
    
    double n = website::counter;
    int num = website::counter;
    
    int iterations = 5;
    double pageRanks[iterations+1][num];
    
    // set initial page rank.
    
    for (int i=0; i<n; i++) {
        websites[i].pageRank=1/n;
        pageRanks[0][i]=websites[i].pageRank;
    }
    
    // Calculating page ranks through a specific amount of iterations.
    
    for (int k=0; k<iterations; k++) {
        
        for (int i=0; i<num; i++) {
            
            if (websites[i].linkedFrom.size()==0) {
                websites[i].pageRank = pageRanks[k][i]/websites[i].outGoingLinks;
                pageRanks[k+1][i] = websites[i].pageRank;
            }
            
            else{
                
                double newVal=0;
                for (int j=0; j<websites[i].linkedFrom.size(); j++) {
                     newVal+=(pageRanks[k][websites[i].linkedFrom[j]->index])/websites[i].linkedFrom[j]->outGoingLinks;

                }
                   
                websites[i].pageRank=newVal;
                pageRanks[k+1][i]=newVal;
            }
            
        }
    }   
    
 
}

// Function to display stats of each website, only used it to make sure everything is good.

void display_stats(website* websites){
    
    int n = website::counter;
    
    
    cout << left << setw(20) <<" "<< setw(20) << "Page Rank" << setw(20)<< "Impressions" << setw(20)<< "Clickthroughs" << setw(20) << "CTR" << setw(20)<< "Final Score"<<endl;
    
    
    for (int i=0; i<n; i++) {
        cout << left << setw(20) <<websites[i].URL<<setw(20)<< websites[i].pageRank << setw(20)<< websites[i].impressions << setw(20)<< websites[i].clickThroughs << setw(20) << websites[i].CTR << setw(20)<< websites[i].score<<endl;
    }
    
}

