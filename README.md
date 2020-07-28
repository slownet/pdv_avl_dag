# PDV - IS DAG AVL?

Zkouskove zadani z 5. 6. 2020

### Jak se generuje orientovany acyklicky graf?
1. Vygeneruje se vektor prazdnych vrcholu. Pocet zalezi na cisle z dalsi sekce.
2. Spojime vrchol `i` nahodne s vrcholy s indexy z intervalu (i, vector.size()]

### Zmena velikosti grafu
Pro zmenu velikosti grafu zmente cislo v 1. radku funkce `generate_dag`.
Napriklad, pro 40000 prazdnych vrcholu se generuje graf velikosti zruba 1700 vrcholu.