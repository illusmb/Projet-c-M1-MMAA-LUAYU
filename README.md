# Projet-c-M1-MMAA-LUAYU
Projet c++ M1 MMAA : Détection de droites et de courbes dans une image
 Prototype Python pour la détection de lignes - Méthode Naïve

Ce dossier contient un prototype en Python pour la détection de lignes dans une image en utilisant la transformée de Hough. Cette approche naïve est une première étape dans le développement d'un algorithme plus robuste et efficace pour le projet 
## Description du Projet

Le projet vise à détecter des segments et des droites dans des images en temps réel en utilisant la transformée de Hough. L'approche naïve ici présente se concentre sur la détection de droites définies par l'équation y = mx + b.

## Fichier `hough_naive.py`

Le script `hough_naive.py` contient l'implémentation de la transformée de Hough pour la détection de lignes dans une image en utilisant une approche naïve. Le script comprend des fonctions pour :
- Charger une image au format PPM.
- Appliquer la transformée de Hough en utilisant une grille discrète pour les paramètres m et b.
- Identifier les maxima dans l'espace de Hough qui correspondent aux droites les plus prononcées dans l'image.
- Dessiner les droites détectées sur l'image originale.


Le script affichera l'image originale, l'espace de Hough, et l'image avec les droites détectées.

## Tests

Des tests simples ont été effectués pour vérifier la capacité du script à détecter des droites dans des images simples et complexes. Les résultats sont encourageants pour des images avec des contrastes marqués, mais des améliorations sont nécessaires pour des images plus réalistes.

## Conclusion

Ce prototype est une étape initiale vers le développement d'un outil plus sophistiqué pour la détection de formes géométriques dans les images. Des améliorations sur la précision et l'efficacité sont prévues dans les prochaines phases du projet.

