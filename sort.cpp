#include <iostream>

void printArray(int array[], int arraySize);

void insertionSort(int array[], int arraySize);

void shellSortBad(int array[], int arraySize);

void shellSortGood(int array[], int arraySize);

void shellSortBad2(int array[], int arraySize);

int main() {
    int myarray[10] = {4, 7, 3, 2, 1, 8, 9, 6, 5, 10};
    int arraySize = 10;

    shellSortBad2(myarray, arraySize);

    printArray(myarray, arraySize);
    std::cout << std::endl;
}

void printArray(int array[], int arraySize) {
    for (int i = 0; i < arraySize; i++) {
        std::cout << array[i] << " ";
    }
}

void insertionSort(int array[], int arraySize) {
    for (int indexToSort = 1; indexToSort < arraySize; indexToSort++) {
        int numToSort = array[indexToSort];
        int j = indexToSort;
        while (j > 0 && (numToSort < array[j - 1])) {
            array[j] = array[j - 1];
            j--;
        }
        array[j] = numToSort;
    }
}

void shellSortBad(int array[], int arraySize) {
    for (int gap = arraySize/2; gap > 0; gap /= 2) {
        for (int i = gap; i < arraySize; i++) {
            int numToSort = array[i];
            int j = i;
            while ((j >= gap) && (numToSort < array[j - gap])) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = numToSort;
        }
    }
}

void shellSortGood(int array[], int arraySize) {
    for (int gap = 2^arraySize - 1; gap > 0; gap--) {
        for (int i = gap; i < arraySize; i++) {
            int numToSort = array[i];
            int j = i;
            while ((j >= gap) && (numToSort < array[j - gap])) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = numToSort;
        }
    }
}

void shellSortBad2(int array[], int arraySize) {
    for (int gap = arraySize / 2; gap > 0; gap /= 2) {
        for (int i = gap; i < arraySize; i++) {
            int numToSort = array[i];
            int j = i;
            while ((j >= gap) && numToSort < array[j - gap]) {
                array[j] = array[j - gap];
                j -= gap;
            }
            array[j] = numToSort;
        }
    }
}