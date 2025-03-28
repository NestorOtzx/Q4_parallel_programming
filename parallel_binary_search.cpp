#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
#include <omp.h>
using namespace std;

int solve(int arr[], int l, int h, int x) {
    int mid = l + (h - l) / 2;
    if (arr[mid] == x) {
        #pragma omp critical
        {
            cout<<"[Hilo "<<omp_get_thread_num()<<"] Valor encontrado en la posición: "<<mid<<endl;
        }
        return mid;
    } else if (l <= h) {
        if (arr[mid] > x) {
            return solve(arr, l, mid - 1, x);
        } else {
            return solve(arr, mid + 1, h, x);
        }
    }
    return -1;
}

int main() {
    srand(0); 
    int n = 60;
    int* arr = new int[n];

    int prev = 0;
    for (int i = 0; i < n; i++) {
        arr[i] = rand() % 5 + prev; 
        prev=arr[i];
    }

    int x = rand() % (arr[n-1]+1);
    cout<<"Arr: [";
    for (int i = 0; i < n; i++) {
     cout << arr[i] << " ";
    }
    cout<<"]\nValor a buscar: "<<x<<endl;

    int result = -1;

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
                if (result == -1 || local_result < result) {
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
