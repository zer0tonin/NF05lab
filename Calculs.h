#ifndef CALCULS_h
#define CALCULS_h

#include "Matrice.h"

Matrice operator+(const Matrice &M1, const Matrice &M2)
Matrice operator-(const Matrice &M1, const Matrice &M2)
Matrice operator*(const Matrice &M1, const Matrice &M2)
Matrice operator/(const Matrice &M1, const Matrice &M2)
Matrice operator*(const Matrice &M1, float Scalaire)
Matrice operator*(float Scalaire, const Matrice &M1)
Matrice operator/(const Matrice &M1, float Scalaire)
float ProduitScalaire(Matrice M1, Matrice M2)

#endif