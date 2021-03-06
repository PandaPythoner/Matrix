#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>
#include <algorithm>
#include <queue>

template<class T>
class matrix{
private:
    int n, m;
    std::vector<std::vector<T>> a;
public:

    inline std::pair<int, int> shape(){
        return std::make_pair(n, m);
    }

    matrix() : n(0), m(0) {
        a.clear();
    }

    matrix(int n, int m, T x = 0) : n(n), m(m) {
        a.assign(n, std::vector<T>(m, x));
    }

    matrix(const std::vector<std::vector<T>> &b){
        a.clear();
        n = b.size();
        if(n == 0){
            m = 0;
        }
        else{
            m = b[0].size();
            a.assign(n, std::vector<T>(m));
            for(int i = 0; i < n; ++i){
                if(b[i].size() != m){
                    throw "Matrix initializer is not rectangular";
                }
                for(int j = 0; j < m; ++j){
                    a[i][j] = b[i][j];
                }
            }
        }
    }

    matrix(const std::vector<T> &b){
        a.clear();
        n = 1;
        m = b.size();
        a.assign(n, std::vector<T>(m));
        for (int j = 0; j < m; ++j) {
            a[0][j] = b[j];
        }
    }

    std::vector<T>& operator[](int i){
        return a[i];
    }

    const std::vector<T>& operator[](int i) const {
        return a[i];
    }

    template<class Type> friend matrix<Type> operator+(const matrix<Type>&, const matrix<Type>&);
    template<class Type> friend matrix<Type> operator*(const matrix<Type>&, Type);
    template<class Type> friend matrix<Type> operator*(const matrix<Type>&, const matrix<Type>&);
    template<class Type> friend matrix<Type> transpose(const matrix<Type>&);
    template<class Type> friend matrix<Type> pow(const matrix<Type>&, long long);

    template<class Type> friend std::ostream& operator<<(std::ostream&, const matrix<Type>&);
    template<class Type> friend std::istream& operator>>(std::istream&, matrix<Type>&);

    T determinant();
    T determinant_fast();

    bool gauss();
    void add_to_line(int, int, T);
    void mul_line(int, T);

    matrix<T> inverted();
};


template<class T>
void matrix<T>::add_to_line(int from, int to, T alph){
    for(int i = 0; i < m; ++i){
        a[to][i] += a[from][i] * alph;
    }
}


template<class T>
void matrix<T>::mul_line(int i, T alph){
    for(int j = 0; j < m; ++j){
        a[i][j] *= alph;
    }
}


template<class T>
bool matrix<T>::gauss(){
    int s = std::min(n, m);
    for(int i = 0; i < s; ++i){
        int x = -1;
        for(int j = i; j < s; ++j){
            if(x == -1 && a[j][i] != 0){
                x = j;
            }
        }
        if(x == -1){
            return false;
        }
        a[i].swap(a[x]);
        mul_line(i, 1 / a[i][i]);
        for(int j = i + 1; j < s; ++j){
            if(a[j][i] != 0){
                add_to_line(i, j, - a[j][i]);
            }
        }
    }
    for(int i = s - 1; i >= 0; --i){
        for(int j = i - 1; j >= 0; --j){
            if(a[j][i] != 0){
                add_to_line(i, j, - a[j][i]);
            }
        }
    }
    return true;
}


template<class T>
matrix<T> matrix<T>::inverted(){
    if(n != m){
        throw "Can't find inverted matrix for a non-square matrix";
    }
    matrix<T> x(n, n + n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            x[i][j] = a[i][j];
        }
    }
    for(int i = 0; i < n; ++i){
        x[i][i + n] = 1;
    }
    if(!x.gauss()){
        throw "This matrix can't be inverted";
    }
    matrix<T> res(n, n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < n; ++j){
            res[i][j] = x[i][j + n];
        }
    }
    return res;
}


template<class T>
T matrix<T>::determinant(){
    if(n != m){
        throw "Can't find determinant for a non-square matrix";
    }
    std::vector<int> p(n);
    for(int i = 0; i < n; ++i){
        p[i] = i;
    }
    T res = 0;
    while(true){
        int d = 1;
        T x = 1;
        for(int i = 0; i < n; ++i){
            for(int j = i + 1; j < n; ++j){
                if(p[i] > p[j]){
                    x *= -1;
                }
            }
            d *= a[i][p[i]];
        }
        res += d * x;
        if(!std::next_permutation(p.begin(), p.end())){
            break;
        }
    }
    return res;
}


