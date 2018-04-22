/*********************************
*  __ --Grup Üyeleri--__ 
**********************************
1_ Eyad Almansour (B141210127)
2_ Zaher Khirullah(B151210568)
3_ Mohammad Almahamid (B141210263)
4_ Mumin Othman (G151210563)
5_ Abdulrahamn hamidi (G151210551)
*********************************/
#include "prog.h"
#include "Siparis.h"
typedef struct {
  char *isim;
  int key;
  
} Person;

JRB b, bn,siparis_tree , b2;
IS myis; 
int i,  file_ptr, sz;

int error_message()
{
      printf("Error :No elemants in Tree \n");
      printf("please try \"add|-sipKey|sipAd|sipMalezeme|sipRenk\" to add items to Tree\n");
      return 0; 
}
/* "add" Komutu agaca siparişlari ekleme funksiyonu
 *******************************************/
int add_fun(char* inputed[])
{
  int cnt=0;
  if(inputed) // inputed biçimler sayisi hesaplama 
  {
      for (i = 1; *(inputed + i); i++)
      cnt++;
  }
  // biçim uygun bulmak için şartlar
  if(inputed[1]==NULL|| atoi(inputed[1]) < 0 ||inputed[5] || cnt!=4)
  {
    printf("“Biçim uygun değil.”\n");
    if(inputed[1]!=NULL && atoi(inputed[1]) == 0) //if  key it isn't number  (integer)
      printf("-sipKey must be number [integer].\n");
    printf("Usage: add|sipKey|sipAd|sipMalezeme|sipRenk\n");
    return 0;
  }

  IS is;
  Siparis *p;
  int nsize, i;

  is = new_inputstruct("input.txt");
  t = make_jrb();

  while (get_line(is) >= 0) {
    if (is->NF > 1) {

      /* Creating the Siparis is just like ni_sort1.c -- please see the comments
         there for how this is done. */

      p = malloc(sizeof(Siparis));
      p->key = atoi(is->fields[is->NF-1]);

      nsize = strlen(is->fields[0]);
      for (i = 1; i < is->NF-1; i++) nsize += (strlen(is->fields[i])+1);

      p->isim = (char *) malloc(sizeof(char)*(nsize+1));
      strcpy(p->isim, is->fields[0]);
      //  p->malzeme = (char *) malloc(sizeof(char)*(nsize+1));
      // strcpy(p->malzeme, is->fields[1]);
      //  p->renk = (char *) malloc(sizeof(char)*(nsize+1));
      // strcpy(p->renk, is->fields[2]);

      nsize = strlen(is->fields[0]);
      for (i = 1; i < is->NF-1; i++)
       {
        p->isim[nsize] = ' ';
        strcpy(p->isim+nsize+1, is->fields[i]);
        nsize += strlen(p->isim+nsize);
      }
      

      /* To insert the Siparis, we first test to see if the key is in the
         tree.  If it is not, we create it with an empty red-black tree as a val. 
         In either case, we insert the isim into the second-level tree. */

      tmp = jrb_find_int(b, p->key);
      if (tmp == NULL) {
        siparis_tree = make_jrb();
        jrb_insert_int(b, p->key, new_jval_v((void *) siparis_tree));
      } else {
        siparis_tree = (JRB) tmp->val.v;
      }
      jrb_insert_str(siparis_tree, p->isim, new_jval_v((void *) p));
      // jrb_insert_str(siparis_tree, p->malzeme, new_jval_v((void *) p));
      // jrb_insert_str(siparis_tree, p->renk, new_jval_v((void *) p));
    }
  }

  /* To print the people, we need to do a nested, two-level recursion */

  jrb_traverse(tmp, t) {
    siparis_tree = (JRB) tmp->val.v;
    jrb_traverse(t2, siparis_tree) {
      p = (Siparis *) t2->val.v;
      printf("%-40s %2d\n", p->isim, p->key);
    }
  }
// Person *p;
//   b = make_jrb();
//       // ... Read and create the person
//       p->key = atoi(inputed[1]);
//       p->isim = inputed[2];
//       jrb_insert_int(b, p->key, new_jval_v((void *) siparis_tree));
      
//       bn = jrb_find_int(b, p->key);
//       if (bn == NULL)
//       {
//         siparis_tree = make_jrb();
//       }
//       else
//       {
//         siparis_tree = (JRB) bn->val.v;
//       }
//       jrb_insert_str(siparis_tree, p->isim, new_jval_v((void *) p));
 



// // Siparis *p;
  // // if(b==NULL) b = make_jrb();  
  // // p->key = atoi(inputed[1]);
  // // p->isim = inputed[2];
  // // if(b!=NULL){
  // //     bn = jrb_find_int(b, p->key);
  // // }
  // //     if (bn == NULL) {
  // //       siparis_tree = make_jrb();
  // //       jrb_insert_int(b, p->key, new_jval_v((void *) siparis_tree));
  // //     }
  // //     else 
  // //     {
  // //       siparis_tree = (JRB) bn->val.v;
  // //     }
  // //     jrb_insert_str(siparis_tree, p->isim, new_jval_v((void *) p));
  // //           // while (get_line(is) >= 0) {
  // //           // if (is->NF > 1) {
  // //           //   ... Read and create the Siparis
  // //             /* To insert the Siparis, we first test to see if the key is in the
  // //             tree.  If it is not, we create it with an empty red-black tree as a val. 
  // //             In either case, we insert the isim into the second-level tree. */
  // //           // }

  // // /* To print the people, we need to do a nested, two-level recursion */
  // // jrb_traverse(bn, b) {
  // //   siparis_tree = (JRB) bn->val.v;
  // //   jrb_traverse(b2, siparis_tree) {
  // //     p = (Siparis *) b2->val.v;
  // //     printf("%-40s %2d\n", p->isim, p->key);
  // //   }
  // // }
  
  /* To print the people, we need to do a nested, two-level recursion */

  // jrb_traverse(bn, b) {
  //   siparis_tree = (JRB) bn->val.v;
  //   jrb_traverse(b2, siparis_tree) {
  //     p = (Person *) b2->val.v;
  //     printf("%-40s %2d\n", p->isim, p->key);
  //   }
  // }
    printf("The items was added to Tree .\n");  
    return 0 ;
}
    // Siparis *sip ;
    //   sip->key    = atoi(inputed[1]); 
    //   sip->isim   = inputed[2]; 
    //   sip->malzeme= inputed[3]; 
    //   sip->renk   = inputed[4];
    //   printf("%d\n",sip->key);

    // if (jrb_find_int(b, sip->key) == NULL) {
    //     (void) jrb_insert_int(b,sip->key , new_jval_v(NULL));// Siparis_key(*sip)
    //     //  jrb_insert_str(b,sip->isim , new_jval_v(NULL));// Siparis_isim(*sip)
    //     //  jrb_insert_str(b,sip->malzeme , new_jval_v(NULL));// Siparis_malzeme(*sip)
    //     //  jrb_insert_str(b,sip->renk , new_jval_v(NULL));// Siparis_renk(*sip)
    // }
        //  jrb_traverse(bn, b)
        //     printf(" %s", jval_s(bn->key)); 
        //     printf("\n"); 

  //    int sip_key = atoi(inputed[1]);
  // for(i=1;i<5;i++){
  //   if (jrb_find_str(b,inputed[i]) == NULL)
  //     (void)  jrb_insert_str(b,strdup(inputed[i]), new_jval_v(NULL));
  //   }

