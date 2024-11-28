#include <iostream>
#include <cstdlib>  // Per rand() e srand()
#include <ctime>    // Per time() e clock()
#include <algorithm> // Per std::swap e std::copy
#include <vector>    // Per Bucket Sort
using namespace std;

// Prototipi degli algoritmi
void bubbleSort(int arr[], int n);
void insertionSort(int arr[], int n);
void quickSort(int arr[], int low, int high);
int partition(int arr[], int low, int high);
int randomizedPartition(int arr[], int low, int high);
void randomizedQuickSort(int arr[], int low, int high);
void mergeSort(int arr[], int l, int r);
void merge(int arr[], int l, int m, int r);
void heapSort(int arr[], int n);
void heapify(int arr[], int n, int i);
void bucketSort(float arr[], int n);
void countingSort(int arr[], int n);
void radixSort(int arr[], int n);

// Funzioni utilitarie
void generaArrayCasuale(int arr[], int n, int minVal, int maxVal);
void stampaArray(int arr[], int n);

// Funzione principale con menù
int main() {
    srand(time(0)); // Inizializza il generatore di numeri casuali

    int n, sceltaClasse, sceltaAlgoritmo;
    cout << "Benvenuto! Inserisci la dimensione dell'array: ";
    cin >> n;

    int minVal, maxVal;
    cout << "Inserisci il valore minimo e massimo per i numeri casuali (es. 1 100): ";
    cin >> minVal >> maxVal;

    int* arr = new int[n]; // Array dinamico per supportare dimensioni variabili
    generaArrayCasuale(arr, n, minVal, maxVal);

    cout << "\nArray generato: ";
    stampaArray(arr, n);

    do {
        cout << "\nScegli la classe di algoritmi:\n";
        cout << "1. Algoritmi Polinomiali\n";
        cout << "2. Algoritmi Logaritmici\n";
        cout << "3. Algoritmi Lineari\n";
        cout << "0. Esci\n";
        cout << "Scelta: ";
        cin >> sceltaClasse;

        if (sceltaClasse == 0) break;

        int* copiaArr = new int[n];
        copy(arr, arr + n, copiaArr);

        switch (sceltaClasse) {
            case 1: // Algoritmi Polinomiali
                cout << "\nScegli l'algoritmo polinomiale:\n";
                cout << "1. Bubble Sort\n";
                cout << "2. Insertion Sort\n";
                cout << "Scelta: ";
                cin >> sceltaAlgoritmo;

                if (sceltaAlgoritmo == 1) {
                    clock_t start = clock(); // Tempo iniziale
                    bubbleSort(copiaArr, n);
                    clock_t end = clock();   // Tempo finale
                    double duration = double(end - start) / CLOCKS_PER_SEC; // Calcola la durata in secondi
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n"; // Converti in millisecondi
                } else if (sceltaAlgoritmo == 2) {
                    clock_t start = clock();
                    insertionSort(copiaArr, n);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else {
                    cout << "Scelta non valida.\n";
                }
                break;

            case 2: // Algoritmi Logaritmici
                cout << "\nScegli l'algoritmo logaritmico:\n";
                cout << "1. Quick Sort\n";
                cout << "2. Randomized Quick Sort\n";
                cout << "3. Merge Sort\n";
                cout << "4. Heap Sort\n";
                cout << "Scelta: ";
                cin >> sceltaAlgoritmo;

                if (sceltaAlgoritmo == 1) {
                    clock_t start = clock();
                    quickSort(copiaArr, 0, n - 1);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else if (sceltaAlgoritmo == 2) {
                    clock_t start = clock();
                    randomizedQuickSort(copiaArr, 0, n - 1);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else if (sceltaAlgoritmo == 3) {
                    clock_t start = clock();
                    mergeSort(copiaArr, 0, n - 1);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else if (sceltaAlgoritmo == 4) {
                    clock_t start = clock();
                    heapSort(copiaArr, n);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else {
                    cout << "Scelta non valida.\n";
                }
                break;

            case 3: // Algoritmi Lineari
                cout << "\nScegli l'algoritmo lineare:\n";
                cout << "1. Bucket Sort\n";
                cout << "2. Counting Sort\n";
                cout << "3. Radix Sort\n";
                cout << "Scelta: ";
                cin >> sceltaAlgoritmo;

                if (sceltaAlgoritmo == 1) {
                    float* floatArr = new float[n];
                    for (int i = 0; i < n; i++) floatArr[i] = copiaArr[i] / float(maxVal);
                    clock_t start = clock();
                    bucketSort(floatArr, n);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                    delete[] floatArr;
                } else if (sceltaAlgoritmo == 2) {
                    clock_t start = clock();
                    countingSort(copiaArr, n);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else if (sceltaAlgoritmo == 3) {
                    clock_t start = clock();
                    radixSort(copiaArr, n);
                    clock_t end = clock();
                    double duration = double(end - start) / CLOCKS_PER_SEC;
                    cout << "Tempo impiegato: " << duration * 1000 << " ms\n";
                } else {
                    cout << "Scelta non valida.\n";
                }
                break;

            default:
                cout << "Scelta non valida. Riprova.\n";
                break;
        }

        cout << "\nArray ordinato: ";
        stampaArray(copiaArr, n);

        delete[] copiaArr; // Libera memoria dinamica
    } while (sceltaClasse != 0);

    delete[] arr; // Libera memoria dinamica
    cout << "Uscita dal programma. Grazie e buon lavoro!\n";
    return 0;
}

// Implementazioni degli algoritmi
void bubbleSort(int arr[], int n) {
    for (int i = 0; i < n - 1; i++) {
        bool scambio = false;
        for (int j = 0; j < n - i - 1; j++) {
            if (arr[j] > arr[j + 1]) {
                swap(arr[j], arr[j + 1]);
                scambio = true;
            }
        }
        if (!scambio) break;
    }
}

void insertionSort(int arr[], int n) {
    for (int i = 1; i < n; i++) {
        int chiave = arr[i];
        int j = i - 1;
        while (j >= 0 && arr[j] > chiave) {
            arr[j + 1] = arr[j];
            j--;
        }
        arr[j + 1] = chiave;
    }
}

int partition(int arr[], int low, int high) {
    int pivot = arr[high];
    int i = low - 1;
    for (int j = low; j < high; j++) {
        if (arr[j] <= pivot) {
            i++;
            swap(arr[i], arr[j]);
        }
    }
    swap(arr[i + 1], arr[high]);
    return i + 1;
}

void quickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = partition(arr, low, high);
        quickSort(arr, low, pi - 1);
        quickSort(arr, pi + 1, high);
    }
}

int randomizedPartition(int arr[], int low, int high) {
    int pivotIndex = low + rand() % (high - low + 1);
    swap(arr[pivotIndex], arr[high]);
    return partition(arr, low, high);
}

void randomizedQuickSort(int arr[], int low, int high) {
    if (low < high) {
        int pi = randomizedPartition(arr, low, high);
        randomizedQuickSort(arr, low, pi - 1);
        randomizedQuickSort(arr, pi + 1, high);
    }
}

void merge(int arr[], int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    int L[n1], R[n2];
    for (int i = 0; i < n1; i++) L[i] = arr[l + i];
    for (int i = 0; i < n2; i++) R[i] = arr[m + 1 + i];
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) arr[k++] = (L[i] <= R[j]) ? L[i++] : R[j++];
    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];
}

void mergeSort(int arr[], int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSort(arr, l, m);
        mergeSort(arr, m + 1, r);
        merge(arr, l, m, r);
    }
}

void heapify(int arr[], int n, int i) {
    int largest = i, left = 2 * i + 1, right = 2 * i + 2;
    if (left < n && arr[left] > arr[largest]) largest = left;
    if (right < n && arr[right] > arr[largest]) largest = right;
    if (largest != i) {
        swap(arr[i], arr[largest]);
        heapify(arr, n, largest);
    }
}

void heapSort(int arr[], int n) {
    for (int i = n / 2 - 1; i >= 0; i--) heapify(arr, n, i);
    for (int i = n - 1; i > 0; i--) {
        swap(arr[0], arr[i]);
        heapify(arr, i, 0);
    }
}

void bucketSort(float arr[], int n) {
    vector<float> buckets[n];
    for (int i = 0; i < n; i++) buckets[int(n * arr[i])].push_back(arr[i]);
    for (int i = 0; i < n; i++) sort(buckets[i].begin(), buckets[i].end());
    int index = 0;
    for (int i = 0; i < n; i++) for (float x : buckets[i]) arr[index++] = x;
}

void countingSort(int arr[], int n) {
    int maxElem = *max_element(arr, arr + n);
    int minElem = *min_element(arr, arr + n);
    int range = maxElem - minElem + 1;
    vector<int> count(range, 0), output(n);
    for (int i = 0; i < n; i++) count[arr[i] - minElem]++;
    for (int i = 1; i < range; i++) count[i] += count[i - 1];
    for (int i = n - 1; i >= 0; i--) output[--count[arr[i] - minElem]] = arr[i];
    for (int i = 0; i < n; i++) arr[i] = output[i];
}

void radixSort(int arr[], int n) {
    int maxElem = *max_element(arr, arr + n);
    for (int exp = 1; maxElem / exp > 0; exp *= 10) {
        vector<int> count(10, 0), output(n);
        for (int i = 0; i < n; i++) count[(arr[i] / exp) % 10]++;
        for (int i = 1; i < 10; i++) count[i] += count[i - 1];
        for (int i = n - 1; i >= 0; i--) output[--count[(arr[i] / exp) % 10]] = arr[i];
        for (int i = 0; i < n; i++) arr[i] = output[i];
    }
}

void generaArrayCasuale(int arr[], int n, int minVal, int maxVal) {
    for (int i = 0; i < n; i++) arr[i] = minVal + rand() % (maxVal - minVal + 1);
}

void stampaArray(int arr[], int n) {
    for (int i = 0; i < n; i++) cout << arr[i] << " ";
    cout << endl;
}