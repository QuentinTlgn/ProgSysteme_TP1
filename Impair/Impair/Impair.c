/******************************************************
Name    : Impair.C
Role    : Composant du TP1 du cours de Programmation Système
Author  : TAULEIGNE Quentin
Org.    : 3iL Ingénieurs Rodez promotion 22
Date    : 30/05/2024
*******************************************************/

#include <stdio.h>

void main() {
    int nombre = 100;
    int i;

    for (i = 1; i <= 100; i += 2) {
        printf("%d\n", i);
    }
}