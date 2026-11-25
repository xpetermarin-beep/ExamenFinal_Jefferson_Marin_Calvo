// ExamenFinal_Jefferson_Marin_Calvo.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include <iostream>
#include <string>
#include <cctype>

using namespace std;


struct NodoDeque {
    char dato;
    NodoDeque* ant;  
    NodoDeque* sig; 
};

struct Deque {
    NodoDeque* frente; 
    NodoDeque* final;  
};


void inicializarDeque(Deque& d) {
    d.frente = nullptr;
    d.final = nullptr;
}


bool dequeVacia(const Deque& d) {
    return d.frente == nullptr;
}


void insertarFrente(Deque& d, char c) {
    NodoDeque* n = new NodoDeque;
    n->dato = c;
    n->ant = nullptr;
    n->sig = d.frente;

    if (dequeVacia(d)) {
        d.final = n; 
    }
    else {
        d.frente->ant = n;
    }
    d.frente = n;
}


void insertarFinal(Deque& d, char c) {
    NodoDeque* n = new NodoDeque;
    n->dato = c;
    n->sig = nullptr;
    n->ant = d.final;

    if (dequeVacia(d)) {
        d.frente = n; 
    }
    else {
        d.final->sig = n;
    }
    d.final = n;
}


bool eliminarFrente(Deque& d, char& valor) {
    if (dequeVacia(d)) {
        return false;
    }
    NodoDeque* aux = d.frente;
    valor = aux->dato;
    d.frente = aux->sig;

    if (d.frente != nullptr) {
        d.frente->ant = nullptr;
    }
    else {
        d.final = nullptr;
    }
    delete aux;
    return true;
}


bool eliminarFinal(Deque& d, char& valor) {
    if (dequeVacia(d)) {
        return false;
    }
    NodoDeque* aux = d.final;
    valor = aux->dato;
    d.final = aux->ant;

    if (d.final != nullptr) {
        d.final->sig = nullptr;
    }
    else {
        d.frente = nullptr; 
    }
    delete aux;
    return true;
}


void mostrarDeque(const Deque& d) {
    if (dequeVacia(d)) {
        cout << "[ El duque esta vacio ]\n";
        return;
    }
    cout << "Frente -> ";
    for (NodoDeque* p = d.frente; p != nullptr; p = p->sig) {
        cout << "[" << p->dato << "] ";
    }
    cout << "<- Final\n";
}


void liberarDeque(Deque& d) {
    char basura;
    while (eliminarFrente(d, basura)) {
        
    }
}


