#include <iostream>
#include "matrix.h"


using namespace std;


int main() {
    matrix<long long> a({{1, 2}, {3, 4}});
    matrix<long long> b({{4, 3}, {2, 1}});
    int n = 2;
    int m = 2;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            cout << (a + b)[i][j] << " ";
        }
        cout << "\n";
    }
    return 0;
}
