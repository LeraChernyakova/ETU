#include <iostream>
#include <vector>
#include <list>
using namespace std;
void lps_func(string txt, vector<int>&Lps){
    Lps[0] = 0;
    int len = 0;
    int i=1;
    while (i<txt.length()){
        if(txt[i]==txt[len]){
            len++;
            Lps[i] = len;
            i++;
            continue;
        }
        else{
            if(len==0){
                Lps[i] = 0;
                i++;
                continue;
            }
            else{
                len = Lps[len-1];
                continue;
            }
        }
    }
}

void KMP(string pattern,string text, list<size_t>&result){
    size_t n = text.length();
    size_t m = pattern.length();
    vector<int>Lps(m);

    lps_func(pattern,Lps);

    int i=0,j=0;
    while(i<n){
        if(pattern[j]==text[i]){i++;j++;}

        if (j == m) {
            result.push_back(i-m);
            j = Lps[j - 1];
        }
        else if (i < n && pattern[j] != text[i]) {
            if (j == 0)
                i++;
            else
                j = Lps[j - 1];
        }
    }
}
