Liste des types de multimedia:
==============================

* Base( nom:string, date_de_creation:time_t, path:string )
* Photo( [ ceux de Base ], lieu:string )
* Video( [ ceux de Base ], duree:int )
* Film( [ ceux de Video ], nombre_de_chaiptres:int, duree_des_chaiptres:int[] ) 


7e étape
========

Ceux qui ont besoin de leurs propres destructeurs sont ceux avec des
pointeurs comme variables. Ca veut dire aussi des tableaux, donc Film.