/* "search" Komutu agacta araştırma funksiyonu
 *******************************************/
int search_fun(char* inputed[])
{
  if(inputed[1]==NULL)
  {
    printf("“Biçim uygun değil.”\n");
    printf("Usage: search|sipKey");
    return 0;
  }
  
    if (jrb_find_int(b,atoi(inputed[1])) != NULL)
      printf("the key is : %d \n",jval_i(b->key));
    else
      printf("“Aranan kayıt bulunamadı.”");
    return 0;
}
/* "write" Komutu dosyaya yazma funksiyonu
 **************************************/
int write_fun(char* inputed[])
{
   if(inputed[1]==NULL)
  {
      printf("Biçim uygun değil\n");
      printf("Usage: write|Fileisim");
      return 0;
  }
    char* Fileisim = inputed[1]; // dosya isim
    //open file 
    file_ptr = open(Fileisim,O_WRONLY|O_CREAT|O_APPEND , 0644);
    if(file_ptr < 0){
        perror(Fileisim); 
        exit(1); 
    }    
     if(b==NULL) return error_message();    
    //write in file 
    jrb_traverse(bn, b){
      sz = write(file_ptr,jval_s(bn->key),strlen(jval_s(bn->key)));   
      sz = write(file_ptr," ",strlen(" "));  
    }    
      sz = write(file_ptr,"\n",strlen("\n"));  
      
    //close file
    if(close(file_ptr)<0){
        perror(Fileisim);
    }
    printf("All Tree items printed in %s\n",Fileisim);

   return 0;
}

/* "print" Komutu ekrana yazma funksiyonu
 **************************************/
int print_fun()
{
  if(b==NULL) return error_message();
    // jrb_traverse(bn, b)
    //   printf("%s ", jval_s(bn->key)); 
      jrb_traverse(bn, b)
       printf("%d ", jval_i(bn->key)); 
    printf(" \n "); 
  return 0;
}
// 
char** str_split(char* a_str, const char a_delim)
{
    char** result    = 0;
    size_t count     = 0;
    char* tmp        = a_str;
    char* last_comma = 0;
    char delim[2];
    delim[0] = a_delim;
    delim[1] = 0;

    /* Count how many elements will be extracted. */
    while (*tmp)
    {
        if (a_delim == *tmp)
        {
            count++;
            last_comma = tmp;
        }
        tmp++;
    }
    /* Add space for trailing token. */
    count += last_comma < (a_str + strlen(a_str) - 1);

    /* Add space for terminating null string so caller
       knows where the list of returned strings ends. */
    count++;
    result = malloc(sizeof(char*) * count);
    if (result)
    {
        size_t idx  = 0;
        char* token = strtok(a_str, delim);
        while (token)
        {
            assert(idx < count);
            *(result + idx++) = strdup(token);
            token = strtok(0, delim);
        }
        // assert(idx == count - 1);
        *(result + idx) = 0;
    }
    return result;
}