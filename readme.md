**Projet IN104 - Classifieur de sons**

L'objectif est de prédire le genre d'un son à partir d'une base de données, le dossier "genres".
Il s'agit de réduire l'information du son par STFT (Short Time Fourier Transform) et de la réduire par moyenne et écart-type. Un classifieur Python s'appuyant sur la bibliothèque sklearn en extrait une prédiction (calcul matriciel W*_ +b) et visualise la matrice de confusion.

Descriptif C :
- wave.c : Son donné -> Extrait les features du son donné.
- stft.c : Features, paramètres de fenètre, tableau magnitude vide -> Calcul la Short Time Fourier Transform, c'est-à-dire remplit le tableau magnitude de taille nRow x nCol.
- magnitude.c : Son donné, &nRow, &nCol -> Concaténation et simplification de wave.c et stft.c, notamment des features ignorées dans wave.c. Renvoie magnitude, et donne sa taille.
- utils.c : magnitude -> Calcul moyenne et écart-type.
- boucle_music.c : _ -> Opère une boucle sur les 100 musiques des 10 genres.
- main.c : fichier.csv -> Via le squelette de boucle_music.c appliqué à magnitude.c et utils.c, remplit le fichier csv avec les moyennes et écart-type pour chaque musique. Puisque nous réduisons sur les colonnes, le fichier possède 514+1 colonnes.
- prediction.c -> Son donné -> A l'aide de W et b, opère un produit matriciel pour déterminer le genre du son donné.

Classifieur Python :
- classifieur.py : fichier.csv -> Calcul la précision du modèle notée "score", ainsi que W et b en vue de la prédiction. Faire intervenir la normalisation de Batch permet d'améliorer le score. Une seconde partie du code est dédié à l'affichage de la matrice de confusion, qui doit idéalement être diagonale.
