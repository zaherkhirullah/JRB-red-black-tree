/*********************************
**********************************
 Zaher Khirullah
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
