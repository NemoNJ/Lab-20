#include<iostream>
#include<fstream>
#include<vector>
#include<string>
#include<cstdlib>

using namespace std;

char score2grade(int score){
    if(score >= 80) return 'A';
    if(score >= 70) return 'B';
    if(score >= 60) return 'C';
    if(score >= 50) return 'D';
    else return 'F';
}

string toUpperStr(string x){
    string y = x;
    for(unsigned i = 0; i < x.size();i++) y[i] = toupper(x[i]);
    return y;
}

void importDataFromFile(string filename,vector<string> &names,vector<int> &scores,vector<char> &grades){
     string textline;
     ifstream source(filename);
     while(getline(source,textline)){
        char name[99];
        int score1,score2,score3;
        char format[] = "%[^:]: %d %d %d";
        sscanf(textline.c_str(),format,name,&score1,&score2,&score3);
        int scoreSum = score1+score2+score3;
        grades.push_back(score2grade(scoreSum));
        scores.push_back(scoreSum) ;
        names.push_back(name); 
     }
}

void getCommand(string &command, string &key){
        cout << "Please input your command: ";
        cin >> command;
        string commandUp = toUpperStr(command);
        if(commandUp == "EXIT" || commandUp =="GRADE" || commandUp == "NAME"){
            cin.ignore();
            getline(cin, key);
        }
}

void searchName(vector<string> names,vector<int> scores,vector<char> grades,string key){
       bool checkfound;
       cout << "---------------------------------\n";
       for(unsigned int i = 0;i < names.size();i++){
          string nameupper = toUpperStr(names[i]);
          if(key == nameupper){
               cout << names[i]<<"'s score = "<<scores[i]<<endl;
               cout << names[i]<<"'s grade = "<<grades[i]<<endl;
               checkfound = true; 
          }
       }
       
       if(checkfound == 0) cout << "Cannot found."<<endl;
       cout << "---------------------------------\n";
}

void searchGrade(vector<string> &names, vector<int> &scores, vector<char> &grades, string key){
       bool checkfound;
       vector<string> namehavegrade;
       vector<int> havegrade;
       cout << "---------------------------------\n";
       for(unsigned int i = 0;i < names.size();i++){
       
          if(key.c_str()[0] == grades[i]){
                namehavegrade.push_back(names[i]);
                havegrade.push_back(scores[i]);
                checkfound = true;
          }
       }
       for(unsigned int i = 0;i < namehavegrade.size();i++){
       cout << namehavegrade[i] <<" ("<< havegrade[i] <<")"<<endl;
       }
       
       if(checkfound == 0) cout << "Cannot found."<<endl;
       cout << "---------------------------------\n";
}




int main(){
    string filename = "name_score.txt";
    vector<string> names;
    vector<int> scores;
    vector<char> grades; 
    importDataFromFile(filename, names, scores, grades);
    
    do{
        string command, key;
        getCommand(command,key);
        command = toUpperStr(command);
        key = toUpperStr(key);
        if(command == "EXIT") break;
        else if(command == "GRADE") searchGrade(names, scores, grades, key);
        else if(command == "NAME") searchName(names, scores, grades, key);
        else{
            cout << "---------------------------------\n";
            cout << "Invalid command.\n";
            cout << "---------------------------------\n";
        }
    }while(true);
    
    return 0;
}