void submenuDeque() {
    Deque d;
    inicializarDeque(d);

    int opcion;
    char caracter, valor;

    do {
        cout << "\n----- Cola Doble (Deque) -----\n";
        cout << "1. Insertar por el frente\n";
        cout << "2. Insertar por el final\n";
        cout << "3. Eliminar por el frente\n";
        cout << "4. Eliminar por el final\n";                                                      //Submenu
        cout << "5. Mostrar todos los elementos\n";
        cout << "6. Verificar si esta vacia\n";
        cout << "7. Volver al menu principal\n";
        cout << "Opcion: ";
        cin >> opcion;

        switch (opcion) {
        case 1:
            cout << "Caracter a insertar por el frente: ";
            cin >> caracter;
            insertarFrente(d, caracter);
            mostrarDeque(d);
            break;
        case 2:
            cout << "Caracter a insertar por el final: ";
            cin >> caracter;
            insertarFinal(d, caracter);
            mostrarDeque(d);
            break;
        case 3:
            if (eliminarFrente(d, valor)) {
                cout << "Elemento eliminado por el frente: " << valor << "\n";
                mostrarDeque(d);
            }
            else {
                cout << "Error: la deque esta vacia, no se puede eliminar.\n";
            }
            break;
        case 4:
            if (eliminarFinal(d, valor)) {
                cout << "Elemento eliminado por el final: " << valor << "\n";
                mostrarDeque(d);
            }
            else {
                cout << "Error: la deque esta vacia, no se puede eliminar.\n";
            }
            break;
        case 5:
            mostrarDeque(d);                                                                                        //PARTE DE OPCIONES DEL SUBMENU
            break;
        case 6:
            if (dequeVacia(d)) {
                cout << "La deque Si esta vacia.\n";
            }
            else {
                cout << "La deque NO esta vacia.\n";
            }
            break;
        case 7:
            break;
        default:
            cout << "Opcion invalida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 7);

    liberarDeque(d);
}



struct NodoPila {
    char dato;
    NodoPila* sig;
};

struct Pila {
    NodoPila* tope;
};


void inicializarPila(Pila& p) {
    p.tope = nullptr;
}
                                                                                      //ESTRUCTURAMENU

void push(Pila& p, char c) {
    NodoPila* n = new NodoPila;
    n->dato = c;
    n->sig = p.tope;
    p.tope = n;
}


bool pop(Pila& p, char& valor) {
    if (p.tope == nullptr) {
        return false;
    }
    NodoPila* aux = p.tope;
    valor = aux->dato;
    p.tope = aux->sig;
    delete aux;
    return true;
}

bool pilaVacia(const Pila& p) {
    return p.tope == nullptr;
}


int tamanioPila(const Pila& p) {
    int cantidad = 0;
    for (NodoPila* n = p.tope; n != nullptr; n = n->sig) {
        cantidad++;
    }
    return cantidad;
}

void liberarPila(Pila& p) {
    char basura;
    while (pop(p, basura)) {
    
    }
}

bool esApertura(char c) {
    return c == '(' || c == '[' || c == '{';
}

bool esCierre(char c) {
    return c == ')' || c == ']' || c == '}';
}


char aperturaCorrespondiente(char cierre) {
    if (cierre == ')') return '(';
    if (cierre == ']') return '[';
    return '{'; 
}


void ejercicioBalanceo() {
    cout << "Ingrese la expresion matematica a evaluar: ";
    string expresion;
    getline(cin, expresion);

    Pila p;
    inicializarPila(p);

    bool balanceada = true;

    for (int i = 0; i < (int)expresion.size() && balanceada; i++) {
        char c = expresion[i];

        if (esApertura(c)) {
            push(p, c);
        }
        else if (esCierre(c)) {
            char tope;
            if (pop(p, tope)) {
                char esperada = aperturaCorrespondiente(c);
                if (tope != esperada) {
                    balanceada = false;
                    cout << "Error: el cierre '" << c
                        << "' no coincide con el ultimo simbolo abierto '"
                        << tope << "'. Se esperaba '" << esperada << "'.\n";
                }
            }
            else {
                
                balanceada = false;
                cout << "Error: el cierre '" << c
                    << "' aparece sin una apertura correspondiente.\n";
            }
        }
    }

    if (balanceada && !pilaVacia(p)) {
        balanceada = false;
        cout << "Error: faltan " << tamanioPila(p)
            << " simbolo(s) de apertura por cerrar.\n";
    }

    cout << "*******************************************************\n";
    if (balanceada) {
        cout << "RESULTADO: La expresion SI esta balanceada.\n";
    }
    else {
        cout << "RESULTADO: La expresion NO esta balanceada.\n";
    }

    liberarPila(p);
}


void generarSubconjuntos(const string& cadena, int indice, string actual) {
    
    if (indice == (int)cadena.size()) {
        cout << "{";
        for (char c : actual) {
            cout << c;
        }
        cout << "}\n";
        return;
    }

 
    generarSubconjuntos(cadena, indice + 1, actual);

  
    actual.push_back(cadena[indice]);
    generarSubconjuntos(cadena, indice + 1, actual);
}


bool cadenaValida(const string& cadena, string& motivo) {
    if (cadena.empty()) {
        motivo = "la cadena no puede estar vacia.";
        return false;
    }
    if ((int)cadena.size() > 8) {
        motivo = "la cadena debe tener maximo 8 caracteres.";
        return false;
    }
    for (int i = 0; i < (int)cadena.size(); i++) {
        for (int j = i + 1; j < (int)cadena.size(); j++) {
            if (cadena[i] == cadena[j]) {
                motivo = "el carácter '" + string(1, cadena[i]) +
                    "' se repite; no se permiten caracteres repetidos.";                                                       //PARTE DE CADENASUBCONJUNTOS
                return false;
            }
        }
    }
    return true;
}

void ejercicioSubconjuntos() {
    string cadena, motivo;

    do {
        cout << "Ingrese la cadena (maximo 8 caracteres, sin repetidos): ";
        getline(cin, cadena);

       
        string limpia;
        for (char c : cadena) {
            if (!isspace((unsigned char)c)) {
                limpia += c;
            }
        }
        cadena = limpia;

        if (!cadenaValida(cadena, motivo)) {
            cout << "Entrada invalida: " << motivo << " Intente nuevamente.\n";
        }
    } while (!cadenaValida(cadena, motivo));

    cout << "\nSubconjuntos de la cadena \"" << cadena << "\":\n";
    generarSubconjuntos(cadena, 0, "");

    int total = 1;
    for (int i = 0; i < (int)cadena.size(); i++) {
        total *= 2;
    }
    cout << "Total de subconjuntos: " << total << "\n";
}


int main() {
    int opcion;

    do {
        cout << "\n*****************************************************\n";
        cout << "                MENU PRINCIPAL\n";
        cout << "*****************************************************\n";
        cout << "1. Cola doble (Deque) implementada con nodos\n";
        cout << "2. Pila dinamica para verificar expresion balanceada\n";
        cout << "3. Recursividad: generador de subconjuntos de una cadena\n";
        cout << "4. Salir\n";
        cout << "*********************************************************\n";
        cout << "Seleccione una opcion: ";                                                                                       //MENU PRINCIPAL
        cin >> opcion;

      
        cin.ignore(10000, '\n');

        switch (opcion) {
        case 1:
            submenuDeque();
            break;
        case 2:
            ejercicioBalanceo();
            break;
        case 3:
            ejercicioSubconjuntos();
            break;
        case 4:
            cout << "Saliendo del programa. ¡HASTA LUEGO!\n";
            break;                                                                                                  //OPCIONES DEL MENU PRINCIPAL
        default:
            cout << "Opción invalida. Intente nuevamente.\n";
            break;
        }
    } while (opcion != 4);

    return 0;
}







