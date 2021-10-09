#include <iostream>
#include "matrix.h"


using namespace std;


int main() {
    try {
        int t;
        cin >> t;
        for(int x = 0; x < t; ++x) {
            int n, m;
            cin >> n >> m;
            vector<vector<double>> va(n, vector<double>(m));
            vector<double> vb(n);
            for (int i = 0; i < n; ++i) {
                for (int j = 0; j < m; ++j) {
                    cin >> va[i][j];
                }
                cin >> vb[i];
            }
            auto fres = solve_linear_system_rect(va, vb);
            auto ok = fres.first;
            auto &res = fres.second;
            cout << "\n" << "Case #" << x + 1 << ":" << "\n";
            if(!ok){
                cout << "System is inconsistent." << "\n";
            }
            else {
                cout << "Free variables: ";
                for (int i = 0; i < m; ++i) {
                    if(!res[i].first){
                        cout << "x" << i + 1 << " ";
                    }
                }
                cout << "\n";
                for (int i = 0; i < m; ++i) {
                    if(res[i].first){
                        cout << "x" << i + 1 << " = " << res[i].second << "\n";
                    }
                }
            }
            cout << "\n";
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