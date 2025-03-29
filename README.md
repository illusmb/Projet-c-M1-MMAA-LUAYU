# Projet-c-M1-MMAA-LUAYU
Projet c++ M1 MMAA : Détection de droites et de courbes dans une image

# Naive Hough Transform (Méthode naïve en C++)

Ce projet implémente la méthode naïve de la transformée de Hough pour détecter les lignes dans des images PPM (format P3) en C++, inspirée du prototype Python.

## Fonctionnalités
- Chargement d'images PPM (format P3)
- Conversion en niveaux de gris
- Détection de lignes par accumulation `y = mx + b`
- Affichage console des lignes détectées
- Tracé des lignes sur l'image (pixels blancs)

## Structure
- `include/hough.hpp` : déclaration de la classe `Hough`
- `src/hough_naive.cpp` : logique de traitement (chargement, Hough, tracé)
- `src/main.cpp` : exécutable
- `images/` : dossier contenant les images `.ppm`

### Exemple : imageAvecDeuxSegments

```
Entrée  : deux segments diagonaux
Sortie  : lignes blanches superposées à l’image
Console :
  Ligne détectée : y = 1.00x + 1
  Ligne détectée : y = -1.00x + 19
  ...
```

## Améliorations futures
- [ ] Version polaire `(ρ, θ)`