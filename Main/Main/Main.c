/******************************************************
Name    : Main.C
Role    : Main du TP1 1du cours de Programmation Système
Author  : TAULEIGNE Quentin
Org.    : 3iL Ingénieurs Rodez promotion 22
Date    : 30/05/2024
*******************************************************/


#include <stdio.h>
#include <windows.h>

#define multithread

#ifdef multithread
int nombre = 500;

DWORD WINAPI pairThread(LPVOID lpParam) {
    for (int i = 2; i <= nombre; i += 2) {
        printf("Pair: %d\n", i);
    }
    return 0;
}

DWORD WINAPI impairThread(LPVOID lpParam) {
    for (int i = 1; i <= nombre; i += 2) {
        printf("Impair: %d\n", i);
    }
    return 0;
}
#endif

int main() {
#ifdef multiprocess
#include <windows.h>
#include <tchar.h>

    // Noms des programmes à exécuter
    LPCSTR applicationName1 = "U:\\C\\ProgSysteme_TP1\\Impair\\x64\\Release\\Impair.exe";
    LPCSTR applicationName2 = "U:\\C\\ProgSysteme_TP1\\Pair\\x64\\Release\\Pair.exe";

    // Structures pour spécifier les informations de démarrage des processus
    STARTUPINFOA startupInfo1, startupInfo2;
    PROCESS_INFORMATION processInfo1, processInfo2;

    // Initialiser les structures pour le premier processus
    ZeroMemory(&startupInfo1, sizeof(startupInfo1));
    startupInfo1.cb = sizeof(startupInfo1);
    ZeroMemory(&processInfo1, sizeof(processInfo1));

    // Initialiser les structures pour le deuxième processus
    ZeroMemory(&startupInfo2, sizeof(startupInfo2));
    startupInfo2.cb = sizeof(startupInfo2);
    ZeroMemory(&processInfo2, sizeof(processInfo2));

    // Créer le premier processus
    if (!CreateProcessA(
        applicationName1,   // Nom de l'application
        NULL,               // Ligne de commande
        NULL,               // Attributs de sécurité du processus
        NULL,               // Attributs de sécurité du thread
        FALSE,              // Héritage des handles
        0,                  // Flags de création
        NULL,               // Environnement
        NULL,               // Répertoire courant
        &startupInfo1,      // Structure STARTUPINFO
        &processInfo1       // Structure PROCESS_INFORMATION
    )) {
        // Si CreateProcess échoue, afficher un message d'erreur
        printf("CreateProcess1 failed (%d).\n", GetLastError());
        return 1;
    }

    // Créer le deuxième processus
    if (!CreateProcessA(
        applicationName2,   // Nom de l'application
        NULL,               // Ligne de commande
        NULL,               // Attributs de sécurité du processus
        NULL,               // Attributs de sécurité du thread
        FALSE,              // Héritage des handles
        0,                  // Flags de création
        NULL,               // Environnement
        NULL,               // Répertoire courant
        &startupInfo2,      // Structure STARTUPINFO
        &processInfo2       // Structure PROCESS_INFORMATION
    )) {
        // Si CreateProcess échoue, afficher un message d'erreur
        printf("CreateProcess2 failed (%d).\n", GetLastError());
        return 1;
    }

    // Tableau des handles des processus
    HANDLE processHandles[2] = { processInfo1.hProcess, processInfo2.hProcess };

    // Attendre la fin des deux processus
    DWORD waitResult = WaitForMultipleObjects(2, processHandles, TRUE, INFINITE);

    // Vérifier le résultat de l'attente
    if (waitResult == WAIT_FAILED) {
        printf("WaitForMultipleObjects failed (%d).\n", GetLastError());
        // Fermer les handles avant de retourner
        CloseHandle(processInfo1.hProcess);
        CloseHandle(processInfo1.hThread);
        CloseHandle(processInfo2.hProcess);
        CloseHandle(processInfo2.hThread);
        return 1;
    }

    // Fermer les handles des structures PROCESS_INFORMATION pour le premier processus
    CloseHandle(processInfo1.hProcess);
    CloseHandle(processInfo1.hThread);
    // Fermer les handles des structures PROCESS_INFORMATION pour le deuxième processus
    CloseHandle(processInfo2.hProcess);
    CloseHandle(processInfo2.hThread);

    printf("Both processes executed successfully.\n");

    return 0;
#endif // multiprocess


#ifdef multithread
    HANDLE hThreadPair, hThreadImpair;
    HANDLE hThreads[2];

    hThreadPair = CreateThread(NULL, 0, pairThread, NULL, 0, NULL);
    hThreadImpair = CreateThread(NULL, 0, impairThread, NULL, 0, NULL);

    if (hThreadPair == NULL || hThreadImpair == NULL) {
        printf("Erreur lors de la création du thread.\n");
        return 1;
    }

    hThreads[0] = hThreadPair;
    hThreads[1] = hThreadImpair;

    // Attendre la fin des deux threads
    DWORD dwWaitResult = WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    switch (dwWaitResult) {
        // Les threads ont terminé avec succès
    case WAIT_OBJECT_0:
    case WAIT_OBJECT_0 + 1:
        printf("Les threads ont terminé avec succès.\n");
        break;

        // En cas d'erreur
    default:
        printf("Erreur lors de l'attente des threads.\n");
        return 1;
    }

    // Fermer les handles des threads
    CloseHandle(hThreadPair);
    CloseHandle(hThreadImpair);

    return 0;
#endif // multithread

}