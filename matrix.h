#ifndef MATRIX_MATRIX_H
#define MATRIX_MATRIX_H

#include <vector>

template<class T>
class matrix{
private:
    int n, m;
    std::vector<std::vector<T>> a;
public:

    matrix() : n(0), m(0) {
        a.clear();
    }

    matrix(int n, int m) : n(n), m(m) {
        a.assign(n, std::vector<T>(m));
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
    template<class Type> friend matrix<Type> pow(const matrix<Type>&, Type);
};


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
            res[i][j] = a[i][j] * T;
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
matrix<T> pow(const matrix<T> &x, T n){
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

#endif //MATRIX_MATRIX_H
