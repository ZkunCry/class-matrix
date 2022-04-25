#include <stdio.h>
#include <malloc.h>
#include <iostream>
#include <cmath>
using namespace std;

class matrix
{
private:
    double** a;
    int n, m, countSwaps;
public:
    const double eps = 1e-9;
    double& operator()(int n, int m);
    //Конструкторы(в том числе и копирования) и деструктор///////////
    matrix() :a(0), n(0), m(0), countSwaps(1) {}

    matrix(int N, int M) :n(N), m(M)
    {
        countSwaps = 1;
        int i = 0, j = 0;
        a = new double* [n];
        for (i = 0; i < n; i++)
            a[i] = new double[m];
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++)
                a[i][j] = 0;
        }
    }
    ~matrix()
    {
        int i = 0;
        if (a != NULL)
        {
            for (i = 0; i < n; i++)
                delete[]a[i];
            delete[]a;
        }
    }
    matrix(const matrix& other)
    {
        this->n = other.n;
        this->m = other.m;
        if (other.a && other.n != 0 && other.m != 0)
        {
            a = new double* [n];
            for (int i = 0; i < n; i++)
                this->a[i] = new double[other.m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                this->a[i][j] = other.a[i][j];
        }
    }
//////////////////////////////////////////////////////
////////////Перегрузка операторов = - + *////////////////
    matrix& operator = (const matrix& other)
    {
        if (this->a != nullptr)
        {
            for (int i = 0; i < this->n; i++)
                delete[]this->a[i];
        }
        delete[]a;
        this->n = other.n;
        this->m = other.m;
        this->a = new double* [other.n];
        for (int i = 0; i < n; i++)
        {
            this->a[i] = new double[other.m];
        }
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
            {
                this->a[i][j] = other.a[i][j];
            }
        }
        return *this;
    }

    matrix operator*(const matrix& other)
    {
        if (this->n == other.m && this->m == other.n || this->n == other.n && this->m == other.m)
        {
            matrix temp(this->n, other.m);
            for (int i = 0; i < this->n; i++)
            {
                for (int j = 0; j < other.m; j++)
                {
                    for (int k = 0; k < this->n; k++)
                        temp.a[i][j] += this->a[i][k] * other.a[k][j];
                }
            }
            return temp;
        }
    }
    matrix &operator *(const int number)
    {
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                this->a[i][j] *= number;
        return *this;
    }
    matrix operator+(const matrix& other)
    {
        if (this->n == other.n && this->m == other.m)
        {
            matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++)
            {
                for (int j = 0; j < this->m; j++)
                    temp.a[i][j] = this->a[i][j] + other.a[i][j];
            }
            return temp;
        }
    }
    matrix operator-(const matrix& other)
    {
        if (this->n == other.n && this->m == other.m)
        {
            matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++)
            {
                for (int j = 0; j < this->m; j++)
                    temp.a[i][j] = this->a[i][j] - other.a[i][j];
            }
            return temp;
        }
    }
////////////////////////////////////////////////////////////////////////////////////////
////////////////////Операции над матрицами и методы для вывода/ввода(геттер) матрицы//////////////////////////////////////////////
    matrix transp()
    {
        int i = 0, j = 0;
        matrix temp(this->m, this->n);
        for (i = 0; i < this->n; i++)
        {
            for (j = 0; j < this->m; j++)
                temp.a[j][i] = this->a[i][j];
        }
        return temp;
    }
    void set()
    {
        int i = 0, j = 0;
        for (i = 0; i < n; i++)
        {
            for (j = 0; j < m; j++)
                cin >> a[i][j];
        }
    }
    void output()
    {
        int i = 0, j = 0;
        for (i = 0; i < n; i++)
        {
            printf("| ");
            for (j = 0; j < m; j++)
                printf("%11.5lf ", a[i][j]);
            printf("  |\n");
        }
        printf("\n\n");
    }
    matrix& gauss()
    {
        int i = 0, j = 0, k;
        double temp = 0;
        for (i = 0; i < this->n; ++i)
        {

            int iMax = i;
            for (j = i + 1; j < this->n; ++j)
                if (fabs(this->a[j][i]) > fabs(this->a[iMax][i]))
                    iMax = j;
            if (fabs(this->a[iMax][i]) < eps)
                continue;
            for (k = 0; k < this->m; ++k)
            {
                temp = this->a[i][k];
                this->a[i][k] = this->a[iMax][k];
                this->a[iMax][k] = temp;
            }
           this->countSwaps = -1 * this->countSwaps * (i != iMax ? 1 : -1);
            for (j = i + 1; j < this->n; ++j)
            {
                double q = -this->a[j][i] / this->a[i][i];
                for (k = this->m - 1; k >= i; --k)
                    this->a[j][k] += q * this->a[i][k];
            }
        }
        return *this;
    }
    matrix& operator^(int n)
    {
        matrix temp(this->n, this->m),temp2(this->n,this->m);
        int q = 1;
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                temp.a[i][j] = this->a[i][j];
        while (q != n)
        {
                for (int i = 0; i < this->n; i++)
                {
                    for (int j = 0; j < this->m; j++)
                        for (int k = 0; k < this->n; k++)
                            temp2.a[i][j] += temp.a[i][k] * this->a[k][j];
                }
                for (int i = 0; i < this->n; i++)
                    for (int j = 0; j < this->m; j++)
                        temp.a[i][j] = temp2.a[i][j];

                for (int i = 0; i < this->n; i++)
                    for (int j = 0; j < this->m; j++)
                        temp2.a[i][j] =0;
           q++;
        }
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                this->a[i][j] = temp.a[i][j];
        return *this;
    }
    int deter()
    {
        matrix temp(this->n, this->m);
        double determenation = 1;
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                temp.a[i][j] = this->a[i][j];
        }
        temp.gauss();
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < m; j++)
                this->a[i][j] = temp.a[i][j];
        }
        for (int i = 0; i < this->n; i++)
        {
            determenation *= temp.a[i][i];
        }
        determenation *= temp.countSwaps;
        return determenation;
    }
    matrix minor(int i, int j)
    {
        matrix b(this->n-1, this->m-1);
        int c=0, t=0,count=1;
        for (int q = 0; q < n; q++)
        {
            for (int k = 0; k < m; k++)
            {
                if (q == i-1  || k == j-1)
                    continue;
                else
                {
                    b.a[c][t] = this->a[q][k];
                    t++;
                    if (t > n - 2)
                    {
                        t = 0;
                        c++;
                    }
                }
            }
        }
        return b;
    }
    double get()
    {
        return *(*a);
    }
    int getn()
    {
        return n;
    }
    int getm()
    {
        return m;
    }

};
ostream& operator<<(ostream& out, matrix a)
{
    a.get();
    for (int i = 0; i < a.getn(); i++)
    {
        out << "| ";
        for (int j = 0; j < a.getm(); j++)
        {
            printf("%11.5lf ", a(i, j));
        }
        out << "  |\n";
    }out << "\n\n";
    return (out);

}
istream& operator>>(istream& istr, matrix &a)
{
    for (int i = 0; i < a.getn(); i++)
    {
        for (int j = 0; j < a.getm(); j++)
            istr >> a(i, j);
    }
    return (istr);

}
double& matrix::operator()(int n, int m)
{
    return (a[n][m]);
}

int main()
{
    system("chcp 1251>null");
    int n, m, result = 0;
    cin >> n >> m;
    matrix x(n, m), temp2(n-1,m-1);
    cin >> x;
    cout << x;
    return 0;
}