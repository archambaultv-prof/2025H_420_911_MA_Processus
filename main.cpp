#include <iostream>
#include <vector>
#include <windows.h>  // Pour SetConsoleOutputCP
#include <thread>
#include <mutex>
#include <chrono>

std::mutex mtx;  // Mutex pour synchroniser l'accès à cout

// Fonction qui sera exécutée par chaque thread
void processusParallele(int id, int duree) {
    {   // Premier bloc de synchronisation
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " démarre son exécution\n";
    }   // Le mutex est libéré ici
    
    // Simulation d'un travail
    std::this_thread::sleep_for(std::chrono::seconds(duree));
    
    {   // Deuxième bloc de synchronisation
        std::lock_guard<std::mutex> lock(mtx);
        std::cout << "Thread " << id << " termine son exécution après " << duree << " secondes\n";
    }
}

void demoThreads() {
    std::cout << "\n=== Démonstration des threads ===\n";
    
    // Création de plusieurs threads
    std::thread t1(processusParallele, 1, 2);  // Thread 1 s'exécute pendant 2 secondes
    std::thread t2(processusParallele, 2, 3);  // Thread 2 s'exécute pendant 3 secondes
    std::thread t3(processusParallele, 3, 1);  // Thread 3 s'exécute pendant 1 seconde

    // Attendre que tous les threads terminent
    t1.join();
    t2.join();
    t3.join();

    std::cout << "Tous les threads ont terminé leur exécution\n";
    std::cout << "================================\n";
}

void configurerConsole() {
    SetConsoleOutputCP(CP_UTF8);  // Configure la console pour UTF-8
}

void printAddress() {
    int stackVar = 42;  // Variable de pile
    int* heapVar = new int(100);  // Variable du tas
    
    std::cout << "\n=== Adresses mémoire actuelles ===\n";
    std::cout << "Adresse de la fonction main: " << reinterpret_cast<void*>(&printAddress) << "\n";
    std::cout << "Adresse de la variable de pile: " << &stackVar << "\n";
    std::cout << "Adresse du pointeur de la variable du tas: " << &heapVar << "\n";
    std::cout << "Adresse de la mémoire allouée dans le tas: " << heapVar << "\n";
    std::cout << "==================================\n";
    
    delete heapVar;  // Nettoyage de la mémoire du tas
}

void memory() {
    std::cout << "État initial de la mémoire:" << std::endl;
    printAddress();

    // Allocation d'objets dans le tas
    std::vector<int*> vector;
    std::cout << "\nAllocation de nouveaux objets dans le tas..." << std::endl;

    // Création de 3 allocations dans le tas
    for(int i = 0; i < 3; i++) {
        vector.push_back(new int(i * 100));
        std::cout << "\nAprès l'allocation " << (i + 1) << ":\n";
        std::cout << "Adresse du nouvel objet dans le tas: " << vector[i] << std::endl;
    }

    // Création de variables dans la pile
    std::cout << "\nCréation de variables dans la pile..." << std::endl;
    constexpr int varPile1 = 10;
    constexpr int varPile2 = 20;
    constexpr int varPile3 = 30;

    std::cout << "Adresses des variables de la pile:\n";
    std::cout << "varPile1: " << &varPile1 << std::endl;
    std::cout << "varPile2: " << &varPile2 << std::endl;
    std::cout << "varPile3: " << &varPile3 << std::endl;

    // Nettoyage de la mémoire du tas
    for(auto ptr : vector) {
        delete ptr;
    }
}

int main() {
    configurerConsole();  // Configure l'encodage de la console

    memory();
    
    // Démonstration de l'exécution parallèle avec des threads
    demoThreads();
    
    return 0;
}