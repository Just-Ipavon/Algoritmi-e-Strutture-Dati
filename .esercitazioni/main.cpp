#include <stdio.h>
#include <stdlib.h>
#include <vector>
#include <iostream>

using namespace std;

void insertionSort(int a[], int n){
    for(int i=1; i<n;i++){
        int chiave = a[i];
        int j= i-1;
        while(j>=0 && a[j]>chiave){
            a[j+1] = a[j];
            j--;
        }
        a[j+1] = chiave;
    }
}

int part(int a[], int inizio, int fine){
    int pivot = a[fine];
    int i = inizio-1;
    for(int j=inizio; j<fine; j++){
        if (a[j]<= pivot){
            i++;
            swap(a[i], a[j]);
        }
    }
    swap(a[i+1], a[fine]);
    return i+1;
}

void quickSort(int a[], int inizio, int fine){
    if(inizio < fine){
        int pivot = part(a, inizio, fine);
        quickSort(a, inizio, pivot-1);
        quickSort(a, pivot+1, fine);
    }
}

void merge(int a[], int sinistra, int centro, int destra){
    int n1 = centro - sinistra +1;
    int n2 = destra - centro;
    int L[n1], R[n2];
    for(int i=0; i<n1; i++){
        L[i] = a[sinistra+i];
    }
    for(int j=0; j<n2; j++){
        R[j] = a[centro+1+j];
    }
    int i=0, j=0, k=sinistra;
    while (i<n1 && j<n2){
        if(L[i] <= R[j]){
            a[k] = L[i];
            i++;
        }else{
            a[k] = R[j];
            j++;
        }
        k++;
    }
    while(i<n1){
        a[k] = L[i];
        i++;
        k++;
    }
    while(j<n2){
        a[k] = R[j];
        j++;
        k++;
    }
}

void mergeSort(int a[], int sinistra, int destra){
    if(sinistra < destra){
        int centro = sinistra + (destra-sinistra)/2;
        mergeSort(a, sinistra, centro);
        mergeSort(a, centro+1, destra);
        merge(a, sinistra, centro, destra);
    }
}






int main() {

    return 0;
}