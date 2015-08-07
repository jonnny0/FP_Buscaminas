#include <iostream>
#include <vector>
#include <cstdlib>
#include <ctime>
#include <string>

using namespace std;

// ENTRADA: int &filas, int &columnas
// SALIDA: vector vector <int>
// Genera la matriz (tablero), con la que trabajará todo el programa a partir de un número de filas y columnas
vector <vector <int> > GeneraTablero (int filas, int columnas) {
    vector <int> unaFila(columnas,0);
    return vector <vector <int> > (filas, unaFila);
}

// ENTRADA: const vector <vector <int> > &matriz, int &fila, int &columna, int posicion
// SALIDA: SIN SALIDA
// Calcula los índices de la matriz pasada posición de la casilla (los almacena en fila y columna pasados por referencia)
void CalculaIndices(const vector <vector <int> > &matriz, int &fila, int &columna, int posicion) {
    int longitudColumna = matriz.at(0).size();
    fila = posicion / longitudColumna;
    columna = posicion % longitudColumna;
}

// ENTRADA: vector <vector <int> > &matriz, int fila, int columna, int numero
// SALIDA: SIN SALIDA
// Modifica el valor de una casilla (fila, columna) en la matriz pasada como referencia
void ModificaCasilla(vector <vector <int> > &matriz, int fila, int columna, int numero) {
    matriz.at(fila).at(columna) = numero;
}


// ENTRADA: vector <vector <int> > &matriz, const vector <int> &posicionMinas, int &fila, int &columna
// SALIDA: SIN SALIDA
// Asigna el valor 9 a la casilla de la matriz mediante fila y columna. Para esto llama a CalculaIndices que pasa
// un número de casilla a su correspondiente valor en índices válidos, y lo modifica mediante la función ModificaCasilla
// Es el lugar inicial de las minas
void ColocaMinas(vector <vector <int> > &matriz, const vector <int> &posicionMinas, int &fila, int &columna) {
    int numeroMinas = posicionMinas.size();

    for (int i=0; i < numeroMinas; i++){
        CalculaIndices(matriz,fila,columna,posicionMinas.at(i));
        ModificaCasilla(matriz,fila,columna,9);
    }
}

// ENTRADA: const vector <vector <int> > &matriz, int numeroMinas
// SALIDA: vector <int>
// Genera aleatoriamente las posiciones (casillas) donde luego va a colocar las minas,
// y las devuelve en un vector de enteros
vector <int> GeneraPosicionMinas(const vector <vector <int> > &matriz, int numeroMinas) {
    int numeroCasillas = matriz.size()*matriz.at(0).size();
    vector <int> minas;
    srand (time(0));

    for (int i = 0; i < numeroMinas; i++) {
        int aleatorio;
        bool repetido;

        do {
            repetido = false;
            aleatorio = rand() % numeroCasillas;
            int j = 0;
            while (repetido == false && j < (int)minas.size()) {
                if (aleatorio == minas.at(j)) {
                    repetido = true;
                }
                j++;
            }
        } while (repetido == true);

        minas.push_back(aleatorio);
    }
    return minas;
}

// ENTRADA: const vector <vector <int> > &matriz, int fila, int columna
// SALIDA: int
// Calcula el número de minas que hay alrededor de cada casilla sin mina y devuelve este
int CalculaNumero(const vector <vector <int> > &matriz, int fila, int columna) {
    int contador = 0;

    for (int f = -1; f <= 1; f++) {
        for (int c = -1; c <= 1; c++) {
            if (!(fila + f == fila && columna + c == columna)) {
                if ((fila + f > -1) && (columna + c > -1) && (fila + f < (int)matriz.size()) && (columna + c < (int)matriz.at(0).size())) {
                    if (matriz.at(fila + f).at(columna + c) == 9) {
                        contador++;
                    }
                }
            }
        }
    }
    return contador;
}

// ENTRADA: vector <vector <int> > &matriz
// SALIDA: SIN SALIDA
// Asigna en la matriz los números de minas que hay alrededor de cada casilla vacía,
// estos los calcula en la función CalculaNumero, y los asgina mediante la función ModificaCasilla
void ColocaNumeros(vector <vector <int> > &matriz) {
    int nuevoValor;
    int longitudFila = matriz.size();
    int longitudColumna = matriz.at(0).size();

    for (int fila = 0; fila < longitudFila; fila++){
        for (int columna = 0; columna < longitudColumna; columna++){
            if (matriz.at(fila).at(columna) != 9) {
                nuevoValor = CalculaNumero(matriz,fila,columna);
                ModificaCasilla(matriz, fila, columna, nuevoValor);
            }
        }
    }
}

