#include <string>
#include <vector>
#include <iostream>


auto kmp_cycle(std::string& pat, std::string& text){
    auto res = -1;
    if (pat.length() != text.length()){
        return res;
    }
    std::string s = text + "#" + pat + pat;
    size_t len_text = text.length();
    size_t len_s = s.length();
    int j = 0;
    for (size_t i = len_text + 1; i < len_s; i++){
        size_t k = i;
        while (s[j] == s[k]){
            j++;
            k++;
            if (j == len_text){
                res = k - 2*len_text - 1;
                return res;
            }
        }
        j = 0;
    }
    return res;
}