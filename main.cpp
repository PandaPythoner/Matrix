#include <iostream>
#include "matrix.h"


using namespace std;


int main() {
    try {
        matrix<long long> a, b;
        long long x, y;
        cout << "Type first matrix (a):\n";
        cin >> a;
        cout << "Type second matrix (b):\n";
        cin >> b;
        cout << "Type number for multiplication (x):";
        cin >> x;
        cout << "Type number for pow (y):";
        cin >> y;
        if(a.shape() == b.shape()){
            cout << "a + b = \n" << a + b << "\n\n";
        }
        cout << "a * x = \n" << a * x << "\n\n";
        if(a.shape().second == b.shape().first) {
            cout << "a * b = \n";
            cout << a * b << "\n\n";
        }
        cout << "transpose(a) = \n" << transpose(a) << "\n\n";
        if(a.shape().first == a.shape().second){
            cout << "a ** y = \n" << pow(a, y) << "\n\n";
        }
    }
    catch(char const* s){
        cout << s << "\n";
    }
    return 0;
}
