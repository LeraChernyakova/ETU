#include <iostream>
#include <cstring>

using namespace std;
class CustomStack {
public:

    CustomStack(){
        mData_size = 0;
        mData = (char **) malloc(3000 * sizeof (char * ));
        for (int i = 0; i < 3000; i++) {
            mData[i] = (char *)malloc (100 * sizeof(char));
            mData[i][0] = '\0';
        }
    }

    ~CustomStack(){
        for (int i = 0; i < mData_size; i++) {
            free(mData[i]);
        }
        free(mData);
    }

    void push(const char* val) { // добавляет новый элемент в стек
        strcpy((mData)[mData_size], val);
        mData_size++;
        (mData)[mData_size][0] = '\0';
    }
    void pop() { // удаляет из стека последний элемент
        mData_size--;
        mData[mData_size][0] = '\0';
    }
    char* top() {// доступ к верхнему элементу
        return mData[mData_size-1];
    }
    size_t size() { // возвращает количество элементов в стеке
        return mData_size;
    }
    bool empty() { // проверяет отсутствие элементов в стеке
        if ((mData) == NULL || mData_size == 0 || mData[0][0] == '\0')
            return true;
        return false;
    }
    void extend(int n) { // расширяет исходный массив на n ячеек
            mData =(char **) realloc(mData, n * sizeof (char * ));
	    for (int i = mData_size; i < n; i++) {
            	mData[i] = (char *)malloc (100 * sizeof(char));
            mData[i][0] = '\0';
            mData_size += n;
            mData[mData_size][0] = '\0';
    }


private:
    unsigned long mData_size;
protected:
    char** mData;
};

int main() {
    string inp;
    CustomStack * theBestStackEver = new CustomStack();
    getline(cin, inp);
    char * tag = new char[100];
    int posCount = 0;
    int i = 0, j = 0;
    while (i < inp.size()) {
        if (inp[i] == '<') {
            i++;
            while (inp[i] != '>') {
                tag[j] = inp[i];
                i++;
                j++;
            }
            tag[j] = '\0';
            /*theBestStackEver->push(tag);
            cout << theBestStackEver->top() << endl;
            theBestStackEver->pop(); */
            if (tag[0] != '/'  && strcmp(tag, "br") != 0 && strcmp(tag, "hr") != 0) {
                theBestStackEver->push(tag);
            } else {
                if (tag[0] == '/') {
                    if (strcmp(theBestStackEver->top(), tag+1)){
                        //cout << theBestStackEver->top() << ' ' << tag << endl;
                        cout << "wrong" << endl;
                        return 0;
                    } else {
                        theBestStackEver->pop();
                    }
                }
            }
            j = 0;

        }
        i++;
    }
    cout << "correct" << endl;
    //cout << theBestStackEver->size() << endl;
    delete theBestStackEver;
    return 0;
}