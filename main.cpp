#include <iostream>
#include "matrix.h"


using namespace std;


int main() {
    try {
        matrix<long long> a({{1, 2},
                             {3, 4}});
        matrix<long long> b({{4, 3},
                             {2, 1}});
        cin >> a >> b;
        int n = a.shape().first;
        int m = a.shape().second;
        for (int i = 0; i < n; ++i) {
            for (int j = 0; j < m; ++j) {
                cout << (a + b)[i][j] << " ";
            }
            cout << "\n";
        }
    }
    catch(char const* s){
        cout << s << "\n";
    }
    return 0;
}
