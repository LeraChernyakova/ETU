#include <iostream>
#include <list>
#include "cycle.hpp"
#include "KMP.hpp"
#include <fstream>

int main(){
    string pattern;
    string text;
    list<size_t> res = {};
    int consoleOrFile;
    cout << "1 -- Console" << endl << "2 -- File" << endl;
    cin >> consoleOrFile;
    if (consoleOrFile == 1){
        cout << "Input pattern : ";
        cin >> pattern;
        cout << "Input text : ";
        cin >> text;
        int choose = 0;
        cout << "1 -- index\n2 -- cycle\n";
        cin >> choose;
        if (choose == 1) {
            KMP(pattern, text, res);
            if (res.empty()) {cout << "-1"<<endl; return 0;}
            for(auto iter = res.begin(); iter != res.end(); iter++){
                if(iter != res.begin()) cout <<",";
                cout<<*iter;
            }
            cout << endl;
        }else if (choose == 2){
            cout << kmp_cycle(pattern, text) << '\n';
        }
    }else if (consoleOrFile == 2){
        string file;
        cout << "Input filename(.txt): ";
        cin >> file;
        ifstream fin(file + ".txt");
        if(!fin) {cout << "Can't open this file!";return 0;}
        getline(fin, pattern);
        getline(fin, text);
        int choose = 0;
        cout << "1 -- index\n2 -- cycle\n";
        cin >> choose;
        if (choose == 1) {
            KMP(pattern, text, res);
            if (res.empty()) {cout << "-1"<<endl; return 0;}
            for(auto iter = res.begin(); iter != res.end(); iter++){
                if(iter != res.begin()) cout <<",";
                cout<<*iter;
            }
            cout << endl;
        }else if (choose == 2){
            cout << kmp_cycle(pattern, text) << '\n';
        }
    }
}