auto kmp_cycle(std::string& pat, std::string& text){ //2nd stepik (find index of cycle shift, if can't return -1)
    auto res = -1;
    if (pat.length() != text.length()){
        return res;
    }
    std::string s = text + "#" + pat + pat;
    unsigned len_text = text.length();
    unsigned len_s = s.length();
    int j = 0;
    for (unsigned i = len_text + 1; i < len_s; i++){
        unsigned k = i;
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