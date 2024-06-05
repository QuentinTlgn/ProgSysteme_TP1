/******************************************************
Name    : Main.C
Role    : Main du TP1 du cours de Programmation Systeme
Author  : TAULEIGNE Quentin
Org.    : 3iL Ingenieurs Rodez promotion 22
Date    : 05/06/2024
*******************************************************/


#include <stdio.h>
#include <windows.h>

#define multithread
#define alternance

#ifdef multithread
int nombre = 500;

#ifdef alternance
volatile int tour = 0;
#endif // alternance


DWORD WINAPI pairThread(LPVOID lpParam) {
#ifdef alternance
    int p; p = 1;
#endif // alternance

    for (int i = 2; i <= nombre; i += 2) {
#ifdef alternance
        while (tour != p){};
#endif // alternance

        printf("Pair: %d\n", i);

#ifdef alternance
        tour = 0;
#endif // alternance
    }
    return 0;
}

DWORD WINAPI impairThread(LPVOID lpParam) {
#ifdef alternance
    int p; p = 0;
#endif // alternance

    for (int i = 1; i <= nombre; i += 2) {
#ifdef alternance
        while (tour != p){};
#endif // alternance
        printf("Impair: %d\n", i);
#ifdef alternance
        tour = 1;
#endif // alternance
    }
    return 0;
}
#endif // multithread

int main() {
#ifdef multiprocess
#include <windows.h>
#include <tchar.h>

    // Noms des programmes à executer
    LPCSTR applicationName1 = "U:\\C\\ProgSysteme_TP1\\Impair\\x64\\Release\\Impair.exe";
    LPCSTR applicationName2 = "U:\\C\\ProgSysteme_TP1\\Pair\\x64\\Release\\Pair.exe";

    // Structures pour specifier les informations de demarrage des processus
    STARTUPINFOA startupInfo1, startupInfo2;
    PROCESS_INFORMATION processInfo1, processInfo2;

    // Initialiser les structures pour le premier processus
    ZeroMemory(&startupInfo1, sizeof(startupInfo1));
    startupInfo1.cb = sizeof(startupInfo1);
    ZeroMemory(&processInfo1, sizeof(processInfo1));

    // Initialiser les structures pour le deuxieme processus
    ZeroMemory(&startupInfo2, sizeof(startupInfo2));
    startupInfo2.cb = sizeof(startupInfo2);
    ZeroMemory(&processInfo2, sizeof(processInfo2));

    // Creer le premier processus
    if (!CreateProcessA(
        applicationName1,   // Nom de l'application
        NULL,               // Ligne de commande
        NULL,               // Attributs de securite du processus
        NULL,               // Attributs de securite du thread
        FALSE,              // Heritage des handles
        0,                  // Flags de creation
        NULL,               // Environnement
        NULL,               // Repertoire courant
        &startupInfo1,      // Structure STARTUPINFO
        &processInfo1       // Structure PROCESS_INFORMATION
    )) {
        // Si CreateProcess echoue, afficher un message d'erreur
        printf("CreateProcess1 failed (%d).\n", GetLastError());
        return 1;
    }

    // Creer le deuxieme processus
    if (!CreateProcessA(
        applicationName2,   // Nom de l'application
        NULL,               // Ligne de commande
        NULL,               // Attributs de securite du processus
        NULL,               // Attributs de securite du thread
        FALSE,              // Heritage des handles
        0,                  // Flags de creation
        NULL,               // Environnement
        NULL,               // Repertoire courant
        &startupInfo2,      // Structure STARTUPINFO
        &processInfo2       // Structure PROCESS_INFORMATION
    )) {
        // Si CreateProcess echoue, afficher un message d'erreur
        printf("CreateProcess2 failed (%d).\n", GetLastError());
        return 1;
    }

    // Tableau des handles des processus
    HANDLE processHandles[2] = { processInfo1.hProcess, processInfo2.hProcess };

    // Attendre la fin des deux processus
    DWORD waitResult = WaitForMultipleObjects(2, processHandles, TRUE, INFINITE);

    // Verifier le resultat de l'attente
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
    // Fermer les handles des structures PROCESS_INFORMATION pour le deuxieme processus
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
        printf("Erreur lors de la creation du thread.\n");
        return 1;
    }

    hThreads[0] = hThreadPair;
    hThreads[1] = hThreadImpair;

    // Attendre la fin des deux threads
    DWORD dwWaitResult = WaitForMultipleObjects(2, hThreads, TRUE, INFINITE);

    switch (dwWaitResult) {
        // Les threads ont termine avec succes
    case WAIT_OBJECT_0:
    case WAIT_OBJECT_0 + 1:
        printf("Les threads ont termine avec succes.\n");
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