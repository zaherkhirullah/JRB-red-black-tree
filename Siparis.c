#include <stdio.h>
#include "Siparis.h"

Siparis SNULL;

Siparis new_Siparis(char * inputed[])
{
    Siparis sip;
    sip.key    = inputed[1]; 
    sip.isim   = inputed[2]; 
    sip.malzeme= inputed[3]; 
    sip.renk   = inputed[4];
    return sip;
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



