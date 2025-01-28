#include <string>
#include <algorithm>
#include <iostream>
#include <ctime>
using namespace std;

int main(){
    string S;
    string T;

    cin >> S;
    cin >> T;
    unsigned result = 0;
    unsigned int start = clock();
    if (T.length() != S.length()){
        cout << -1 << '\n';
        unsigned int end = clock();
        return 0;
    } else if (T==S){
        cout << 0;
        return 0;
    }

    do{
        rotate(T.begin(), T.begin()+1, T.end());
        result++;
    }
    while (result != T.length() && T != S);

    result = T.length() - result;
    if (result) cout << result << endl;
    else cout << -1;
}