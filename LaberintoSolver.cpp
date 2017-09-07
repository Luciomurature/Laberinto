#include "LaberintoSolver.h"
#include "Pila.h"

typedef struct {
    unsigned x;
    unsigned y;
} coord;


/**
 * Función recursiva para solucionar el laberinto
 * @param x Pocición x de la celda actual
 * @param y Pocición y de la celda actual
 * @return true si la celda es parte de la solución, sino false
 */
bool LaberintoSolver::solve(unsigned x, unsigned y) {
    Pila<coord> pila;
    bool termine = false;
    coord actual = {x, y};

    pila.push(actual);

    while (!pila.esVacia()) {
        actual = pila.peek();
        x = actual.x;
        y = actual.y;
        if (!m->esVisitado(x, y)) {
            m->visitar(x, y);
            pintar(x, y, 1);
        }
        int celda = m->getData(x, y);
        // Base
        if ((x == w - 1 && y == h - 1) || termine) {
            pintar(x, y, 2); //Encontre
            termine = true;
            pila.pop();
        } else if ((celda & 0x02) && y != h - 1 && !m->esVisitado(x, y + 1)) {
            pila.push({x, y + 1});
        } else if ((celda & 0x04) && x != w - 1 && !m->esVisitado(x + 1, y)) {
            pila.push({x + 1, y});
        } else if ((celda & 0x01) && y != 0 && !m->esVisitado(x, y - 1)) {
            pila.push({x, y - 1});
        } else if ((celda & 0x08) && x != 0 && !m->esVisitado(x - 1, y)) {
            pila.push({x - 1, y});
        } else {
            pintar(x, y, 0); //Encontre
            pila.pop();
        }
    }
}

/**
 * Constructor de LaberintoSolver
 * @param callback Función callback que hace algo segun si es solución o no la celda actual
 * @param m Laberinto a solucionar
 */
LaberintoSolver::LaberintoSolver(Funcion callback, MazeGenerator *m) {
    this->pintar = callback;
    this->m = m;
    this->w = m->getW();
    this->h = m->getH();
}

/**
 * Ejecuta el solver desde la posicion 0 0
 */
void LaberintoSolver::run() {
    solve(0, 0);
}