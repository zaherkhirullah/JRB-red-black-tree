/*********************************
*  __ --Grup Üyeleri--__ 
**********************************
1_ Eyad Almansour (B141210127)
2_ Zaher Khirullah(B151210568)
3_ Mohammad Almahamid (B141210263)
4_ Mumin Othman (G151210563)
5_ Abdulrahamn hamidi (G151210551)
*********************************/
#include "shell.h"
#include "prog.h"

void init(){
		// See if we are running interactively
        GBSH_PID = getpid();
        // The shell is interactive if STDIN is the terminal  
        GBSH_IS_INTERACTIVE = isatty(STDIN_FILENO);  

		if (GBSH_IS_INTERACTIVE) {
			// Loop until we are in the foreground
			while (tcgetpgrp(STDIN_FILENO) != (GBSH_PGID = getpgrp()))
					kill(GBSH_PID, SIGTTIN);             
	              
	        // Set the signal handlers for SIGCHILD and SIGINT
			act_child.sa_handler = Cocuk;
			act_int.sa_handler = signal_int;					
			
			sigaction(SIGCHLD, &act_child, 0);
			sigaction(SIGINT, &act_int, 0);
			
			// Put ourselves in our own process group
			setpgid(GBSH_PID, GBSH_PID); // we make the shell process the new process group leader
			GBSH_PGID = getpgrp();
			if (GBSH_PID != GBSH_PGID) {
					printf("Error, the shell is not process group leader");
					exit(EXIT_FAILURE);
			}
			// Grab control of the terminal
			tcsetpgrp(STDIN_FILENO, GBSH_PGID);  
			
			// Save default terminal attributes for shell
			tcgetattr(STDIN_FILENO, &GBSH_TMODES);

			// Get the current directory that will be used in different methods
			currentDirectory = (char*) calloc(1024, sizeof(char));
        } else {
                printf("Could not make the shell interactive.\n");
                exit(EXIT_FAILURE);
        }
}
void signal_int(int p)
{
	if (kill(pid,SIGTERM) == 0)
	 {
		printf("\nProcess %d received a sigint signal\n",pid);
		NoPropmt = 1;			
	 }
	else
	 {
		printf("\n");
	 }
}
void Cocuk(int p)
{
	while (waitpid(-1, NULL, WNOHANG) > 0)
	 {
	 	
	 }
	printf("\n");
}
// NOT : Buradan yukarıdaki init(), signalHandler_child(), signalHandler_int()
// fonksiyonları linuxta signal kullanımı için hazır alınmıştır. Linuxta signal'in
//  ne olduğunu anlamış bulunmaktayız fakat kodlarda karışıklılığa neden olmamak için
// signal kodlarını hazır bulup kodlara uyarladık. 

int commandExecute(char * command[],char* inputed[]){ 
	int i = 0;
	int j = 0;
    int background = 0; // Arka planda programı çalıştırabilmek için kontrol değeri.
	char *command_args[256];
	while ( command[j] != NULL){ // Bu döngü ile özel karakterli komutların bulunduğu durumlarda (">", "<", "&") kolaylık 
                                 // olması için yeni bir dizi tanımlıyoruz.
		if ( (strcmp(command[j],">") == 0) ||
			 (strcmp(command[j],"<") == 0) ||
			 (strcmp(command[j],"&") == 0))
		{
			break;
		}
		command_args[j] = command[j];
		j++;
	}
	
 	if(strcmp(command[0],"add") == 0 ) 	 
		add_fun(inputed);
    if(strcmp(command[0],"search") == 0 ) 
		search_fun(inputed);
    if(strcmp(command[0],"write") == 0 ) 
	write_fun(inputed);
   if(strcmp(command[0],"print") == 0){
		if(inputed[1]!=NULL)
			printf("Usage: print\n");
		else
		print_fun();
		}
	if(inputed[1]!=NULL)return 0; // eğer komut uygun değilse dongu tekrar basa dondur 
    if(strcmp(command[0],"quit") == 0) exit(0);
	 //Bulunduğumuz dosyadan baska bir dosyay gecmek için kullanılan komut	
    if(strcmp(command[0],"cd") == 0)
		changeDirectory(command);
    else{
		while (command[i] != NULL && background == 0){
            if (strcmp(command[i],"&") == 0){
				background = 1;
			}
			 // Cat komutu için gerekli işlemlerin yapılmasını saglayan koşul.             			
            else if (strcmp(command[i],"<") == 0){
								if (command[i+1] == NULL ){
					printf(">> lutfen < sonra ekrana yazdirmak istediginiz dosya adi yaziniz\n");
					return -1;
				}
				// Cat komutunda dosya giriş-çıkış işlemleri için parametre yolluyoruz.
				IOProcess(command_args,command[i+1],command[i+2],1); 
				return 1;
			}
			// Cat komutu ile çıkış yönlendirme yapmak için gerekli koşul.
			else if (strcmp(command[i],">") == 0){ 
				if (command[i+1] == NULL){
					printf("Komut Yeterli Degil !\n");
					return -1;
				}
				IOProcess(command_args,NULL,command[i+1],0); // Cat komutunda dosya giriş-çıkış işlemleri için parametre yolluyoruz.
				return 1;
			}
			i++;
        }
         command_args[i] = NULL;
         execProgram(command_args,background);
    }
    return 1;
}

