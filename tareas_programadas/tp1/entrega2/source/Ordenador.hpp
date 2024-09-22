// Copyright 2024 Jose Manuel Mora Z
#pragma once

class Ordenador {
 private:
  /* Defina aquí los métodos auxiliares de los
      algoritmos de ordenamiento solamente. */
  // Puede definir cuantos métodos quiera.

  static inline void swap(int& a, int& b) {
    int temp = a;
    a = b;
    b = temp;
  }

  /**
   * @brief Primera parte del Merge Sort, parte el arreglo en dos hasta que
   * queda vacío o con solo un elemento adentro, en cuyo caso retorna. Luego
   * llama a merge() para continuar el proceso.
   *
   * @param A Arreglo a ordenar.
   * @param first Índice de la primera posición en el arreglo.
   * @param last Índice de la última posición en el arreglo.
   */
  void mergeSort(int* A, const int first, const int last) const {
    // Revisar si el arreglo solo tiene un elemento o está vacío.
    if (first >= last) { return; }

    int mid = (first + last) / 2;
    // Ordenar cada mitad
    this->mergeSort(A, first, mid);
    this->mergeSort(A, mid + 1, last);
    // Mezclar las dos mitades, ordenadas.
    merge(A, first, mid, last);
  }

  /**
   * @brief Parte principal del Merge Sort. Combina las dos mitades del arreglo
   * de forma ordenada.
   *
   * @param A Arreglo a ordenar.
   * @param first Índice de la primera posición en el arreglo.
   * @param mid Índice de la posición a la mitad del arreglo.
   * @param last Índice de la última posición en el arreglo.
   */
  void merge(int* A, const int first, const int mid, const int last) const {
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

  // TODO(jm): doc
  void buildMaxHeap(int* Arr, const int arr_len, int& heap_size) const {
    heap_size = arr_len;
    for (int i = arr_len / 2; i >= 0; --i) {
      this->maxHeapify(Arr, i, heap_size);
    }
  }

  // TODO(jm): doc
  void maxHeapify(int* Arr, const int index, int& heap_size) const {
    int left = this->Left(index);
    int right = this->Right(index);
    int largest = index;

    if (left < heap_size && Arr[left] > Arr[index]) {
      largest = left;
    }
    if (right < heap_size && Arr[right] > Arr[largest]) {
      largest = right;
    }

    if (largest != index) {
      Ordenador::swap(Arr[index], Arr[largest]);
      maxHeapify(Arr, largest, heap_size);
    }
  }

  // TODO(jm): doc
  inline int Left(const int index) const { return index * 2; }

  // TODO(jm): doc
  inline int Right(const int index) const { return index * 2 + 1; }

  // TODO(jm): doc
  void quickSort(int* Arr, const int first, const int last) const {
    if (first < last) {
      const int pivot = this->partition(Arr, first, last);
      this->quickSort(Arr, first, pivot - 1);
      this->quickSort(Arr, pivot + 1, last);
    }
  }

  // TODO(jm): doc
  int partition(int* Arr, const int first, const int last) const {
    int pivot = Arr[last];
    int i = first - 1;
    for (int j = first; j < last; ++j) {
      if (Arr[j] <= pivot) {
        Ordenador::swap(Arr[++i], Arr[j]);
      }
    }
    Ordenador::swap(Arr[i + 1], Arr[last]);
    return i + 1;
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

  /**
   * @brief Implementación del Selection Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
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
        Ordenador::swap(A[min], A[i]);
      }
    }
  }

  /**
   * @brief Implementación del Insertion Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
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

  /**
   * @brief Implementación del Merge Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMezcla(int *A, int n) const {
    this->mergeSort(A, 0, n - 1);
  }

  // TODO(jm): doc
  void ordenamientoPorMonticulos(int *A, int n) const {
    int heap_size = 0;
    this->buildMaxHeap(A, n, heap_size);
    for (int i = n; i >= 1; --i) {
      Ordenador::swap(A[1], A[i]);
      --heap_size;
      this->maxHeapify(A, 1, heap_size);
    }
  }

  // TODO(jm): doc
  void ordenamientoRapido(int *A, int n) const {
    this->quickSort(A, 0, n - 1);
  }

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
    return "Carné: C35280, Nombre: José Manuel Mora Z, Tarea 1 Etapa 2";
  }
};
