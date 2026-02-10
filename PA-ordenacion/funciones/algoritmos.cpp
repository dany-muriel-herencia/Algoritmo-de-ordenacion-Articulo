#include "algoritmos.h"

// --- QuickSort ---
// Usamos el elemento central como pivote para evitar el peor caso en arreglos ya ordenados
int partition(vector<int>& arr, int low, int high) {
    int pivot = arr[low + (high - low) / 2];
    int i = low;
    int j = high;

    while (i <= j) {
        while (arr[i] < pivot) {
            i++;
        }
        while (arr[j] > pivot) {
            j--;
        }
        if (i <= j) {
            swap(arr[i], arr[j]);
            i++;
            j--;
        }
    }
    return i;
}

void quickSort(vector<int>& arr, int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        
        // Ordenar recursivamente los subarreglos
        // pi es el punto de partición devuelto por nuestro esquema de partición hoare-like modificado
        if (low < pi - 1)
            quickSort(arr, low, pi - 1);
        if (pi < high)
            quickSort(arr, pi, high);
    }
}

// --- MergeSort ---
void merge(vector<int>& arr, int left, int mid, int right) {
    int n1 = mid - left + 1;
    int n2 = right - mid;

    // Vectores temporales
    vector<int> L(n1), R(n2);

    for (int i = 0; i < n1; i++)
        L[i] = arr[left + i];
    for (int j = 0; j < n2; j++)
        R[j] = arr[mid + 1 + j];

    int i = 0, j = 0, k = left;
    while (i < n1 && j < n2) {
        if (L[i] <= R[j]) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) {
        arr[k] = L[i];
        i++;
        k++;
    }

    while (j < n2) {
        arr[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(vector<int>& arr, int left, int right) {
    if (left < right) {
        int mid = left + (right - left) / 2;
        mergeSort(arr, left, mid);
        mergeSort(arr, mid + 1, right);
        merge(arr, left, mid, right);
    }
}

// --- HeapSort ---
void heapify(vector<int>& arr, int n, int i) {
    int largest = i;
    int left = 2 * i + 1;
    int right = 2 * i + 2;

    if (left < n && arr[left] > arr[largest])
        largest = left;

    if (right < n && arr[right] > arr[largest])
        largest = right;

    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(vector<int>& arr) {
    int n = arr.size();

    // Construir el heap (reorganizar el arreglo)
    for (int i = n / 2 - 1; i >= 0; i--)
        heapify(arr, n, i);

    // Extraer elementos del heap uno por uno
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

// --- ShellSort ---
void shellSort(vector<int>& arr) {
    int n = arr.size();
    // Empezar con un gap grande, luego reducir el gap
    for (int gap = n / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < n; i += 1) {
            int temp = arr[i];
            int j;
            for (j = i; j >= gap && arr[j - gap] > temp; j -= gap)
                arr[j] = arr[j - gap];
            arr[j] = temp;
        }
    }
}

// --- Calculadora de Memoria ---
long long calcularMemoriaBytes(const vector<int>& arr, bool esMergeSort) {
    long long n = arr.size();
    long long bytesPorInt = sizeof(int); // Generalmente 4 bytes
    long long memoriaBase = n * bytesPorInt;
    
    if (esMergeSort) {
        // MergeSort utiliza espacio auxiliar proporcional a N en la fase de mezcla.
        // El enunciado pide especificamente incluir el vector auxiliar temporal.
        // Memoria Total = Memoria Vector Original + Memoria Vector Auxiliar
        return memoriaBase * 2; 
    }
    
    // QuickSort, HeapSort, ShellSort son algoritmos in-place (o usan stack O(log n)),
    // pero la memoria principal de datos es solo el vector.
    return memoriaBase;
}