void execProgram(char **command, int background){	 
    // Prosesler ile bir komutun gerçeklenmesi.
	int status;
	pid = fork();
	if(pid==0){ // Cocuk proses
		signal(SIGINT, SIG_IGN);
		setenv("parent",getcwd(currentDirectory, 1024),1);//Cocuk proses için parent'in pathname ini tanımlıyoruz

		if (execvp(command[0],command) < 0){ // Girilen bir komut yoksa hata veriyoruz.
			printf("Komut bulunamadı !");
			kill(getpid(),SIGTERM);
		}
	}
    if(pid < 0){ // Fork hatası
	    printf("Fork hatası - Cocuk proses olusturulamadi !\n");
		return;
	}
	 if (background == 0){ // Background da çalışabilmesi için bekleme komutu.
		 waitpid(pid,&status,0);
	}
     else{ // ebeveyn proses
     	 if( WIFEXITED(status))
	    {
	    	printf(" >[%d] retval: %d\n" , pid ,WEXITSTATUS(status));
	    }   
	}	 
}
void IOProcess(char * command[], char* inputFile, char* outputFile, int control){
	// Cat komutu için dup2 ve execvp fonksiyonları ile gerçeklenen dosya giriş çıkış işlemleri.
	int file;
    pid = fork();

	if(pid==0){ //Cocuk Proses
		
		if (control == 0){ // Çıkış yönlendirmesi			
			file = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600); //Dosya sadece yazmak için açılıp içi sıfırlanır.
			dup2(file, STDOUT_FILENO); //Konsol da dosya içindeki veriyi yazdırmak için kopyalama yapılır.
			close(file);
		} 
        else if (control == 1){ // Giriş ve çıkış yönlendirmesi
			file = open(inputFile, O_RDONLY, 0600); // Dosya sadece okunmak için açılır.
			dup2(file, STDIN_FILENO); // Dosya içindekiler kopyalanıp dosya kapatılır. 
			close(file);
			
			file = open(outputFile, O_CREAT | O_TRUNC | O_WRONLY, 0600); // Farklı dosya içine veri yazılmak için açılır
			dup2(file, STDOUT_FILENO); // Yine önceki dosyadan kopyalananlar bu dosyaya yazılır.
			close(file);		 
		}
		 
		setenv("parent",getcwd(currentDirectory, 1024),1); //Child proses için parent'i ortam değişkenlerine tanımlarız.
		
		if (execvp(command[0],command) < 0){ // Komut calıstırılamazsa hata verilir.
			printf("err");
			kill(getpid(),SIGTERM);
		}		 
	}
    if(pid < 0){ // Fork hatası
		perror("Fork hatası - Cocuk proses olusturulamadi !");
		return;
	}
    waitpid(pid,NULL,0);
}
void prompt(){
    char hostName[256] = "";
    gethostname(hostName, sizeof(hostName));
    // printf("%s@%s:%s$", getenv("USER"), hostName,currentDirectory); 
	 /* Burada normal UNIX'teki terminaller gibi bir promp yapmaya çalıştık.*/	
    printf("> ");
	//USER ile kullanıcı adını, hostname ile de bilgisayarın adını ekrana basıyoruz.
    fflush(stdout);
}
// Komut çalıştırılacak konumun değiştirildiği fonksiyon.
int changeDirectory(char * command[])
{
	// Sadece cd komutu girildiğinde bir alt dosya konumuna gidilmesini saglayan koşul.
    if (command[1] == NULL) {
		chdir(getenv("HOME")); 
	    return 1;
	}
	else{ 
		if (chdir(command[1]) == -1) {
			printf(" %s: Boyle bir dosya yok.\n", command[1]);
            return -1;
		}
	}
    return 0;
}

int main(){
    char line[MAX_COMMAND_LINE];
	char *tokens[TOKEN_LIMIT];  // Bu tanımlamayı line a girilen komutu kısıtlamak için kullanıyoruz. 
                                // Örneğin "-" gibi işaretler girildiğinde yapılacak işlemler için.
	char** inputed_command;	
	int tokenNumber;
    int run_control = 1;
    init(); // Hazır Fonksiyon
    setenv("shell",getcwd(currentDirectory, 1024),1); //Child proses için shell in directorysini ortam değişkenlerine tanımlıyoruz.

    while(run_control){      
    prompt();
         // line : girilen komut , MAXLINE : komutun max uzunluğu, stdin : C'de IO için parametre.
		fgets(line, MAX_COMMAND_LINE, stdin);
	inputed_command = str_split(line, '|');
	
	if(inputed_command){
		tokens[0] = *inputed_command;	
		// free(*inputed_command);
	}
	else
	inputed_command=NULL;
	 // Kullanıcı prompta bir şey girmezse döngü başa döner.
	if((tokens[0] = strtok(line," \n\t")) == NULL) 
		continue;
	tokenNumber = 1;
	while((tokens[tokenNumber] = strtok(NULL, " \n\t")) != NULL) 
		tokenNumber++;
	commandExecute(tokens,inputed_command);
  }   	
    free(currentDirectory);
    free(inputed_command);
    return 0;
}


