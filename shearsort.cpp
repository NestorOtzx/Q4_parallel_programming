#include <iostream>
#include <stdlib.h>
#include <time.h>
#include <algorithm>
#include <math.h>
using namespace std;

void print_matrix(int** matrix, int n) { //O(n^2)
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            cout << matrix[i][j] << "\t";
        }
        cout << endl;
    }
    cout << endl;
}

void sort_row(int** matrix, int n, int row, bool ascending = false) { //O(nlog(n)+n) = O(nlog(n))
    sort(matrix[row], matrix[row] + n);
    if (!ascending){
        reverse(matrix[row], matrix[row]+n);
    }
}


void sort_column(int** matrix, int n, int col) { // O(n+nlog(n)+n) = O(nlogn)
    int* aux = new int[n];
    for (int i = 0; i < n; i++) {
        aux[i] = matrix[i][col];
    }
    sort(aux, aux + n); //ordenar el arreglo auxiliar y luego copiarla en la columna original
    for (int i = 0; i < n; i++) {
        matrix[i][col] = aux[i];
    }
    delete[] aux;
}

void transpose(int** matrix, int n) { //O(n^2)
    for (int i = 0; i < n; i++) {
        for (int j = i + 1; j < n; j++) {
            swap(matrix[i][j], matrix[j][i]);
        }
    }
}

void delete_matrix(int** matrix, int n) { //O(n)
    for (int i = 0; i < n; i++) { 
        delete[] matrix[i];
    }
    delete[] matrix;
}

void shear_sort(int** matrix, int n) //O(log(n)*(2n*(nlog(n)))) = O(n^2*log(n)^2)
{
    for (int i = 0; i<(int)ceil(log2(n))+1; i++)
    {
        for (int j = 0; j<n; j++)
        {
            sort_row(matrix, n, j, j % 2 == 0);
        }
        for (int j = 0; j<n; j++)
        {
            sort_column(matrix, n, j);
        }
    }
}


void alt_shear_sort(int** matrix, int n) 
//O(log(n)*(2n*(nlog(n))+2n^2)) = O(n^2*log(n)^2+n^2log(n)) = O(n^2*log(n)^2) 
//por que n^2log(n)^2 tiene mayor orden que n^2log(n)
{
    for (int i = 0; i<(int)ceil(log2(n))+1; i++)
    {
        for (int j = 0; j<n; j++)
        {
            sort_row(matrix, n, j, j % 2 == 0);
        }
        transpose(matrix, n);
        for (int j = 0; j<n; j++)
        {
            sort_row(matrix, n, j, true);
        }
        transpose(matrix, n);
    }
}

int main() { //O(n^2*log(n)^2 + 3n^2) = O(n^2*log(n)^2)
    srand(0);
    int n = 3; //tamaño arbitrario

    int** matrix = new int*[n];
    for (int i = 0; i < n; i++) { //O(n^2)
        matrix[i] = new int[n];
        for (int j = 0; j < n; j++) {
            matrix[i][j] = rand() % 100;
        }
    }

    cout<<"matrix:"<<endl;
    print_matrix(matrix, n);  //O(n^2)

    //shear_sort(matrix,n);
    alt_shear_sort(matrix, n); //O(n^2*log(n)^2)

    cout<<"Shearsort:"<<endl;
    print_matrix(matrix, n); //O(n^2)

    return 0;
}
