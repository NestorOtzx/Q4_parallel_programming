#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

int result = -1;


int solve(int arr[], int l, int h, int x) {
    int ans = -1;
    while (l <= h && ans == -1 && result == -1)
    {
        if (arr[l] == x)
        {
            #pragma omp critical
            {
                cout<<"[Hilo "<<omp_get_thread_num()<<"] Valor encontrado en la posición: "<<l<<endl;
            }
            ans = l;
        }else if (arr[h] == x)
        {
            #pragma omp critical
            {
                cout<<"[Hilo "<<omp_get_thread_num()<<"] Valor encontrado en la posición: "<<h<<endl;
            }
            ans = h;
        }
        else{
            ++l; //"recurre" sobre l+1 y h-1
            --h;
        }
    }
    return ans;
}

int main() {
    srand(3); 
    int n = 60;
    int* arr = new int[n];

    for (int i = 0; i < n; i++) {
        arr[i] = rand() % n; 
    }

    int x = rand() % n;
    cout<<"Valor a buscar: "<<x<<endl;


    #pragma omp parallel
    {
        int num_threads = omp_get_num_threads();
        int thread_id = omp_get_thread_num();
        int chunk_size = n / num_threads;
        int l = thread_id * chunk_size; //limite inferior
        int h = (thread_id == num_threads - 1) ? (n - 1) : (l + chunk_size - 1); //limite superior

        #pragma omp critical
        {
            cout<<"[Hilo "<<thread_id<<"] Procesando rango ["<<l<<", "<<h<<"]\n";
        }

        int local_result = -1;
        if (result == -1) //si ya lo encontro no lo sigue buscando
        {
            local_result = solve(arr, l, h, x);
        }
         

        if (local_result != -1) {
            #pragma omp critical
            {
                if (result == -1) {
                    result = local_result;
                }
            }
        }
    }

    if (result != -1) {
        cout<<"Valor encontrado en la posición: "<<result<<endl;
    } else {
        cout<<"Valor no encontrado."<<endl;
    }

    delete[] arr;
    return 0;
}
