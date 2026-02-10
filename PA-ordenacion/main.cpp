#include <iostream>
#include <vector>
#include <chrono>
#include <algorithm>
#include <fstream>
#include <sstream>
#include <iomanip>
#include <string>
#include "funciones/algoritmos.h"

using namespace std;
using namespace std::chrono;

// Función para cargar datos desde un archivo .txt/csv
bool cargarDatos(const string& nombreArchivo, vector<int>& datos) {
    datos.clear();
    // Intentar abrir en la carpeta datos/ relativa a la raíz
    string ruta = "datos/" + nombreArchivo;
    ifstream archivo(ruta);
    
    if (!archivo.is_open()) {
        cerr << "Error: No se pudo abrir el archivo " << ruta << endl;
        return false;
    }

    string linea;
    if (getline(archivo, linea)) {
        stringstream ss(linea);
        string valorStr;
        while (getline(ss, valorStr, ',')) {
            try {
                datos.push_back(stoi(valorStr));
            } catch (...) {
                continue; // Ignorar errores de parsing si los hay
            }
        }
    }
    return true;
}

// Wrapper para llamar a los algoritmos y medir tiempo/memoria
void probarAlgoritmo(const string& nombre, void (*func)(vector<int>&), const vector<int>& datosOriginales, bool esMergeSort) {
    // Copiamos el arreglo original para ordenar esta instancia sin afectar al original en memoria
    vector<int> arr = datosOriginales;
    
    long long memoria = calcularMemoriaBytes(arr, esMergeSort);
    
    auto start = high_resolution_clock::now();
    func(arr);
    auto stop = high_resolution_clock::now();
    
    auto durationNano = duration_cast<nanoseconds>(stop - start).count();
    double durationMs = durationNano / 1000000.0;
    
    // Imprimir resultados
    cout << left << setw(12) << nombre 
         << " | Tiempo: " << right << setw(10) << fixed << setprecision(4) << durationMs << " ms"
         << " | Mem Aprox: " << setw(15) << memoria << " bytes" << endl;
}

// Wrappers específicos
void runQuickSort(vector<int>& arr) {
    if (!arr.empty()) quickSort(arr, 0, arr.size() - 1);
}

void runMergeSort(vector<int>& arr) {
    if (!arr.empty()) mergeSort(arr, 0, arr.size() - 1);
}

int main() {
    // Configuraciones de prueba
    vector<int> tamanios = {1000, 10000, 50000, 100000, 1000000}; 
    vector<string> tipos = {"aleatorio", "ordenado", "inverso"};
    
    cout << "=================================================================================\n";
    cout << "   Comparative Analysis of Memory Performance and Processing Time (C++)\n";
    cout << "=================================================================================\n\n";

    for (int n : tamanios) {
        cout << ">>> N = " << n << " <<<\n";
        
        for(const string& tipo : tipos) {
            string nombreArchivo = "vector_" + tipo + "_" + to_string(n) + ".txt";
            vector<int> datosCargados;
            
            if (cargarDatos(nombreArchivo, datosCargados)) {
                
                string tituloCaso;
                 if (tipo == "aleatorio") tituloCaso = "Aleatorio";
                 else if (tipo == "ordenado") tituloCaso = "Ya Ordenado";
                 else tituloCaso = "Ordenado Inverso";

                cout << "\n[ Caso: " << tituloCaso << " (Leido de " << nombreArchivo << ") ]\n";
                
                probarAlgoritmo("QuickSort", runQuickSort, datosCargados, false);
                probarAlgoritmo("MergeSort", runMergeSort, datosCargados, true);
                probarAlgoritmo("HeapSort",  heapSort,     datosCargados, false);
                probarAlgoritmo("ShellSort", shellSort,    datosCargados, false);
            }
        }
        cout << "---------------------------------------------------------------------------------\n";
    }

    return 0;
}