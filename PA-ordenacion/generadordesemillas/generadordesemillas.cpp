#include <iostream>
#include <vector>
#include <fstream>
#include <algorithm>
#include <random>
#include <string>

using namespace std;

// Función para guardar el vector en un archivo .txt
void guardarArchivo(const string& nombreArchivo, const vector<int>& datos) {
    // La ruta relativa asume que se ejecuta desde la carpeta generadordesemillas
    // o desde la raíz del proyecto dependiendo de cómo se compile/ejecute.
    // Usaremos rutas relativas asumiendo ejecución desde la carpeta del ejecutable generador.
    // Si el ejecutable está en generadordesemillas/, la carpeta datos está en ../datos/
    
    string ruta = "../datos/" + nombreArchivo;
    ofstream archivo(ruta);
    
    if (!archivo.is_open()) {
        // Intentar ruta alternativa por si se ejecuta desde la raíz
        ruta = "datos/" + nombreArchivo;
        archivo.open(ruta);
    }

    if (archivo.is_open()) {
        for (size_t i = 0; i < datos.size(); ++i) {
            archivo << datos[i];
            if (i < datos.size() - 1) {
                archivo << ","; // Formato CSV simple
            }
        }
        archivo.close();
        cout << "Archivo generado: " << ruta << endl;
    } else {
        cerr << "Error al abrir el archivo " << ruta << " para escritura." << endl;
    }
}

// Generadores
void generarAleatorio(vector<int>& arr, int n) {
    arr.resize(n);
    random_device rd;
    mt19937 gen(rd());
    uniform_int_distribution<> dis(0, 100000);
    for (int i = 0; i < n; ++i) arr[i] = dis(gen);
}

void generarOrdenado(vector<int>& arr, int n) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) arr[i] = i;
}

void generarInverso(vector<int>& arr, int n) {
    arr.resize(n);
    for (int i = 0; i < n; ++i) arr[i] = n - i;
}

int main() {
    // Tamaños para las pruebas (N)
    vector<int> tamanios = {1000, 10000, 50000, 100000, 1000000}; 
    vector<string> tipos = {"aleatorio", "ordenado", "inverso"};

    for (int n : tamanios) {
        for (const string& tipo : tipos) {
            vector<int> datos;
            
            if (tipo == "aleatorio") generarAleatorio(datos, n);
            else if (tipo == "ordenado") generarOrdenado(datos, n);
            else if (tipo == "inverso") generarInverso(datos, n);
            
            string nombreArchivo = "vector_" + tipo + "_" + to_string(n) + ".txt";
            guardarArchivo(nombreArchivo, datos);
        }
    }

    cout << "Generación de semillas completada." << endl;
    return 0;
}