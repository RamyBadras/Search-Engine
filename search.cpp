//
//  search.cpp
//  Semester Project
//
//  Created by Ramy Gad on 24/04/2022.
//

#include "WebQuickSort.hpp"
#include "search.hpp"


    vector<website> search(string search, website* websites){
    vector <website> found;

    if (search.length()==0){
        cout << "Please Enter Valid keyword(s)."<<endl;
        return found;
    }
    
    int n = website::counter;
    int wordCount = count(search);
    string* wordList = list(search, wordCount);
    
    for (int i=0; i<n; i++) {
        websites[i].inSearch=false;
    }
    
    if (wordCount==1) {
        for (int i=0; i<n; i++) {
            for (int j=0; j<websites[i].keyWords.size(); j++) {
                if (websites[i].keyWords[j]==wordList[0]) {
                    found.push_back(websites[i]);
                }
            }
        }
    }
    
    else{
        
        for (int i=0; i<wordCount; i++) {
            
            if (wordList[i]=="AND") {
                bool safe=false;
                i++;
                for (int j=found.size()-1; j>=0; j--) {
                    for (int k=0; k<found[j].keyWords.size(); k++) {
                        if(found[j].keyWords[k]==wordList[i]){
                            safe = true;
                        }
                    }
                    
                    if (!safe) {
                        found[j].inSearch=false;
                        found.erase(found.begin()+j);
                    }
                    safe = false;
                }
                
            }
            
            if (i==0 || wordList[i-1]!="AND") {
                for (int k=0; k<n; k++) {
                    for (int j=0; j<websites[k].keyWords.size(); j++) {
                        if (websites[k].keyWords[j]==wordList[i]) {
                            if (websites[k].inSearch==false) {
                                websites[k].inSearch=true;
                                found.push_back(websites[k]);
                            }
                        }
                    }
                }
            }
            
        }

        }
        
    quickSort(found, 0, found.size()-1);
    
    ofstream outImp;
    outImp.open("impressions.csv");
    
    for (int i=0; i<found.size(); i++) {
        websites[found[i].index].impressions+=1;
    }
    
    for (int i=0; i<n; i++) {
        outImp << websites[i].URL<<","<<websites[i].impressions;
        if (i<n-1) {
            outImp << '\n';
        }
    }
    
    
    outImp.close();
    return found;
    
}


string *list(string main, int n){
    int wordCount=n;
    string * arr = new string [wordCount];

    int j=0;
    
    for(int i=0;i<main.length();i++){
        
        if (main[i]=='"'){
            i++;
            while (main[i]!='"') {
                arr[j]+=main[i++];
            }
            
            arr[j]+=main[++i];
        }
        
        if(main[i]!=' '){
            arr[j]+=main[i];
        }
        
        else{
            j++;
        }
    }
    
    return arr;
}
    
int count(string x){
        int counter=1;
        for (int i = 0; i < x.length(); i++){
            if (x[i]==' '){
                counter++;
            }
        }
        return counter;
    }
