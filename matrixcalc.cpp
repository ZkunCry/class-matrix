#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string.h>
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
        if (n > 0)
        {
            matrix temp(this->n, this->m), temp2(this->n, this->m);
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
                        temp2.a[i][j] = 0;
                q++;
            }
            for (int i = 0; i < this->n; i++)
                for (int j = 0; j < this->m; j++)
                    this->a[i][j] = temp.a[i][j];
            return *this;
        }
        else
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
    matrix &inversion()
    {
        matrix Temp(this->n, this->m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                Temp.a[i][j] = this->a[i][j];
       double determenant = Temp.deter();
       if (determenant != 0 || this->n == this->m)
       {
           int i = 0, j = 0, k = 0;
           if (this->n == this->m)
           {
               double temp;
               matrix E(this->n, this->m);
               for (i = 0; i < this->n; i++)
                   for (j = 0; j < this->n; j++)
                   {
                       E.a[i][j] = 0.0;
                       if (i == j)
                           E.a[i][j] = 1.0;
                   }
               for (k = 0; k < this->n; k++)
               {
                   temp = this->a[k][k];
                   for (j = 0; j < this->n; j++)
                   {
                       this->a[k][j] /= temp;
                       E.a[k][j] /= temp;
                   }
                   for (i = k + 1; i < this->n; i++)
                   {
                       temp = this->a[i][k];

                       for (j = 0; j < this->n; j++)
                       {
                           this->a[i][j] -= this->a[k][j] * temp;
                           E.a[i][j] -= E.a[k][j] * temp;
                       }
                   }
               }

               for (k = this->n - 1; k > 0; k--)
               {
                   for (i = k - 1; i >= 0; i--)
                   {
                       temp = this->a[i][k];

                       for (j = 0; j < this->n; j++)
                       {
                           this->a[i][j] -= this->a[k][j] * temp;
                           E.a[i][j] -= E.a[k][j] * temp;
                       }
                   }
               }
               for (i = 0; i < this->n; i++)
                   for (j = 0; j < this->n; j++)
                       this->a[i][j] = E.a[i][j];
           }
           return *this;
       }
       else
           return *this;
    }
    matrix& operator/(matrix& a)
    {
        matrix temp(n, m);
        matrix result(n, m);
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                temp.a[i][j]= this->a[i][j];
        a.inversion();
        result = temp *a;
        for (int i = 0; i < n; i++)
            for (int j = 0; j < m; j++)
                this->a[i][j] = result.a[i][j];
        return *this;
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
            char s[25];
            sprintf(s,"%11.5lf ", a(i, j));
            out << s;
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
    matrix x(n,m), temp2(n,m),temp3(n,m);
    cin >> x>>temp2;
    temp3 = x / temp2;
    cout << temp3;
    return 0;
}