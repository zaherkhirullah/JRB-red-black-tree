/*********************************
*  __ --Grup Üyeleri--__ 
**********************************
1_ Zaher Khirullah(B151210568)
2_ Eyad Almansour (B141210127)
3_ Mohammad Almahamid (B141210263)
4_ Mumin Othman (G151210563)
5_ Abdulrahamn hamidi (G151210551)
*********************************/
#ifndef	_SIPARIS_H_
#define	_SIPARIS_H_

#include <stdio.h>
#include <stdlib.h>

typedef struct {
     int key;
     char * isim;
     char * malzeme;
     char * renk;
  } Siparis;  

extern Siparis new_Siparis(char **);
extern Siparis SNULL;
extern int Siparis_key(Siparis);
extern char *Siparis_isim(Siparis);
extern char *Siparis_malzeme(Siparis);
extern char *Siparis_renk(Siparis);

#endif
