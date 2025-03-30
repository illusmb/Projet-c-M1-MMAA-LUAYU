# Détecteur de droites par Transformée de Hough (M1 MMAA - C++)

## Branche : `feature/polaire-cpp`


Détecter les segments de droites présents dans une image avec :
- Une détection de contours intelligente
- Une transformée de Hough en (ρ, θ)
- Une suppression des droites dupliquées
- Un tracé net des droites avec l'algorithme de Bresenham

 La version polaire est plus générale, plus stable, et évite les problèmes avec les droites verticales.

Critère	Naïve |(y = mx + b)|	Polaire (ρ = x cos θ + y sin θ)
Représentation|	(m, b)	|    (rho, theta)
Problème avec droites verticales|	Oui|	Non
Précision	|Moyenne	|Haute
Espace de Hough|	Non uniforme	|Uniforme
Robustesse|	Limitée|	Forte

Le prototype initial était en Python et utilisait :l’équation y = mx + b, un seuillage fixe, un accumulateur simple,un tracé matplotlib

La version C++ reprend ces idées et les améliore : Passage à la représentation polaire,,meilleure couverture de l’espace de droites,suppression des doublons,tracé via l’algorithme de Bresenham avec épaisseur

exemple d'execution sur vs studio
./detecteur images/imageAvecDeuxSegments.ppm
./detecteur images/imageM1.ppm
