/*********************************
*  __ --Grup Üyeleri--__ 
**********************************
1_ Zaher Khirullah(B151210568)
2_ Eyad Almansour (B141210127)
3_ Mohammad Almahamid (B141210263)
4_ Mumin Othman (G151210563)
5_ Abdulrahamn hamidi (G151210551)
*********************************/
#include "siparis.h"

Siparis SNULL;

Siparis new_Siparis(char * inputed[])
{
    Siparis *sip;
    sip->key    = atoi(inputed[1]); 
    sip->isim   = inputed[2]; 
    sip->malzeme= inputed[3]; 
    sip->renk   = inputed[4];
    return *sip;
}

int Siparis_key(Siparis sip) 
{
  return sip.key;
}

char *Siparis_isim(Siparis sip) {
  return sip.isim;
}

char *Siparis_malzeme(Siparis sip) {
  return sip.malzeme;
}

char *Siparis_renk(Siparis sip) {
  return sip.renk;
}



