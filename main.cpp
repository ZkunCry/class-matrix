#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <iostream>
#include <cmath>
#include <string.h>
#include "C:\Users\Eugene\source\repos\classmatrixgit\classmatrixgit\matrix.h"

using namespace std;

int main()
{
    system("chcp 1251>null");
    int n, m, result = 0;
    cin >> n >> m;
    matrix x(n,m), temp;
    cin >> x;
    cout << x;
    return 0;
}