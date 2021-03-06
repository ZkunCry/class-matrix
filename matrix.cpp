#include "matrix.h"
const double eps = 1e-9;

matrix::matrix() :a(NULL), n(0), m(0), countSwaps(1) {}
matrix::matrix(int N, int M) :n(N), m(M)
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
matrix::~matrix()
{
    int i = 0;
    if (a != nullptr)
    {
        for (i = 0; i < n; i++)
            delete[]a[i];
        delete[]a;
    }
}
matrix::matrix(const matrix& other)
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
matrix& matrix::operator = (const matrix& other)
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
            error(MATRIX_OPERATOR_EQUAL, "?????? ???????? ??????? ???????? ??? ?????????????????.\n");
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
    else if (other.n < 0 || other.m < 0)
    {
        error(MATRIX_OPERATOR_EQUAL, "??????????? ??????? ?????? ???????\n");
        return *this;
    }
    else if (other.a == NULL)
    {
        error(MATRIX_OPERATOR_EQUAL, "??????? ??????????????????\n");
        return *this;
    }
}
matrix matrix::operator*(const matrix& other)
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
        error(MATRIX_OPERATOR_MULTI, "??????? ?? ????????????? ???????? ????????? ??? ?????????? ???????????????????? ???????\n");
        exit(1);
    }
}
matrix& matrix::operator *(const int number)
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
        error(MATRIX_MULNUM, "??????? ??????????????????\n");
        exit(1);
    }
}
matrix matrix::operator+(const matrix& other)
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
        error(MATRIX_OPERATOR_SUM, "??????? ?? ???????? ???????????, ??? ??????? ??????????????????.\n");
        exit(1);
    }
}
matrix matrix::operator-(const matrix& other)
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
        error(MATRIX_OPERATOR_SUB, "??????? ?? ???????? ???????????, ??? ??????? ??????????????????.\n");
        exit(1);
    }
}
matrix& matrix::operator/(matrix& a)
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
        error(MATRIX_OPERATOR_DEL, "??????? ?????????????????? ??? ???????.\n");
        exit(1);
    }
}
matrix& matrix::operator++()
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->a[i][j]++;
    return *this;
}
matrix matrix::operator++(int)
{
    matrix temp(*this);
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->a[i][j]++;
    return temp;
}
matrix& matrix::operator--()
{
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->a[i][j]--;
    return *this;
}
matrix matrix::operator--(int)
{
    matrix temp(*this);
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->m; j++)
            this->a[i][j]--;
    return temp;
}
double& matrix::operator[](int index)
{
    if (index<0 || index >(this->n + this->m))
    {
        cout << "Error!\n";
    }
    else
        return (*a)[index];

}
matrix& matrix::operator^(int n)
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
        error(MATRIX_EXP, "??????? ?????? ????.\n");
        exit(1);
    }
}
////////////////////////////////////////////////////////////////////////////////////////
////////////////////???????? ??? ????????? ? ?????? ??? ??????/?????(??????) ???????//////////////////////////////////////////////
matrix matrix::transp()
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
        error(MATRIX_TRANSP, "??????? ??????????????????.\n");
        exit(1);
    }
}
matrix& matrix::gauss()
{
    if (this->n == this->m && this->n > 0 && this->m > 0)
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
        error(MATRIX_GAUSS, "??????? ?? ?????????? ??? ??????????????????.\n");
        exit(1);
    }
}

double matrix::deter()
{
    if (!this && this->n > 0 && this->m > 0)
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
    else if (this == NULL)
    {
        error(MATRIX_DET, "??????? ??????????????????\n");
        exit(1);
    }
    else if (this->n < 1 || this->m < 1)
    {
        error(MATRIX_DET, "??????????? ??????? ?????? ???????\n");
        exit(1);
    }
}
//??????? ?????????? ??????
matrix matrix::minor(int i, int j)
{
    if (i > n || j > n || this->a == NULL)
    {
        error(MATRIX_MINOR, "?????? ?? ???????????????? ??? ?? ????? ?? ??????? ???????.\n");
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
double matrix::GetMatrix()
{
    return *(*a);
}
int matrix::GetN()
{
    return n;
}
int matrix::GetM()
{
    return m;
}
matrix& matrix::inversion()
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
            error(MATRIX_INV, "???????????? ??????? ????? ????.\n");
            exit(1);
        }
        else if (this->n != this->m)
        {
            error(MATRIX_INV, "??????? ?? ??????????\n");
            exit(1);
        }
    }
    else
    {
        error(MATRIX_INV, "??????? ??????????????????\n");
        exit(1);
    }
}
double& matrix::operator()(int n, int m)
{
    return (a[n][m]);
}
void matrix::error(int numberErr, const char* errType)
{
    //????????? ??????
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
    //????? ?? ????? ???? ??????
    printf("Type error: %s\n", errType);
}

ostream& operator<<(ostream& out, matrix a)
{

    a.GetMatrix();
    for (int i = 0; i < a.GetN(); i++)
    {
        out << "| ";
        for (int j = 0; j < a.GetM(); j++)
        {
            char s[25];
            sprintf(s, "%11.5lf ", a(i, j));
            out << s;
        }
        out << "  |\n";
    }out << "\n\n";
    return (out);

}
istream& operator>>(istream& istr, matrix& a)
{
    if (a.GetN() > 0 && a.GetM() > 0)
    {
        for (int i = 0; i < a.GetN(); i++)
        {
            for (int j = 0; j < a.GetM(); j++)
                istr >> a(i, j);
        }
        return (istr);
    }
    else
        return (istr);
}