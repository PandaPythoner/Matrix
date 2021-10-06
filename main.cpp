#include <iostream>
#include "matrix.h"


using namespace std;


int main() {
    try {
        int n;
        cout << "Type linear system size:";
        cin >> n;
        vector<vector<double>> va(n, vector<double>(n));
        vector<double> vb(n);
        for(int i = 0; i < n; ++i){
            for(int j = 0; j < n; ++j){
                cin >> va[i][j];
            }
            cin >> vb[i];
        }
        auto res = solve_linear_system(va, vb);
        for(int i = 0; i < n; ++i){
            cout << res[i] << " ";
        }
        cout << "\n";
        matrix<double> a, b;
        double x;
        long long y;
        cout << "Type first matrix (a):\n";
        cin >> a;
        auto inva = a.inverted();
        cout << "inverted(a) = \n" << inva << "\n\n";
        cout << "inv() * a = \n" << inva * a << "\n\n";
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

/*
5 5
1 0 3 0 2
8 5 2 0 1
7 3 9 6 1
9 7 0 1 2
0 9 8 2 1
*/