template<class T>
T matrix<T>::determinant_fast(){
    if(n != m){
        throw "Can't find determinant for a non-square matrix";
    }
    std::vector<T> x(1 << n, 0);
    x[0] = 1;
    for(int msk = 0; msk < (1 << n) - 1; ++msk){
        int o = 1;
        int c = 0;
        for(int i = 0; i < n; ++i){
            if((msk >> i) & 1){
                ++c;
            }
        }
        for(int i = n - 1; i >= 0; --i){
            if((msk >> i) & 1){
                o *= -1;
            }
            else{
                x[msk + (1 << i)] += x[msk] * o * a[c][i];
            }
        }
    }
    return x[(1 << n) - 1];
}


template<class T>
matrix<T> operator+(const matrix<T> &a, const matrix<T> &b){
    int n = a.n;
    int m = a.m;
    if(n != b.n || m != b.m){
        throw "Matrices have different sizes!";
    }
    matrix<T> res(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            res[i][j] = a[i][j] + b[i][j];
        }
    }
    return res;
}

template<class T>
matrix<T> operator*(const matrix<T> &a, T x){
    int n = a.n;
    int m = a.m;
    matrix<T> res(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            res[i][j] = a[i][j] * x;
        }
    }
    return res;
}

template<class T>
matrix<T> operator*(const matrix<T> &a, const matrix<T> &b){
    int n = a.n;
    int k = a.m;
    int m = b.m;
    if(b.n != k){
        throw "Matrices have bad sizes for multiplication";
    }
    matrix<T> res(n, m);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            res[i][j] = 0;
            for(int x = 0; x < k; ++x){
                res[i][j] += a[i][x] * b[x][j];
            }
        }
    }
    return res;
}

template<class T>
matrix<T> transpose(const matrix<T> &a){
    int n = a.n;
    int m = a.m;
    matrix<T> res(m, n);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            res[j][i] = a[i][j];
        }
    }
    return res;
}

template<class T>
matrix<T> pow(const matrix<T> &x, long long n){
    if(n == 1){
        return x;
    }
    if(x.n != x.m){
        throw "Can't raise a non-square matrix to a power";
    }
    matrix<T> a = pow(x, n / 2);
    a = a * a;
    if(n & 1){
        a = a * x;
    }
    return a;
}

template<class T>
std::ostream& operator<<(std::ostream& out, const matrix<T>& a){
    int n = a.n;
    int m = a.m;
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            out << a[i][j] << " ";
        }
        out << "\n";
    }
    return out;
}


template<class T>
std::istream& operator>>(std::istream& in, matrix<T>& a){
    int n, m;
    in >> n >> m;
    a = matrix<T>(n, m);
    for(int i = 0; i < n; ++i) {
        for (int j = 0; j < m; ++j) {
            in >> a[i][j];
        }
    }
    return in;
}

template<class T>
matrix<T> solve_linear_system(const matrix<T> &x, const matrix<T> &y){
    return x.inverted() * y;
}

template<class T>
std::vector<T> solve_linear_system(const std::vector<std::vector<T>> &x, const std::vector<T> &y){
    return transpose(matrix<T>(x).inverted() * transpose(matrix<T>(y)))[0];
}


template<class T>
std::pair<bool, std::vector<std::pair<bool, T>>> solve_linear_system_rect(const std::vector<std::vector<T>> &x, const std::vector<T> &y){
    int n = x.size();
    int m = x[0].size();
    matrix<T> a(n, m + 1);
    for(int i = 0; i < n; ++i){
        for(int j = 0; j < m; ++j){
            a[i][j] = x[i][j];
        }
        a[i][m] = y[i];
    }
    int s = 0;
    int c = 0;
    std::vector<int> f;
    f.reserve(n);
    for(; c < m && s < n; ++c){
        int x = -1;
        for(int j = s; j < n; ++j){
            if(x == -1 && a[j][c] != 0){
                x = j;
            }
        }
        if(x == -1){
            continue;
        }
        a[s].swap(a[x]);
        a.mul_line(c, 1 / a[s][c]);
        f.push_back(c);
        for(int j = 0; j < n; ++j){
            if(j != s && a[j][c] != 0){
                a.add_to_line(s, j, - a[j][c]);
            }
        }
        ++s;
    }
    std::vector<std::pair<bool, T>> res(m, std::make_pair(false, 0));
    for(int i = s; i < n; ++i){
        if(a[i][m] != 0){
            return std::make_pair(false, res);
        }
    }
    for(int i = 0; i < s; ++i){
        res[f[i]] = std::make_pair(true, a[i][m]);
    }
    return make_pair(true, res);
}


#endif //MATRIX_MATRIX_H
