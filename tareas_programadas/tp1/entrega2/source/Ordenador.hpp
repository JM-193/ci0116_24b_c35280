// Copyright 2024 Jose Manuel Mora Z
#pragma once

class Ordenador {
 private:
  /* Defina aquí los métodos auxiliares de los
      algoritmos de ordenamiento solamente. */
  // Puede definir cuantos métodos quiera.

  /**
   * @brief Valida si un arreglo es válido.
   *
   * @param A Arreglo a validar.
   * @param n Tamaño del arreglo.
   * @return true Si el arreglo es válido.
   * @return false Si el arreglo no es válido.
   */
  bool validateArray(int* A, const int n) const {
    if (A != nullptr && n > 0) {
      return true;
    } else {
      std::cerr << "El arreglo no es válido." << std::endl;
      return false;
    }
  }

  /**
   * @brief Intercambia los valores de dos variables enteras.
   *
   * @param a Primera variable.
   * @param b Segunda variable.
   */
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

  /**
   * @brief Crea el Montículo Máximo a partir de un arreglo.
   *
   * @param Arr Arreglo a ordenar.
   * @param arr_len Tamaño del arreglo.
   * @param heap_size Tamaño del heap.
   */
  void buildMaxHeap(int* Arr, const int arr_len, int& heap_size) const {
    // Actualizar el tamaño del heap.
    heap_size = arr_len;
    // Construir el heap máximo.
    for (int i = arr_len / 2 - 1; i >= 0; --i) {
      this->maxHeapify(Arr, i, heap_size);
    }
  }

  /**
   * @brief Reordena el sub-montículo para mantener la propiedad
   * de Montículo Máximo.
   *
   * @param Arr Arreglo a ordenar.
   * @param index Índice del nodo raíz del sub-árbol.
   * @param heap_size Tamaño del heap.
   */
  void maxHeapify(int* Arr, const int index, int& heap_size) const {
    // Obtener los índices de los hijos.
    int left = this->Left(index);
    int right = this->Right(index);
    // Valor más grande entre el nodo y sus hijos.
    int largest = index;

    // Revisar si el hijo izquierdo o derecho es más grande.
    if (left < heap_size && Arr[left] > Arr[index]) {
      largest = left;
    }
    if (right < heap_size && Arr[right] > Arr[largest]) {
      largest = right;
    }

    // Si el nodo no es el más grande, intercambiarlo con el más grande.
    if (largest != index) {
      Ordenador::swap(Arr[index], Arr[largest]);
      // Llamar recursivamente a maxHeapify para el sub-árbol.
      maxHeapify(Arr, largest, heap_size);
    }
  }

  /**
   * @brief Retorna el índice del hijo izquierdo de un nodo.
   *
   * @param index Índice del nodo.
   * @return int Índice del hijo izquierdo.
   */
  inline int Left(const int index) const { return (index * 2) + 1; }

  /**
   * @brief Retorna el índice del hijo derecho de un nodo.
   *
   * @param index Índice del nodo.
   * @return int Índice del hijo derecho.
   */
  inline int Right(const int index) const { return (index * 2 + 1) + 1; }

  /**
   * @brief Sección recursiva del quickSort.
   *
   * @param Arr Arreglo a ordenar.
   * @param first Primer índice del arreglo.
   * @param last Último índice del arreglo.
   */
  void quickSort(int* Arr, const int first, const int last) const {
    // Revisar si el arreglo solo tiene un elemento o está vacío.
    if (first < last) {
      // Particionar el arreglo.
      const int pivot = this->partition(Arr, first, last);
      // Ordenar las dos mitades recursivamente.
      this->quickSort(Arr, first, pivot - 1);
      this->quickSort(Arr, pivot + 1, last);
    }
  }

  /**
   * @brief Particiona el arreglo en relación a un pivote.
   *
   * @param Arr Arreglo a ordenar.
   * @param first Primer índice del arreglo.
   * @param last Último índice del arreglo.
   * @return int Índice del pivote.
   */
  int partition(int* Arr, const int first, const int last) const {
    // Tomar el último elemento como pivote.
    int pivot = Arr[last];
    // Índice para los elementos menores que el pivote.
    int i = first - 1;
    // Ordenar los elementos en relación al pivote.
    for (int j = first; j < last; ++j) {
      // Si el elemento es menor o igual al pivote, intercambiarlo y aumentar i.
      if (Arr[j] <= pivot) {
        Ordenador::swap(Arr[++i], Arr[j]);
      }
    }
    // Intercambiar el pivote con el elemento en i + 1.
    Ordenador::swap(Arr[i + 1], Arr[last]);
    // Retornar la posición del pivote.
    return i + 1;
  }

