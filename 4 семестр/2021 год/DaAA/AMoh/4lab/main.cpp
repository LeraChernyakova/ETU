#include <list>
#include <iostream>
#include "kmp.hpp"
#include "cycleShift.hpp"

using namespace std;

int main(){
    string pattern;
    string text;
    list<unsigned > res = {};
    int sel = 0;
    cout << "Select:\n1 -- kmp indexes\n2 -- cycle shift\n";
    cin >> sel;
    cout << "Input pattern and text:\n";
    cin >> pattern >> text;
    if (sel == 1) {
        KMP(pattern, text, res);
        if (res.empty()) {
            cout << "-1" << endl;
            return 0;
        }
        for (auto iter = res.begin(); iter != res.end(); iter++) {
            if (iter != res.begin()) cout << ",";
            cout << *iter;
        }
        cout << endl;
    }else if(sel == 2){
        cout << kmp_cycle(pattern, text) << endl;
    }
    return 0;
}
