### Greedy Activity Selector

Il problema del **Greedy Activity Selector** consiste nel selezionare il maggior numero di attività compatibili, dato un insieme di attività con orari di inizio e fine. Due attività sono compatibili se non si sovrappongono.

---

### **Descrizione del Problema**

- **Input**:  
  Un insieme di \( n \) attività, ognuna definita da un orario di inizio \( s[i] \) e un orario di fine \( f[i] \), dove \( s[i] < f[i] \).  
- **Output**:  
  Il massimo numero di attività compatibili che possono essere selezionate senza sovrapposizioni.  

---

### **Proprietà Greedy**

1. **Greedy Choice**:  
   Selezionare l'attività con l'orario di fine più piccolo che sia compatibile con le attività già selezionate. Questo riduce il tempo rimanente e lascia spazio per il massimo numero di attività successive.

2. **Sottostruttura ottima**:  
   Dopo aver selezionato un'attività, il problema rimanente è un sottoinsieme dello stesso problema, rendendo possibile l'applicazione ricorsiva dell'approccio greedy.

---

### **Algoritmo**

1. Ordinare le attività in ordine crescente di tempo di fine \( f[i] \).
2. Selezionare la prima attività \( A_1 \) (ha il tempo di fine più piccolo).
3. Iterare attraverso le attività rimanenti:
   - Aggiungere un'attività \( A_i \) all'insieme selezionato solo se il suo tempo di inizio \( s[i] \) è maggiore o uguale al tempo di fine dell'ultima attività selezionata.

---

### **Pseudocodice**

```cpp
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// Struttura per rappresentare un'attività
struct Activity {
    int start;
    int finish;
};

// Funzione per selezionare il massimo numero di attività compatibili
vector<Activity> activitySelector(vector<Activity>& activities) {
    // Ordinare le attività in base al tempo di fine
    sort(activities.begin(), activities.end(), [](const Activity& a, const Activity& b) {
        return a.finish < b.finish;
    });

    vector<Activity> selectedActivities;

    // Selezionare la prima attività
    selectedActivities.push_back(activities[0]);
    int lastFinishTime = activities[0].finish;

    // Iterare attraverso le altre attività
    for (size_t i = 1; i < activities.size(); i++) {
        if (activities[i].start >= lastFinishTime) {
            selectedActivities.push_back(activities[i]);
            lastFinishTime = activities[i].finish;
        }
    }

    return selectedActivities;
}

int main() {
    // Esempio di input
    vector<Activity> activities = {
        {1, 4}, {3, 5}, {0, 6}, {5, 7}, {3, 8}, {5, 9}, {6, 10}, {8, 11}, {8, 12}, {2, 13}, {12, 14}
    };

    // Calcolare le attività selezionate
    vector<Activity> selectedActivities = activitySelector(activities);

    // Stampare le attività selezionate
    cout << "Attività selezionate:" << endl;
    for (const auto& activity : selectedActivities) {
        cout << "(" << activity.start << ", " << activity.finish << ")" << endl;
    }

    return 0;
}
```

---

### **Spiegazione**

1. **Ordinamento**:  
   Le attività sono ordinate in base al tempo di fine per applicare il greedy choice.  
   Esempio: se abbiamo \( [(1, 4), (3, 5), (0, 6)] \), l'ordine diventa \( [(1, 4), (3, 5), (0, 6)] \).

2. **Iterazione**:  
   Dopo aver selezionato l'attività \( A_1 \), ogni attività successiva è verificata per compatibilità (cioè, il suo tempo di inizio deve essere maggiore o uguale al tempo di fine dell'ultima attività selezionata).

3. **Output**:  
   Il risultato è l'insieme delle attività selezionate che massimizzano il numero di attività compatibili.

---

### **Esempio**

#### Input:
`Attività con (s[i], f[i]):  
(1, 4), (3, 5), (0, 6), (5, 7), (3, 8), (5, 9), (6, 10), (8, 11), (8, 12), (2, 13), (12, 14)`

#### Output:

`Attività selezionate:  
(1, 4), (5, 7), (8, 11), (12, 14)`
---

### **Complessità**

- **Tempo**:  
  \( O(n \log n) \) per ordinare le attività in base al tempo di fine, dove \( n \) è il numero di attività.  
  \( O(n) \) per iterare attraverso le attività.

- **Spazio**:  
  \( O(n) \) per memorizzare le attività selezionate.  

