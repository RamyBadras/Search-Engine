//
//  mainScreen.cpp
//  Semester Project
//
//  Created by Ramy Gad on 27/04/2022.
//

#include "mainScreen.hpp"

void startMain(){

int answer;

    cout << "Welcome!"<<endl;
    cout << "What would you like to do?"<<endl;
    cout << "1. New Search" <<endl;
    cout << "2. Exit"<<endl;
    cout << "Enter your choice: ";
    cin >> answer;
    
    
    if (answer==1){
            
        startSearch();

    }
    
    else if(answer==2){
        return;
    }
    
    else{
        cout << "Please enter valid answer" <<endl;
    }
    
}


void startSearch(){
    
    
    int answer;
    website* websites = new website;
    websites = initializeWebsites();
    
//    display_stats(websites);
    
    string inputString;
    
    cout << "Enter Keywords for search: ";
    cin.ignore();
    getline(cin, inputString);
    vector <website> found=search(inputString, websites);
    
    if (found.size()==0)
    {
        cout << "No Results Found"<<endl;
        cout << "Would you like to: "<<endl;
        cout << "1. Start New Search. "<<endl;
        cout << "2. Exit."<<endl;
        
        cin >> answer;
        while (answer!=1 && answer!=2) {
            cout << "Please enter valid answer: ";
            cin >>  answer;
        }
        if (answer==1) {
            startSearch();
        }
            
        else if(answer==2){
            return;
            }
    }

    else{
        displayResults(found, websites);
    }
    
}


void visitPage(vector<website>& found, website* websites){
    
    int n = website::counter;
    int answer;
    
    cout << "Enter page index to visit: ";
    cin>>answer;
    while (answer>found.size() || answer <= 0) {
        cout << "please enter valid page index: ";
        cin >>answer;
    }
    cout << "You are now viewing: "<<found[answer-1].URL<<endl;
    websites[found[answer-1].index].clickThroughs+=1;
    
    cout << "What would you like to do: "<<endl;
    cout << "1. Back to Search Results."<<endl;
    cout << "2. New Search." <<endl;
    cout << "3. Exit." << endl;
    cout << "Enter your choice: ";
    cin >>  answer;
    
    
    if (answer==3) {
        return;
    }
    else if(answer==2){
        ofstream outClik;
        outClik.open("clickthroughs.csv");
        
        for (int i=0; i<n; i++) {
            outClik << websites[i].clickThroughs<<'\n';
        }
        
        outClik.close();
        startSearch();
    }
    else if(answer==1){
        
        displayResults(found, websites);
    }
    
}

void displayResults(vector<website> found, website* websites){
    int n = website::counter;
    int answer;
    
    cout << "Search Results: " <<endl;
    for (int i=0; i<found.size(); i++) {
        cout << i+1<<". "<<found[i].URL <<endl;
    }
    cout << endl;
    cout << "Would you like to: "<<endl;
    cout << "1. Choose a webpage to open"<<endl;
    cout << "2. New Search"<<endl;
    cout << "3. Exit"<<endl;
    cout << "Enter your choice: ";
    cin >> answer;
    
    if (answer==3) {
        return;
    }
    else if (answer==1) {
        visitPage(found, websites);
    }
    else if (answer==2){
        ofstream outClik;
        outClik.open("clickthroughs.csv");
        
        for (int i=0; i<n; i++) {
            outClik << websites[i].clickThroughs<<'\n';
        }
        
        outClik.close();
        startSearch();
    }
    
}