  /**
   * @brief Encuentra el valor máximo en un arreglo.
   *
   * @param Arr Arreglo a revisar.
   * @param n Tamaño del arreglo.
   * @return int Valor máximo en el arreglo.
   */
  int getMax(int* Arr, const int n) const {
    // Valor máximo en el arreglo (k).
    int max = Arr[0];
    // Encontrar el máximo.
    for (int i = 1; i < n; ++i) {
      if (Arr[i] > max) {
        max = Arr[i];
      }
    }
    return max;
  }

  /**
   * @brief Implementación del Counting Sort.
   *
   * @param Arr Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   * @param digits Dígitos a considerar.
   */
  void countingSort(int* Arr, const int n, const int digits) const {
    // Arreglo "B", donde se guardará el resultado.
    int output[n];
    // Arreglo auxiliar "C".
    int count[10] = {0};

    for (int i = 0; i < n; ++i) {
      // Contar las apariciones de cada "dígito".
      count[getDigit(Arr, i, digits)]++;
    }

    for (int i = 1; i < 10; ++i) {
      // Sumar las apariciones de los dígitos anteriores.
      // Esto indica la posición de cada dígito en el arreglo ordenado.
      count[i] += count[i - 1];
    }

    // Recorrer el arreglo en orden inverso,
    // para conservar el orden de los elementos.
    for (int i = n - 1; i >= 0; --i) {
      // Agregar los elementos a "B" en la posición indicada por "C".
      output[count[getDigit(Arr, i, digits)] - 1] = Arr[i];
      // Disminuir la posición del siguiente elemento del mismo dígito.
      count[getDigit(Arr, i, digits)]--;
    }

    for (int i = 0; i < n; ++i) {
      // Copiar los elementos ordenados al arreglo original.
      Arr[i] = output[i];
    }
  }

  /**
   * @brief Sección principal del Radix Sort.
   *
   * @param Arr Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void radixSort(int* Arr, const int n) const {
    // Encontrar el valor máximo en el arreglo (k).
    int max = this->getMax(Arr, n);

    // Ordenar los elementos por dígito.
    for (int digits = 1; max / digits > 0; digits *= 10) {
      this->countingSort(Arr, n, digits);
    }
  }

  /**
   * @brief Obtiene el dígito de un número en una posición específica.
   *
   * @param Arr Arreglo a revisar.
   * @param i Índice del elemento en el arreglo.
   * @param digits Dígitos a considerar.
   * @return int Dígito en la posición indicada.
   */
  int getDigit(int *Arr, int i, const int digits) const {
    return (Arr[i] / digits) % 10;
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
    if (!this->validateArray(A, n)) { return; }

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
    if (!this->validateArray(A, n)) { return; }

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
    if (!this->validateArray(A, n)) { return; }

    this->mergeSort(A, 0, n - 1);
  }

  /**
   * @brief Implementación del Heap Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorMonticulos(int *A, int n) const {
    if (!this->validateArray(A, n)) { return; }

    int heap_size = n;
    this->buildMaxHeap(A, n, heap_size);
    for (int i = n - 1; i >= 0; --i) {
      Ordenador::swap(A[0], A[i]);
      --heap_size;
      this->maxHeapify(A, 0, heap_size);
    }
  }

  /**
   * @brief Implementación del Quick Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoRapido(int *A, int n) const {
    if (!this->validateArray(A, n)) { return; }

    this->quickSort(A, 0, n - 1);
  }

  /**
   * @brief Implementación del Radix Sort.
   *
   * @param A Arreglo a ordenar.
   * @param n Tamaño del arreglo.
   */
  void ordenamientoPorRadix(int *A, int n) const {
    if (!this->validateArray(A, n)) { return; }

    this->radixSort(A, n);
  }

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
