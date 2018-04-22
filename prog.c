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

JRB b, bn;
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
  if(b==NULL) b = make_jrb();

  int cnt=0;
  if(inputed) // inputed biçimler sayisi hesaplama 
  {
      for (i = 1; *(inputed + i); i++)
      cnt++;
  }
  // biçim uygun bulmak için şartlar
  if(inputed[1]==NULL|| atoi(inputed[1]) < 0 ||inputed[5] || cnt!=4)
  {
    printf("Biçim uygun değil\n");
    if(inputed[1]!=NULL && atoi(inputed[1]) == 0) //if  key it isn't number  (integer)
      printf("Usage: sipKey must be number [integer]\n");
    printf("Usage: add|sipKey|sipAd|sipMalezeme|sipRenk\n");
    return 0;
  }
    Siparis *sip ;
      sip->key    = atoi(inputed[1]); 
      sip->isim   = inputed[2]; 
      sip->malzeme= inputed[3]; 
      sip->renk   = inputed[4];
      printf("%d\n",sip->key);

    if (jrb_find_int(b, sip->key) == NULL) {
        (void) jrb_insert_int(b,sip->key , new_jval_v(NULL));// Siparis_key(*sip)
        //  jrb_insert_str(b,sip->isim , new_jval_v(NULL));// Siparis_isim(*sip)
        //  jrb_insert_str(b,sip->malzeme , new_jval_v(NULL));// Siparis_malzeme(*sip)
        //  jrb_insert_str(b,sip->renk , new_jval_v(NULL));// Siparis_renk(*sip)
    }
    printf("The items was added to Tree .\n");
        //  jrb_traverse(bn, b)
        //     printf(" %s", jval_s(bn->key)); 
        //     printf("\n"); 

  //    int sip_key = atoi(inputed[1]);
  // for(i=1;i<5;i++){
  //   if (jrb_find_str(b,inputed[i]) == NULL)
  //     (void)  jrb_insert_str(b,strdup(inputed[i]), new_jval_v(NULL));
  //   }
    return 0 ;
}
/* "search" Komutu agacta araştırma funksiyonu
 *******************************************/
int search_fun(char* inputed[])
{
  if(inputed[1]==NULL)
  {
    printf("Biçim uygun değil\n");
    printf("Usage: search|sipKey");
    return 0;
  }
  
    if (jrb_find_int(b,atoi(inputed[1])) != NULL)
        printf("the key is : %d \n",jval_i(b->key));


  return 0;
}

/* "write" Komutu dosyaya yazma funksiyonu
 **************************************/
int write_fun(char* inputed[])
{
   if(inputed[1]==NULL)
  {
      printf("Biçim uygun değil\n");
      printf("Usage: write|FileName");
      return 0;
  }
    char* FileName = inputed[1]; // dosya name
    //open file 
    file_ptr = open(FileName,O_WRONLY|O_CREAT|O_APPEND , 0644);
    if(file_ptr < 0){
        perror(FileName); 
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
        perror(FileName);
    }
    printf("All Tree items printed in %s\n",FileName);

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


// char* s_split( char string[])
// {
//     char *ch;
//     ch = strtok(string, "|");
//     while (ch != NULL)
//     {
//         printf("%s\n", ch);
//             ch = strtok(NULL, "|"); 
//     }
//     return ch;
     
// }