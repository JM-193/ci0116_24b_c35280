#pragma once

class Ordenador {
    private:
    /* Defina aquí los métodos auxiliares de los
       algoritmos de ordenamiento solamente. */
    // Puede definir cuantos métodos quiera.

      // TODO(jm): doc
      void mergeSort(int* A, int first, int last) const {
        // Revisar si el arreglo solo tiene un elemento o está vacío.
        if (first >= last) { return; }

        int mid = (first + last) / 2;
        // Ordenar cada mitad
        this->mergeSort(A, first, mid);
        this->mergeSort(A, mid + 1, last);
        // Mezclar las dos mitades, ordenadas.
        merge(A, first, mid, last);
      }

      // TODO(jm): doc
      void merge(int* A, int first, int mid, int last) const {
        // Calcular las longitudes de los dos arreglos.
        int leftLen = mid - first + 1;
        int rightLen = last - mid;

        // Sub-arreglos para ordenar.
        int* leftArr = new int[leftLen];
        int* rightArr = new int[rightLen];

        // Copiar los elementos a los sub-arreglos.
        for (int i = 0; i < leftLen; ++i) {
          leftArr[i] = A[first + i];
        }
        for (int j = 0; j < rightLen; ++j) {
          rightArr[j] = A[mid + 1 + j];
        }

        // Índices para los sub-arreglos y el arreglo principal.
        int i = 0, j = 0, k = first;

        // Mezclar los sub-arreglos temporales, de forma ordenada.
        while (i < leftLen && j < rightLen) {
          if (leftArr[i] <= rightArr[j]) {
            A[k++] = leftArr[i++];
          } else {
            A[k++] = rightArr[j++];
          }
        }

        // Al terminar, agregar los elementos restantes al final del arreglo.
        while (i < leftLen) {
          A[k++] = leftArr[i++];
        }
        while (j < rightLen) {
          A[k++] = rightArr[j++];
        }

        // Liberar la memoria dinámica.
        delete[] rightArr;
        delete[] leftArr;
      }

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

    // TODO(jm): doc
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
          int temp = A[min];
          A[min] = A[i];
          A[i] = temp;
        }
      }
    }

    // TODO(jm): doc
    void ordenamientoPorInsercion(int *A, int n) const {
      for (int i = 1; i < n; ++i) {
        int key = A[i];
        // Insertar A[i] en el sub-arreglo ordenado A[0:i-1]
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
          A[j + 1] = A[j];
          j = j - 1;
        }
        // Insertar key.
        A[j + 1] = key;
      }
    }

    // TODO(jm): doc
    void ordenamientoPorMezcla(int *A, int n) const {
      this->mergeSort(A, 0, n - 1);
    }

    // void ordenamientoPorMonticulos(int *A, int n) const {}
    // void ordenamientoRapido(int *A, int n) const {}
    // void ordenamientoPorRadix(int *A, int n) const {}

    /**
     * @brief Retorna un std::string con los datos de la tarea.
     *
     * Este método devuelve una cadena de texto que contiene el carné, nombre
     * y tarea.
     *
     * @return std::string Una cadena de texto con los datos de la tarea.
     */
    constexpr const char* datosDeTarea() const {
      return "Carné: C35280, Nombre: José Manuel Mora Z, Tarea 1 Etapa 1";
    }
};
