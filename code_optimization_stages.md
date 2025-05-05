# Code Optimization Stages

## [ ] Élimination des sous-expressions communes

## [ ] Optimisation des boucles

## [ ] Élimination des variables ou instructions inutiles (b n'est pas utilisé dans le programme, donc on l'élimine)

## [ ] Élimination des variables d'induction 

Avant: 

```c
I = I + 1;
J = I + 6;
```

Après (si 'I' n'est pas utilisé dans le programme après) :

```c
J = (I+1) + 6;
```

