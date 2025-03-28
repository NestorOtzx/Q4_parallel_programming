#include <iostream>
#include <cstdlib>
#include <ctime>
#include <algorithm>
using namespace std;

int solve(int arr[], int l, int h, int x) {
    int ans = -1;
    while (l <= h && ans == -1)
    {
        if (arr[l] == x)
        {
            ans = l;
        }else if (arr[h] == x)
        {
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
