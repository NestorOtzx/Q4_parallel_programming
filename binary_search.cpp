#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int solve(int arr[], int l, int h, int x) {
    int mid = l + (h - l) / 2;
    if (arr[mid] == x) 
    {
        return mid; 
    }
    else if(l <= h) {
        if (arr[mid] > x) 
        {
            return solve(arr, l, mid - 1, x);
        }else{
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

    int result = solve(arr, 0, n - 1, x);

    if (result != -1) {
        cout<<"Valor encontrado en la posición: "<<result<<endl;
    } else {
        cout<<"Valor no encontrado."<<endl;
    }

    delete[] arr;

    return 0;
}