// ENTRADA: const vector <vector <int> > &matriz
// SALIDA: SIN SALIDA
// Muestra por pantalla el estado de la matriz: las casillas cerradas (*), las marcadas (?)
// y las abiertas (vacío ó el número de minas de alrededor), mina explotada (X)
void ImprimeTablero(const vector <vector <int> > &matriz) {
    int longitudColumna = matriz.at(0).size();
    int longitudFila = matriz.size();
    cout << endl << "    ";

    for (int c = 0; c < longitudColumna; c++) {
        cout << c << "  ";
    }
    cout << endl;

    for (int c = 0; c < longitudColumna; c++) {
        cout << "----";
    }
    cout << endl;

    for (int f = 0; f < longitudFila; f++) {
        cout << f << " |";
        for (int c = 0; c < longitudColumna; c++) {
            cout << " ";
            if (matriz.at(f).at(c) >= 0 && matriz.at(f).at(c) <= 9) {
                cout << "*";
            } else if (matriz.at(f).at(c) == 10) {
                cout << " ";
            } else if (matriz.at(f).at(c) >= 11 && matriz.at(f).at(c) <= 18) {
                cout << matriz.at(f).at(c) - 10;
            } else if (matriz.at(f).at(c) == 19) {
                cout << "X";
            } else {
                cout << "?";
            }
            cout << "|";
        }
        cout << endl;
    }

    for (int c = 0; c < longitudColumna; c++) {
        cout << "----";
    }
    cout << endl;
}

// ENTRADA: string minusculas
// SALIDA: string
// Entra un string y sale el mísmo en mayúsculas
string PasarAMayusculas(string minusculas) {
    for (int i = 0; i < (int)minusculas.size(); i++) {
        minusculas.at(i) = toupper(minusculas.at(i));
    }
    return minusculas;
}

// ENTRADA: string &accion, int &fila, int &columna, const vector <vector <int> > &matriz
// SALIDA: SIN SALIDA
// Pide por pantalla una acción a realizar, la fila y la columna donde realizarla
// y lo almacena en variables pasadas por referencia, antes pasa la acción a mayúsculas
// para permitir que la palabra se escriba en mayúsculas y minúsculas
void SolicitaJugada(string &accion, int &fila, int &columna, const vector <vector <int> > &matriz) {
    do {
        cout << endl << "ACCION: (A)brir o (M)arcar: ";
        cin >> accion;
        cout << endl << "FILA: ";
        cin >> fila;
        cout << endl << "COLUMNA: ";
        cin >> columna;
        accion = PasarAMayusculas(accion);
    } while ((accion != "A" && accion != "M" && accion != "ABRIR" && accion != "MARCAR") ||
            (fila < 0 || fila > (int)matriz.size()-1) || (columna < 0 || columna > (int)matriz.at(0).size()-1));
}

// ENTRADA: int &filas, int &columnas, int &minas
// SALIDA: SIN SALIDA
// Pide por pantalla las filas, columnas y minas para generar el tablero inicial
// y las almacena en variables pasadas por referencia
void DatosIniciales(int &filas, int &columnas, int &minas) {
    do {
        cout << "NUMERO DE FILAS (MINIMO 4): ";
        cin >> filas;
    } while (filas < 4);

    do {
        cout << "NUMERO DE COLUMNAS (MINIMO 4): ";
        cin >> columnas;
    } while (columnas < 4);

    do {
        cout << "NUMERO DE MINAS (MINIMO 5, MAXIMO 50% DE CASILLAS CON MINA, EN ESTE CASO (" << (filas*columnas)/2 << ")): ";
        cin >> minas;
    } while (minas < 5 || minas > (filas*columnas)/2);
}

// ENTRADA: const vector <vector <int> > &matriz
// SALIDA: bool
// Comprueba si se ha dado la condición de fin del juego ganando,
// es decir que estén todas las casillas abiertas y las minas marcadas
bool CompruebaResuelto (const vector <vector <int> > &matriz) {
    bool resuelto = true;
    for (int f = 0; f < (int)matriz.size() && resuelto == true; f++) {
        for (int c = 0; c < (int)matriz.at(0).size() && resuelto == true; c++) {
            if ((matriz.at(f).at(c) < 10) || (matriz.at(f).at(c) > 19 && matriz.at(f).at(c) != 29)) {
                resuelto = false;
            }
        }
    }
    return resuelto;
}

// ENTRADA: vector <vector <int> > &matriz, int fila, int columna
// SALIDA: SIN SALIDA
// Pasados por valor fila y columna, mira en la matriz esa posición,
// si se encuentra sin marca la pone, y si la tiene la quita
void MarcaCasilla(vector <vector <int> > &matriz, int fila, int columna) {
    if (matriz.at(fila).at(columna) >= 0 && matriz.at(fila).at(columna) <= 9) {
        matriz.at(fila).at(columna) += 20;
    } else if (matriz.at(fila).at(columna) >= 20 && matriz.at(fila).at(columna) <=29) {
        matriz.at(fila).at(columna) -= 20;
    }
}

