#include <utility>
#include <vector>
#include <stdexcept>

using namespace std;

template<typename T>
class Matrix {
    private:
        vector<T> mas;
        size_t row, col;

    public:
        /*
            creates a matrix with size (n, m) out of a vector
        */
        Matrix(vector<T> d, int _n, int _m) { 
            row = _n;
            col = _m;
            if (row * col == d.size()) {
                mas = d;
            } else {
                std::cerr << "Cannot create a matrix with size (" << row << ", " << col << ")!\n";
                throw std::runtime_error("");
            }
        }

        /*
            returns a pair (rows, columns) 
        */
        pair<size_t, size_t> size() const { 
            return make_pair(row, col);
        }

        /*
            returns (i, j) element of martrix
        */
        T elem(int i, int j) const {
            auto r = col * i + j;
            return mas[r];
        }

        /*
            returns a reference to (i, j) element of matrix
        */
        T& elem(int i, int j) {
            auto r = col * i + j;
            return mas[r];
        }

        /*
            Summs two matrices, so S[i,j] = A[i, j] + B[i, j]
        */
        Matrix<T>& operator += (const Matrix<T>& other) { 
            auto a = other.size();
            if ((*this).size() == a) {
                for (size_t i = 0; i < a.first; ++i) {
                    for (size_t j = 0; j < a.second; ++j) {
                        mas[i * a.second + j] += other.elem(i, j);
                    }
                }
                return *this;
            } else {
                std::cerr << "Cannot sum matrices with sizes (" << row << ", " << col << ") and (" << a.first << ", " << a.second << ")!\n";
                throw std::runtime_error("");
            }
        }

        /*
            multiplies a matrix and a constant
        */
        Matrix<T>& operator *= (const T t) {
            for (size_t i = 0; i < row; ++i) {
                for (size_t j = 0; j < col; ++j) {
                    mas[i * col + j] *= t;
                }
            }
            return *this;
        }

        /*
            returns Matrix class vector mas
        */
        vector<T> get_vec() const {
            return mas;
        }

        /*
            transposes a matrix
        */
        Matrix<T>& transpose() {
            vector<T> g;
            for (size_t j = 0; j < col; ++j) {
                for (size_t i = 0; i < row; ++i) {
                    g.push_back(mas[i * col + j]);
                }
            }
            size_t c = row;
            row = col;
            col = c;
            mas = g;
            return *this;
        }

        /*
            is used in function transposed()
        */
        void transposed_change(vector<T> g) {
            size_t c = row;
            row = col;
            col = c;
            mas = g;
        }

        /*
            returns another matrix, which is transposed
        */
        Matrix<T> transposed() const {
            Matrix chn = *this;
            vector<T> g;
            for (size_t j = 0; j < col; ++j) {
                for (size_t i = 0; i < row; ++i) {
                    g.push_back(mas[i * col + j]);
                }
            }
            chn.transposed_change(g);
            return chn;
        }

        /*
            is used somewhere here...
            returns mas[g]
        */
        T operator[] (size_t g) const {
            return mas[g];
        }

        /*
            multiplies matrices
        */
        Matrix<T>& operator *= (const Matrix& other) {
            if (col == other.size().first) {
                Matrix<T> y = *this;
                auto pa = other.size();
                mas.clear();
                mas.resize(pa.second * row);
                for (size_t i = 0; i < row; ++i) {
                    for (size_t j = 0; j < pa.second; ++j) {
                        mas[i*pa.second + j] = 0;
                        for (size_t t = 0; t < col; ++t) {
                            mas[pa.second * i + j] += y[i * col + t] * other[t * pa.second + j];
                        }
                    }
                }
                col = pa.second;
                return *this;
            } else {
                std::cerr << "Cannot multiply matrices with sizes (" << row << ", " << col << ") and (" << other.size().first << ", " << other.size().second << ")!\n";
                throw std::runtime_error("");
            }
        }

        /*
            multiplies matrices
        */
        Matrix<T> operator * (const Matrix& other) const {
            Matrix<T> y = *this;
            y *= other;
            return y;
        }

        /*
            matrix iterator
        */
        typedef typename vector<T>::iterator Iter;
        Iter begin() {
            return mas.begin();
        }
        Iter end() {
            return mas.end();
        }

        /*
            matrix const_iterator
        */
        typedef typename vector<T>::const_iterator IterC;
        IterC begin() const {
            return mas.begin();
        }
        IterC end() const {
            return mas.end();
        }

        /*
            overloaded matrix operator <<
        */
        friend std::ostream& operator<< (std::ostream &out, const Matrix<T> &a) { // <<
            auto p = a.size();
            for (auto i = 0; i < p.first; ++i) {
                for (auto j = 0; j < p.second; ++j) {
                    out << a.elem(i,j) << ' ';
                }
                out << '\n';
            }
            return out;
        }
};
