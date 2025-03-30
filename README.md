#  Projet C++ M1 MMAA – Détection de droites dans une image par transformée de Hough

 # Objectifs

- Lire une image couleur au format `.ppm` (P3)
- Convertir l’image en niveaux de gris
- Détecter les **contours**
- Appliquer la **transformée de Hough en coordonnées polaires**
- Déterminer les droites les plus significatives
- **Supprimer les doublons** (droites trop proches)
- Tracer les droites sur l’image avec **l’algorithme de Bresenham**
- Sauvegarder :
  - L’image avec les droites détectées
  - L’espace de Hough visualisé sous forme d’image

---

## Organisation des branches

| Branche                | Description                                                   |
|------------------------|---------------------------------------------------------------|
| `main`                 |  Version stable finale (polaire + contours + Bresenham)     |
| `feature/polaire-cpp`  | Version complète avec toutes les fonctionnalités implémentées |
| `feature/naive-cpp`    | Méthode naïve basée sur y = mx + b                            |
| `proto/python-naive`   | Prototype initial en Python                                   |

---
Limitations et parties non réalisées

Détection de cercles ou ellipses
Détection par échantillonnage de points	apeut être envisagé comme méthode alternative
Contours par filtre Sobel/Canny	 (actuellement fait par seuillage simple


Ce projet démontre l’intérêt de la représentation polaire dans la détection de droites dans des images binaires.

La modularité du code permettrait à terme de :

-Gérer les cercles et ellipses

-Appliquer des techniques d’optimisation

-Ajouter une interface graphique

Le projet est organisé par branches pour suivre l’évolution de la méthode, depuis le prototype Python jusqu’à la version optimisée C++.
