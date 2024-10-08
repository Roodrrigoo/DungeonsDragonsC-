#include <iostream>
#include <fstream>
#include <string>
#include <sstream>
#include <vector>
#include <list>
#include <locale>
#include <random>
#include <algorithm>

using namespace std;

template <typename T>
class Grafo {
private:
    vector<vector<T>> matrizAdyacencia;

public:
    Grafo(const vector<vector<T>>& adyacencia) : matrizAdyacencia(adyacencia) {}

    vector<T> obtenerVecinos(T nodo) const {
        if (nodo < 1 || nodo > matrizAdyacencia.size()) {
            cerr << "Nodo fuera de rango." << endl;
            return vector<T>();
        }

        return matrizAdyacencia[nodo - 1];
    }
};

template <typename T>
vector<vector<T>> leerArchivoDungeon(const string& nombreArchivo) {
    ifstream archivo(nombreArchivo);
    vector<vector<T>> grafo;

    if (!archivo.is_open()) {
        cerr << "No se pudo abrir el archivo." << endl;
        return grafo;
    }

    string linea;

    while (getline(archivo, linea)) {
        istringstream iss(linea);
        T numero;
        vector<T> vecinos;

        while (iss >> numero) {
            vecinos.push_back(numero);
        }

        grafo.push_back(vecinos);
    }

    archivo.close();

    return grafo;
}

template <typename T>
struct Nodo {
    T dato;
    Nodo<T>* anterior;
    Nodo<T>* siguiente;

    Nodo(const T& dato) : dato(dato), anterior(nullptr), siguiente(nullptr) {}
};

template <typename T>
class ListaDoble {
private:
    Nodo<T>* head;
    Nodo<T>* tail;
    int size;

public:
    ListaDoble() : head(nullptr), tail(nullptr), size(0) {}

    void push_front(const T& dato) {
        Nodo<T>* nuevoNodo = new (nothrow) Nodo<T>(dato);
        if (head == nullptr) {
            head = tail = nuevoNodo;
        } else {
            nuevoNodo->siguiente = head;
            head->anterior = nuevoNodo;
            head = nuevoNodo;
        }
        size++;
    }

    void push_back(const T& dato) {
        Nodo<T>* nuevoNodo = new (nothrow) Nodo<T>(dato);
        if (tail == nullptr) {
            head = tail = nuevoNodo;
        } else {
            tail->siguiente = nuevoNodo;
            nuevoNodo->anterior = tail;
            tail = nuevoNodo;
        }
        size++;
    }

    int getSize() const {
        return size;
    }

    bool empty() const {
        return size == 0;
    }

    T getRandomElement() const {
        random_device rd;
        mt19937 gen(rd());
        uniform_int_distribution<int> dist(0, size - 1);
        int indice = dist(gen);

        Nodo<T>* actual = head;
        for (int i = 0; i < indice; ++i) {
            actual = actual->siguiente;
        }

        return actual->dato;
    }

    ~ListaDoble() {
        while (head != nullptr) {
            Nodo<T>* temp = head;
            head = head->siguiente;
            delete temp;
        }
    }
};

struct Hechizo {
    string nombre;
    int MP;
};

bool compare(const Hechizo& a, const Hechizo& b) {
    return a.nombre < b.nombre;
}

list<Hechizo> ordenar_hechizos(const string& archivo) {
    ifstream documento(archivo);

    list<Hechizo> hechizos;

    string linea;
    getline(documento, linea);
    while (getline(documento, linea)) {
        size_t pos = linea.find(",");
        string nombre = linea.substr(0, pos);
        string MP = linea.substr(pos + 1);

        Hechizo hechizo;
        hechizo.nombre = nombre;
        hechizo.MP = stoi(MP);

        hechizos.push_back(hechizo);
    }
    hechizos.sort(compare);

    return hechizos;
}

class Monstruo {
public:
    string name;
    float cr;
    string type;
    string size;
    int ac;
    int hp;
    string align;

    Monstruo(const string& n, float c, const string& t, const string& s, int a, int h, const string& al)
        : name(n), cr(c), type(t), size(s), ac(a), hp(h), align(al) {}
};

class NodoMonstruoDerrotado {
public:
    Monstruo monstruo;
    NodoMonstruoDerrotado* siguiente;

    NodoMonstruoDerrotado(const Monstruo& m) : monstruo(m), siguiente(nullptr) {}
};

class ArchivoMonstruos {
private:
    ListaDoble<Monstruo> monstruos;

public:
    ArchivoMonstruos() {}

    bool abrir(const string& catalogo) {
        ifstream archivo(catalogo);

        if (!archivo) {
            cerr << "No se pudo abrir el archivo " << catalogo << endl;
            return false;
        }

        string linea;

        getline(archivo, linea);
        while (getline(archivo, linea)) {
            istringstream ss(linea);
            string n, t, s, al;
            float c;
            int a, h;
            string campo;
            string campoAC;
            string campoHP;

            if (getline(ss, n, ',') && getline(ss, campo, ',') && getline(ss, t, ',') &&
                getline(ss, s, ',') && getline(ss, campoAC, ',') && getline(ss, campoHP, ',') &&
                getline(ss, al, ',')) {
                c = stoi(campo);
                a = stoi(campoAC);
                h = stoi(campoHP);
                monstruos.push_back(Monstruo(n, c, t, s, a, h, al));
            }
        }

        archivo.close();
        return true;
    }

    const ListaDoble<Monstruo>& getMonstruos() const {
        return monstruos;
    }
};

