//## 3) Create `main.cpp` skeleton
//Create `~/Documents/CALEB_PORT_UNI/10_Cpp_Projects/MathLabToolkit/src/main.cpp` and paste:

//```cpp 
#include <iostream>
#include <iomanip>
#include <vector>
#include <cmath>
#include <stdexcept>
using namespace std;

using Matrix = vector<vector<double>>;
const double EPS = 1e-9;

// --- Declarations ---
Matrix readMatrix(int r, int c);
void printMatrix(const Matrix& A);
Matrix add(const Matrix& A, const Matrix& B);
Matrix multiply(const Matrix& A, const Matrix& B);
double det2(const Matrix& A);
double det3(const Matrix& A);
bool gaussianSolve(Matrix A, vector<double> b, vector<double>& x); // returns true if unique solution

int main() {
    cout << "=== MathLab Toolkit ===\n"
         << "1) Matrix addition\n"
         << "2) Matrix multiplication\n"
         << "3) Determinant (2x2 or 3x3)\n"
         << "4) Solve Ax=b (2x2 or 3x3)\n"
         << "0) Exit\n";

    while (true) {
        cout << "\nChoose option: ";
        int op; if (!(cin >> op)) return 0;
        if (op == 0) break;

        if (op == 1) {
            int r, c; cout << "Rows Cols: "; cin >> r >> c;
            cout << "Enter A ("<<r<<"x"<<c<<"):\n"; Matrix A = readMatrix(r,c);
            cout << "Enter B ("<<r<<"x"<<c<<"):\n"; Matrix B = readMatrix(r,c);
            try { Matrix C = add(A,B); cout << "A+B:\n"; printMatrix(C); }
            catch (const exception& e) { cout << "Error: " << e.what() << "\n"; }
        }
        else if (op == 2) {
            int r1,c1,r2,c2;
            cout << "A dims (r c): "; cin >> r1 >> c1;
            cout << "Enter A:\n"; Matrix A = readMatrix(r1,c1);
            cout << "B dims (r c): "; cin >> r2 >> c2;
            cout << "Enter B:\n"; Matrix B = readMatrix(r2,c2);
            try { Matrix C = multiply(A,B); cout << "A*B:\n"; printMatrix(C); }
            catch (const exception& e) { cout << "Error: " << e.what() << "\n"; }
        }
        else if (op == 3) {
            int n; cout << "Order (2 or 3): "; cin >> n;
            Matrix A = readMatrix(n,n);
            if (n==2) cout << "det(A) = " << det2(A) << "\n";
            else if (n==3) cout << "det(A) = " << det3(A) << "\n";
            else cout << "Only 2 or 3 supported.\n";
        }
        else if (op == 4) {
            int n; cout << "Size (2 or 3): "; cin >> n;
            cout << "Enter A ("<<n<<"x"<<n<<"):\n"; Matrix A = readMatrix(n,n);
            cout << "Enter b ("<<n<<" values): "; vector<double> b(n); for (double &v: b) cin >> v;
            vector<double> x;
            if (gaussianSolve(A,b,x)) {
                cout << "Solution x:\n";
                for (double v: x) cout << fixed << setprecision(6) << v << " ";
                cout << "\n";
            } else {
                cout << "No unique solution (matrix is singular or near-singular).\n";
            }
        }
        else cout << "Invalid option.\n";
    }
    return 0;
}

// --- Implementations ---
Matrix readMatrix(int r, int c) {
    Matrix A(r, vector<double>(c));
    for (int i = 0; i < r; i++) {
        for (int j = 0; j < c; j++) {
            cin >> A[i][j];
        }
    }
    return A;
}
void printMatrix(const Matrix& A) {
    for (auto& row: A) {
        for (double v: row) cout << setw(10) << fixed << setprecision(4) << v << " ";
        cout << "\n";
    }
}
Matrix add(const Matrix& A, const Matrix& B) {
    int r=A.size(), c=A[0].size();
    if (r!=(int)B.size() || c!=(int)B[0].size()) throw runtime_error("Dimension mismatch for addition");
    Matrix C(r, vector<double>(c,0));
    for (int i=0;i<r;i++) for (int j=0;j<c;j++) C[i][j]=A[i][j]+B[i][j];
    return C;
}
Matrix multiply(const Matrix& A, const Matrix& B) {
    int m=A.size(), n=A[0].size(), n2=B.size(), p=B[0].size();
    if (n!=n2) throw runtime_error("Inner dimensions mismatch for multiplication");
    Matrix C(m, vector<double>(p,0));
    for (int i=0;i<m;i++)
        for (int j=0;j<p;j++) {
            double s=0; for (int k=0;k<n;k++) s+=A[i][k]*B[k][j];
            C[i][j]=s;
        }
    return C;
}
double det2(const Matrix& A) {
    return A[0][0]*A[1][1] - A[0][1]*A[1][0];
}
double det3(const Matrix& A) {
    double a=A[0][0], b=A[0][1], c=A[0][2];
    double d=A[1][0], e=A[1][1], f=A[1][2];
    double g=A[2][0], h=A[2][1], i=A[2][2];
    return a*(e*i - f*h) - b*(d*i - f*g) + c*(d*h - e*g);
}
bool gaussianSolve(Matrix A, vector<double> b, vector<double>& x) {
    int n = A.size();
    // Forward elimination with partial pivoting
    for (int k=0;k<n;k++) {
        int piv = k;
        for (int i=k+1;i<n;i++) if (fabs(A[i][k]) > fabs(A[piv][k])) piv = i;
        if (fabs(A[piv][k]) < EPS) return false; // singular
        if (piv != k) { swap(A[piv], A[k]); swap(b[piv], b[k]); }
        for (int i=k+1;i<n;i++) {
            double f = A[i][k]/A[k][k];
            for (int j=k;j<n;j++) A[i][j] -= f*A[k][j];
            b[i] -= f*b[k];
        }
    }
    // Back substitution
    x.assign(n,0);
    for (int i=n-1;i>=0;i--) {
        double s = b[i];
        for (int j=i+1;j<n;j++) s -= A[i][j]*x[j];
        if (fabs(A[i][i]) < EPS) return false;
        x[i] = s / A[i][i];
    }
    return true;
}