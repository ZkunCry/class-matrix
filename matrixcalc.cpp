#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string.h>

using namespace std;
//Перечисление ошибок
enum Error
{
    MATRIX_OPERATOR_EQUAL, //Типы ошибок при вызове конкретного метода.
    MATRIX_OPERATOR_MULTI,
    MATRIX_OPERATOR_SUM,
    MATRIX_OPERATOR_SUB,
    MATRIX_OPERATOR_DEL,
    MATRIX_TRANSP,
    MATRIX_INV,
    MATRIX_MINOR,
    MATRIX_GAUSS,
    MATRIX_EXP,
    MATRIX_MULNUM,
    MATRIX_DET

};

class matrix
{
private:
    double** a;
    int n, m, countSwaps;

    void error(int numberErr, const char* errType)
    {
        //Обработка ошибок
        switch (numberErr)
        {
        case MATRIX_OPERATOR_EQUAL:
            printf("Error while executing assignment!\n");
            break;
        case MATRIX_OPERATOR_MULTI:
            printf("Error while executing multiplication function!\n");
            break;
        case MATRIX_OPERATOR_SUM:
            printf("Error while executing sum function!\n");
            break;
        case MATRIX_OPERATOR_SUB:
            printf("Error while executing difference function!\n");
            break; 
        case  MATRIX_OPERATOR_DEL:
            printf("Error while executing the division function!\n");
            break;
        case MATRIX_TRANSP:
            printf("Error while performing matrix transposition!\n");
            break;
        case MATRIX_INV:
            printf("An error occurred while executing the inverse matrix function!\n");
            break;
        case MATRIX_MINOR:
            printf("Error when finding matrix minor!\n");
            break;
        case MATRIX_EXP:
            printf("An error occurred while executing the exponentiation function\n");
            break;
        case MATRIX_GAUSS:
            printf("An error occurred while executing the find triangular matrix function\n");
            break;
        case MATRIX_MULNUM:
            printf("An error occurred while executing the multiplication function\n");
            break;
        case MATRIX_DET:
            printf("An error occurred while executing the determiner function\n");
            break;
        }
        //Вывод на экран типа ошибки
        printf("Type error: %s\n", errType);
    }

public:
    const double eps = 1e-9;