bool abrirArchivo(ListaDoble<Monstruo>& monstruos) {
    string catalogo = "monsters.csv";
    ifstream archivo(catalogo);

    if (!archivo) {
        cerr << "No se pudo abrir el archivo " << catalogo << endl;
        return false;
    }
    string linea;

    getline(archivo, linea);
    while (getline(archivo, linea)) {
        istringstream ss(linea);
        string n, t, s, al;
        float c;
        int a, h;
        string campo;
        string campoAC;
        string campoHP;
        if (getline(ss, n, ',') && getline(ss, campo, ',') && getline(ss, t, ',') &&
            getline(ss, s, ',') && getline(ss, campoAC, ',') && getline(ss, campoHP, ',') &&
            getline(ss, al, ',')) {
            c = stoi(campo);
            a = stoi(campoAC);
            h = stoi(campoHP);
            monstruos.push_back(Monstruo(n, c, t, s, a, h, al));
        }
    }

    archivo.close();
    return true;
}

Monstruo elegirMonstruoAleatorio(const ListaDoble<Monstruo>& monstruos) {
    if (monstruos.empty()) {
        cerr << "La lista de monstruos está vacía." << endl;
        return Monstruo("", 0.0, "", "", 0, 0, "");
    }
    return monstruos.getRandomElement();
}

template <class T>
class Cuarto {
public:
    T dato;
    Cuarto* anterior;
    Cuarto* siguiente;

    Cuarto(const T& valor) : dato(valor), anterior(nullptr), siguiente(nullptr) {}
};

template <class T>
class ListaDoble2 {
private:
    Cuarto<T>* primero;
    Cuarto<T>* ultimo;
    int size;

public:
    ListaDoble2() : primero(nullptr), ultimo(nullptr), size(0) {}

    void agregarCuarto(const T& valor) {
        Cuarto<T>* nuevoCuarto = new Cuarto<T>(valor);
        if (ultimo == nullptr) {
            primero = ultimo = nuevoCuarto;
        } else {
            ultimo->siguiente = nuevoCuarto;
            nuevoCuarto->anterior = ultimo;
            ultimo = nuevoCuarto;
        }
        size++;
    }

    void mostrarCuartos(const ListaDoble<Monstruo>& listaMonstruos, const Grafo<int>& grafo) {
        Cuarto<T>* actual = primero;
        int cuartoNum = 1;
        while (actual != nullptr) {
            Monstruo monstruoAleatorio = listaMonstruos.getRandomElement();

            cout << "[" << cuartoNum << "] Cuarto con " << monstruoAleatorio.name << ": ";
            vector<int> vecinos = grafo.obtenerVecinos(cuartoNum);

            for (int vecino : vecinos) {
                cout << vecino << " ";
            }
            cout << endl;

            actual = actual->siguiente;
            cuartoNum++;
        }
    }

    ~ListaDoble2() {
        Cuarto<T>* actual = primero;
        while (actual != nullptr) {
            Cuarto<T>* temp = actual;
            actual = actual->siguiente;
            delete temp;
        }
    }
};

class ListaMonstruosDerrotados {
private:
    NodoMonstruoDerrotado* primero;
    int size;

public:
    ListaMonstruosDerrotados() : primero(nullptr), size(0) {}

    void agregarMonstruoDerrotado(const Monstruo& monstruo) {
        NodoMonstruoDerrotado* nuevoNodo = new NodoMonstruoDerrotado(monstruo);
        if (primero == nullptr) {
            primero = nuevoNodo;
        } else {
            NodoMonstruoDerrotado* actual = primero;
            while (actual->siguiente != nullptr) {
                actual = actual->siguiente;
            }
            actual->siguiente = nuevoNodo;
        }
        size++;
    }

    void imprimir() {
        NodoMonstruoDerrotado* actual = primero;
        while (actual != nullptr) {
            cout << actual->monstruo.name << endl;
            actual = actual->siguiente;
        }
    }

    ~ListaMonstruosDerrotados() {
        while (primero != nullptr) {
            NodoMonstruoDerrotado* temp = primero;
            primero = primero->siguiente;
            delete temp;
        }
    }
};

class Jugador {
public:
    Jugador(string nombre, string raza) : nombre("Rodrigo"), raza("humano"), hp(100), mp(100) {}
    string nombre;
    string raza;
    int hp;
    int mp;

    void mostrarInformacion() {
        cout << "Nombre: " << nombre << endl;
        cout << "Raza: " << raza << endl;
        cout << "HP: " << hp << endl;
        cout << "MP: " << mp << endl;
        cout << "Monstruos derrotados:" << endl;
    }
};

int main() {
    ListaDoble2<int> listaDeCuartos;
    ArchivoMonstruos archivoMonstruos;
    list<Hechizo> hechizos = ordenar_hechizos("hechizos.csv");

    archivoMonstruos.abrir("monsters.csv");

    for (int i = 1; i <= 31; i++) {
        listaDeCuartos.agregarCuarto(i);
    }

    vector<vector<int>> grafo = leerArchivoDungeon<int>("dungeon.txt");
    Grafo<int> grafoDungeon(grafo);

    listaDeCuartos.mostrarCuartos(archivoMonstruos.getMonstruos(), grafoDungeon);

    cout << "Hechizos disponibles (ordenados): " << endl;
    for (Hechizo hechizo : hechizos) {
        cout << hechizo.nombre << "," << hechizo.MP << endl;
    }

    return 0;
}
