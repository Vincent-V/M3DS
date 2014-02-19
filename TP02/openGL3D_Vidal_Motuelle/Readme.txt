Binome :
Vidal Vincent
Motuelle Romain

Avancement :

Le TP a été réalisé entièrement de la question 1 à la question 23.
La question bonus n'a pas été faite, nous n'y sommes pas parvenu.

Explications :

Q6. 
Nous avons dupliqué l'ensemble des sommets afin d'avoir des sommets à usage unique.
C'est important ca ici un même sommet doit avoir plusieurs couleurs.
Pour la superposition des triangles, le dernier ajouté se retrouve au dessus et est visible.

Q8.
  1. Les valeurs du dephBuffer sont comprises entre 0 et 1, donc si on l'initialise à 1
     et qu'on utilise la fonction Greater, qui n'affiche que si on est superieur
     rien ne sera affiché car il impossible qu'un point soit superieur à 1.
     
  2. Si on initialise à -1 (inferieur au minimum), alors la fonction Greater fonctionne et affiche les objets qui sont le plus loin.
  
  3. Ici les triangles les plus loins ont été coupés, en effet on peut voir les sommets à -10 mais pas celui à -20. En effet, les points avec un z inférieur à -11.1 sont invisibles.