    //Конструкторы(в том числе и копирования) и деструктор///////////
    matrix() :a(NULL), n(0), m(0), countSwaps(1) {}
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
        if (a != nullptr)
        {
            for (i = 0; i < n; i++)
                delete[]a[i];
            delete[]a;
        }
    }
    matrix(const matrix& other)
    {
       
        if (other.a && other.n != 0 && other.m != 0)
        {
            this->n = other.n;
            this->m = other.m;
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
        if (other.n > 0 || other.m > 0 && !(&other))
        {
            if (this->a != nullptr)
            {
                for (int i = 0; i < this->n; i++)
                    delete[]this->a[i];
            }
            else if (this->a == nullptr)
            {
                error(MATRIX_OPERATOR_EQUAL, "Массив содержит нулевое значение или неинициализирован.\n");
                return *this;
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
        else if(other.n <0 || other.m<0 )
        {
            error(MATRIX_OPERATOR_EQUAL, "Размерность матрицы меньше единицы\n");
            return *this;
        }
        else if (other.a == NULL)
        {
            error(MATRIX_OPERATOR_EQUAL, "Матрица неинициализирована\n");
            return *this;
        }
    }
    matrix operator*(const matrix& other)
    {
        if (this->n == other.m && this->m == other.n || this->n == other.n && this->m == other.m && !this || !(&other))
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
        else
        {
            error(MATRIX_OPERATOR_MULTI, "Матрицы не удовлетворяют правилам умножения или содержится неинициализированная матрица\n");
            exit(1);
        }
    }
    matrix &operator *(const int number)
    {
        if (!this)
        {
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    this->a[i][j] *= number;
            return *this;
        }
        else
        {
            error(MATRIX_MULNUM, "Матрица неинициализирована\n");
            exit(1);
        }
    }
    matrix operator+(const matrix& other)
    {
        if (this->n == other.n && this->m == other.m && !a)
        {
            matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++)
            {
                for (int j = 0; j < this->m; j++)
                    temp.a[i][j] = this->a[i][j] + other.a[i][j];
            }
            return temp;
        }
        else
        {
            error(MATRIX_OPERATOR_SUM, "Матрицы не являются квадратными, или матрица неинициализирована.\n");
            exit(1);
        }
    }
    matrix operator-(const matrix& other)
    {
        if (this->n == other.n && this->m == other.m && !a)
        {
            matrix temp(this->n, this->m);
            for (int i = 0; i < this->n; i++)
            {
                for (int j = 0; j < this->m; j++)
                    temp.a[i][j] = this->a[i][j] - other.a[i][j];
            }
            return temp;
        }
        else
        {
            error(MATRIX_OPERATOR_SUB, "Матрицы не являются квадратными, или матрица неинициализирована.\n");
            exit(1);
        }
    }
    matrix& operator/(matrix& a)
    {
        if (!this || !(&a))
        {
            matrix temp(n, m);
            matrix result(n, m);
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    temp.a[i][j] = this->a[i][j];
            a.inversion();
            result = temp * a;
            for (int i = 0; i < n; i++)
                for (int j = 0; j < m; j++)
                    this->a[i][j] = result.a[i][j];
            return *this;
        }
        else
        {
            error(MATRIX_OPERATOR_DEL, "Матрица неинициализирована или нулевая.\n");
            exit(1);
        }
    }
    matrix& operator++()
    {
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                this->a[i][j]++;
        return *this;
    }
    matrix operator++(int)
    { 
        matrix temp(*this);
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                this->a[i][j]++;
        return temp;
    }
    matrix& operator--()
    {
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                this->a[i][j]--;
        return *this;
    }
    matrix operator--(int)
    {
        matrix temp(*this);
        for (int i = 0; i < this->n; i++)
            for (int j = 0; j < this->m; j++)
                this->a[i][j]--;
        return temp;
    }
    double& operator[](int index)
    {
        if (index<0 || index >(this->n + this->m))
        {
            cout << "Error!\n";
        }
        else
            return (*a)[index];

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
        {
            error(MATRIX_EXP, "Степень меньше нуля.\n");
            exit(1);
        }
    }
////////////////////////////////////////////////////////////////////////////////////////
////////////////////Операции над матрицами и методы для вывода/ввода(геттер) матрицы//////////////////////////////////////////////
    matrix transp()
    {
        if (!this)
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
        else
        {
            error(MATRIX_TRANSP, "Матрица неинициализирована.\n");
            exit(1);
        }
    }
    matrix& gauss()
    {
        if (this->n == this->m && this->n >0 && this->m >0)
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
        else
        {
            error(MATRIX_GAUSS, "Матрица не квадратная или неинициализирована.\n");
            exit(1);
        }
    }
    
    double deter()
    {
        if (!this && this->n >0 && this->m >0)
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
        else if(this == NULL)
        {
            error(MATRIX_DET, "Матрица неинициализирована\n");
            exit(1);
        }
        else if (this->n < 1 || this->m <1)
        {
            error(MATRIX_DET, "Размерность матрицы меньше единицы\n");
            exit(1);
        }
    }
    //Функция нахождения минора
    matrix minor(int i, int j)
    {
        if (i > n || j > n || this->a==NULL)
        {
            error(MATRIX_MINOR, "Матриц не инициализирована или вы вышли за пределы матрицы.\n");
            exit(1);
        }
        else
        {
            matrix b(this->n - 1, this->m - 1);
            int c = 0, t = 0, count = 1;
            for (int q = 0; q < n; q++)
            {
                for (int k = 0; k < m; k++)
                {
                    if (q == i - 1 || k == j - 1)
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
        if (!this || this->n > 0 && this->m > 0)
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
            else if (determenant == 0)
            {
                error(MATRIX_INV, "Определитель матрицы равен нулю.\n");
                exit(1);
            }
            else if (this->n != this->m)
            {
                error(MATRIX_INV, "Матрица не квадратная\n");
                exit(1);
            }
        }
        else
        {
            error(MATRIX_INV, "Матрица неинициализирована\n");
            exit(1);
        }
    } 
    double& operator()(int n, int m)
    {
        return (a[n][m]);
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
            sprintf(s, "%11.5lf ", a(i, j));
            out << s;
        }
        out << "  |\n";
    }out << "\n\n";
    return (out);

}
istream& operator>>(istream& istr, matrix &a)
{
    if (a.getn() > 0 && a.getm() > 0)
    {
        for (int i = 0; i < a.getn(); i++)
        {
            for (int j = 0; j < a.getm(); j++)
                istr >> a(i, j);
        }
        return (istr);
    }
    else
        return (istr);
}
int main()
{
    system("chcp 1251>null");
    int n, m, result = 0;
    cin >> n >> m;
    matrix x, temp;
    x.minor(1, 1);
    return 0;
}