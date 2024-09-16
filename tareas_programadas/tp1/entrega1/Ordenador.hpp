#pragma once

#include <algorithm>

class Ordenador {
    private:
    /* Defina aquí los métodos auxiliares de los
       algoritmos de ordenamiento solamente. */
    // Puede definir cuantos métodos quiera.

    public:
    Ordenador() = default;
    ~Ordenador() = default;

    Ordenador(Ordenador& o) = delete;
    Ordenador(Ordenador&& o) = delete;
    Ordenador& operator=(Ordenador& o) = delete;
    Ordenador& operator=(Ordenador&& o) = delete;

    /* Nota:
     - Si no planea implementar algunos de los métodos de ordenamiento, no los
       borre.
     - Simplemente déjelos con el cuerpo vacío para evitar errores de
       compilación, ya que se ejecutará el mismo main para todas las tareas.
     - Recuerde hacer uso de programación defensiva y documentar los métodos
       con formato Doxygen, por ejemplo.
     - No cambié la firma de los métodos de la clase Ordenador.
     - No lance excepciones para el manejo de errores.
       Ante un error, basta con que el método no modifique el arreglo original
       y que no cause la caída del programa.
    */

    void ordenamientoPorSeleccion(int *A, int n) const {
      for (int i = 0; i < n - 1; ++i) {
        // Seleccionar el elemento más pequeño en A[i:n]
        int min = i;
        for (int j = i + 1; j < n; ++j) {
          if (A[j] < A[min]) {
            // Guardar el índice en m.
            min = j;
          }
        }
        // Intercambiar A[i] con el A[min] resultante.
        if (min != i) {
          std::swap(A[min], A[i]);
        }
      }
    }

    void ordenamientoPorInsercion(int *A, int n) const {}
    void ordenamientoPorMezcla(int *A, int n) const {}
    void ordenamientoPorMonticulos(int *A, int n) const {}
    void ordenamientoRapido(int *A, int n) const {}
    void ordenamientoPorRadix(int *A, int n) const {}

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     *
     * Este método devuelve una cadena de texto que contiene el carné, nombre
     * y tarea.
     *
     * @return std::string Una cadena de texto con los datos de la tarea.
     */
    constexpr const char* datosDeTarea() const {
      return "Carné: 12345, Nombre: AA, Tarea 1";
    }

    /**
     * @brief Retorna el string solicitado con los datos del estudiante y
     * la tarea.
     *
     * @return constexpr const char* String con los datos solicitados.
     */
    constexpr const char* ImprimirDatosDeTarea() const {
      return "Carné: C35280, Nombre: José Manuel Mora Z, Tarea 1 Etapa 1";
    }
};