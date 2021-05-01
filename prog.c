/*********************************
**********************************
 Zaher Khirullah
*********************************/
#include "prog.h"
#include "siparis.h"

JRB b, bn,siparis_tree , b2;
IS myis; 
Siparis *sip;
int i,  file_ptr, sz;

int error_message(){
  printf("Error :No elemants in Tree \n");
  printf("please try \"add|-sipKey|sipAd|sipMalezeme|sipRenk\" to add items to Tree\n");
  return 0; 
}
/* "add" Komutu agaca siparişlari ekleme funksiyonu
 *******************************************/
int add_fun(char* inputed[])
{
  int cnt = 0;
  if(inputed){ // inputed biçimler sayisi hesaplama 
    for (i = 1; *(inputed + i); i++)
      cnt++;
  }
  // biçim uygun bulmak için şartlar
  if(inputed[1]==NULL ||atoi(inputed[1]) <= 0||inputed[5] || cnt!=4){
    printf("\t“Biçim uygun değil.”\n");
    printf("\tUsage: add|sipKey|sipAd|sipMalezeme|sipRenk\n");
    if(inputed[1]!=NULL && atoi(inputed[1]) == 0) //if  key it isn't number  (integer)
      printf("\t-sipKey must be number [integer].\n");
    return 0;
  }

  if(b==NULL)  b = make_jrb();  // Eğer JRB (b ) boş ise new obj all 
  // p siparis struct tipinden tanımlama 
    sip = malloc(sizeof(Siparis)); 
  // değerler p'ye atama işlemleri
    sip->key = atoi(inputed[1]); 
    sip->isim = inputed[2];
    sip->malzeme = inputed[3];
    sip->renk = inputed[4];
  // klaveyden girilmis key degeri ara 
    if (jrb_find_int(b,sip->key) == NULL){ // bolunmadi ise 
      siparis_tree = make_jrb(); // new agac tanimla
      jrb_insert_int(b,sip->key, new_jval_v((void *) siparis_tree)); // siparis key agaca ekle 
      jrb_insert_str(siparis_tree,sip->isim, new_jval_v((void *) sip));
      jrb_insert_str(siparis_tree,sip->malzeme, new_jval_v((void *) sip));
      jrb_insert_str(siparis_tree,sip->renk, new_jval_v((void *) sip));
    } 
    else{  // bulundu ise
        siparis_tree = (JRB) bn->val.v;
        printf("Ayni anahtar (Siparis Key =  %d ) Mevcut .\n",sip->key);
    }
    // printf("Elemanlar agaca başarila eklendi .\n");  
    return 0 ;
}

/* "search" Komutu agacta araştırma funksiyonu
 *******************************************/
int search_fun(char* inputed[])
{
  if(inputed[1]==NULL){
    printf("\t“Biçim uygun değil.”\n");
    printf("\tUsage: search|sipKey");
    return 0;
  }
  if(b==NULL) return error_message();
  if (jrb_find_int(b,atoi(inputed[1])) != NULL){
    jrb_traverse(bn, b) {
      siparis_tree = (JRB) bn->val.v;
      jrb_traverse(b2, siparis_tree)
          sip = (Siparis *) b2->val.v;
      if( sip->key ==atoi(inputed[1]) )
        printf("%d,%s,%s,%s\n", sip->key, sip->isim, sip->malzeme, sip->renk);
    } 
  }
  else
    printf("“Aranan kayıt bulunamadı.”\n");
  return 0;
}
/* "write" Komutu dosyaya yazma funksiyonu
 **************************************/
int write_fun(char* inputed[])
{
   if(inputed[1]==NULL){
      printf("\tBiçim uygun değil\n");
      printf("\tUsage: write|FileName");
      return 0;
  }
    char* FileName = inputed[1]; // dosya isim
    //open file 
    // file_ptr = open(FileName,O_WRONLY|O_CREAT|O_APPEND , 0644);
    // if(file_ptr < 0){
    //     perror(FileName); 
    //     exit(1); 
    // }    
     if(b==NULL) return error_message();    
     /* siparisler dosyada yazdirmak için  */
    FILE* fp;
    fp = fopen (FileName, "a");
    jrb_traverse(bn, b) {
    siparis_tree = (JRB) bn->val.v;
    jrb_traverse(b2, siparis_tree)
       sip = (Siparis *) b2->val.v;      
    fprintf(fp,"%d, %s, %s, %s",sip->key,sip->isim,sip->malzeme,sip->renk);      
  }
  //close file
    if(fclose(fp)<0){
        perror(FileName);
    }
  //  if(close(file_ptr)<0){
  //     perror(FileName);
  // }
    printf("Tüm agaçtaki elemanlar %s içerisinde yazdırıldı. \n",FileName);
   return 0;
}

/* "print" Komutu ekrana yazma funksiyonu
 **************************************/
int print_fun()
{
  if(b==NULL) return error_message();
  jrb_traverse(bn, b) {
    siparis_tree = (JRB) bn->val.v;
    // sz = write(file_ptr,jval_i(bn->val),strlen(jval_i(bn->val)));
    jrb_traverse(b2, siparis_tree) 
        sip = (Siparis *) b2->val.v;
     printf("%d,%s,%s,%s",sip->key,sip->isim,sip->malzeme,sip->renk);
    } 
  return 0;
}
int temizleme(char* inputed[])
{
  if(inputed)
    free(*inputed);
  if(sip)
    free(sip);
  if(b){
    jrb_traverse(bn, b)
      jrb_delete_node(bn);
    jrb_free_tree(b);
  }
  if(siparis_tree){
    jrb_traverse(b2, siparis_tree)
      jrb_delete_node(b2);
    jrb_free_tree(siparis_tree);  
      
  }
  printf("“Her şey temizlendi.”\n");
 return 0;
}
int pro_fun(char *inputed[])
{
    
    if(inputed[1]==NULL)
    {
      printf("Usage: pro|input.txt\n");
      return 0;
    }
    char* fileIsmi =inputed[1];
    char** txt_inputed;
    char* txt_line ;
    myis = new_inputstruct("input.txt");
    if(myis){
      while(get_line(myis) != EOF){  
        for(i = 0; i < myis->NF; i++){
          txt_line = myis->fields[i];
        txt_inputed = str_split(txt_line,'|');
        add_fun(txt_inputed);
        free(*txt_inputed);         
        }
      }
    jettison_inputstruct(myis);    
     printf("elemanlar başarila agaca eklendi. \n");      
    }
    else
    printf("HATA: %s dosya bulunmadi \n",inputed[1]);
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