// ENTRADA: const vector <vector <int> > &matriz, vector <int> &pendientes, int fila, int columna
// SALIDA: SIN SALIDA
// Pasada la matriz, la fila y columna, modifica el vector de enteros pendientes (pasado como referencia)
// añadiéndole las casillas de su alrededor con índices válidos y que no estén abiertas
void InsertaVecinos(const vector <vector <int> > &matriz, vector <int> &pendientes, int fila, int columna) {
    for (int f = -1; f <= 1; f++) {
        for (int c = -1; c <= 1; c++) {
            if (!(fila + f == fila && columna + c == columna)) {
                if ((fila + f > -1) && (columna + c > -1) && (fila + f < (int)matriz.size())
                    && (columna + c < (int)matriz.at(0).size())) {
                    if (matriz.at(fila + f).at(columna + c) < 9) {
                        pendientes.push_back((fila + f) * matriz.at(0).size() + (columna + c));
                    }
                }
            }
        }
    }
}

// ENTRADA: vector <vector <int> > &matriz, int &fila, int &columna
// SALIDA: int
// Abre una casilla cerrada de la matriz, si el contenido está entre 1 y 9 le suma 10,
// si es un 0 le suma 10 y añade para seguir abriendo sus casillas colindantes
// a pendientes mediante el método InsertaVecinos, hasta que aparezca otro número
int AbreCasilla (vector <vector <int> > &matriz, int &fila, int &columna) {
    if (matriz.at(fila).at(columna) >= 0 && matriz.at(fila).at(columna) <= 9) {
        vector <int> pendientes;
        pendientes.push_back(fila * matriz.at(0).size() + columna);

        while (pendientes.size() > 0) {
            int ultimoElemento = pendientes.at(pendientes.size()-1);
            pendientes.pop_back();
            CalculaIndices(matriz, fila, columna, ultimoElemento);

            if (matriz.at(fila).at(columna) > 0 && matriz.at(fila).at(columna) <= 9) {
                matriz.at(fila).at(columna) += 10;
            } else if (matriz.at(fila).at(columna) == 0) {
                matriz.at(fila).at(columna) += 10;
                InsertaVecinos(matriz, pendientes, fila, columna);
            }
        }
    }
    return matriz.at(fila).at(columna);
}

// ENTRADA: vector <vector <int> > &matriz, int numeroMinas, int &fila, int &columna
// SALIDA: SIN SALIDA
// Prepara el tablero para la primera visualización, generando las minas, los números y colocando
// todo en el tablero mediante 3 métodos distintos (GeneraPosicionMinas, ColocaMinas y ColocaNumeros)
void RellenaTablero(vector <vector <int> > &matriz, int numeroMinas, int &fila, int &columna) {
    vector <int> posicionMinas = GeneraPosicionMinas(matriz, numeroMinas);
    ColocaMinas(matriz,posicionMinas,fila,columna);
    ColocaNumeros(matriz);
}

// Este juego va a estar pidiendo acciones hasta que se abra una mina
// o se abran todas las casillas y se marquen todas las minas.
// El funcionamiento es el siguiente:
// Se almacenan las variables, llamando a la función DatosIniciales.
// Se GeneraTablero y se RellenaTablero antes de la primera jugada
// (con las minas y números iniciales).
// Y luego esta pidiendo acciones hasta que estado sea 19 (explotado mina, se pierde)
// o hasta CompruebaResuelto sea verdadero (se han localizado todas las minas, se gana).
int main()
{
    int fila, columna, minas, filasIniciales, columnasIniciales, estado;
    string accion;
    vector <vector <int> > matriz;
    bool resuelto = false;
    DatosIniciales(filasIniciales, columnasIniciales, minas);
    matriz = GeneraTablero(filasIniciales, columnasIniciales);
    RellenaTablero(matriz, minas, fila, columna);

    do {
        ImprimeTablero(matriz);
        SolicitaJugada(accion, fila, columna, matriz);

        if (accion == "M" || accion == "MARCAR") {
            MarcaCasilla(matriz,fila,columna);
        } else {
            estado = AbreCasilla(matriz, fila, columna);
        }
        resuelto = CompruebaResuelto(matriz);
    } while (estado != 19 && resuelto == false);

    ImprimeTablero(matriz);

    if (estado == 19) {
        cout << endl << "¡BOOOM! HAS EXPLOTADO UNA MINA. HAS PERDIDO. FIN DEL JUEGO.";
    } else {
        cout << endl << "¡ENHORABUENA HAS DESCUBIERTO TODAS LAS MINAS!. HAS GANADO. FIN DEL JUEGO.";
    }
}
