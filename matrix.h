#pragma once

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
    void error(int numberErr, const char* errType);
public:

    matrix();
    matrix(int N, int M);
    ~matrix();
    matrix(const matrix& other);
    matrix& operator = (const matrix& other);
    matrix operator*(const matrix& other);
    matrix& operator *(const int number);
    matrix operator+(const matrix& other);
    matrix operator-(const matrix& other);
    matrix& operator/(matrix& a);
    matrix& operator++();
    matrix operator++(int);
    matrix& operator--();
    matrix operator--(int);
    double& operator[](int index);
    matrix& operator^(int n);
    matrix transp();
    matrix& gauss();
    double deter();
    matrix minor(int i, int j);
    double GetMatrix();
    int GetN();
    int GetM();
    matrix& inversion();
    double& operator()(int n, int m);

};
ostream& operator<<(ostream& out, matrix a);
istream& operator>>(istream& istr, matrix& a);