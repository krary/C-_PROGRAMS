#include "library.h"
//index value_fileno
//index memmove
//index fabs
//index stat
//index sscanf
//index isspace
//index fwrite
//index memmove
//index seek
//index bit_bit
//index module
//index draw_character
//index termios_old
//stdout_fileno
struct termios new,old;

void stdout_fileno(){
	fd_set lista;
	FD_ZERO(&lista);
	FD_SET(STDIN_FILENO,&lista);
	struct timeval tv = {3,0};
	select(STDIN_FILENO +1,&lista,NULL,NULL,&tv);

    char buffer[1024];
    ssize_t bytes_found = read(STDIN_FILENO,buffer,sizeof(buffer));
    if(bytes_found > 0){buffer[bytes_found] = '\0';printf("RESULTAOD: %s\n",buffer);return;}
    
	}


void get_term_old(struct termios *o){
	tcgetattr(STDIN_FILENO,o);
}

void get_term_new(struct termios *n,struct termios *o) {
	*n = *o;
	n->c_lflag &= ~(ICANON | ECHO);
	tcsetattr(STDIN_FILENO,TCSANOW,n);}

void take_back(struct termios *o){
	tcsetattr(STDIN_FILENO,TCSANOW,o);
}

void draw_character(){
	uint8_t cero[] = { 0xF0, 0x10, 0x20, 0x40, 0x40};
	for(int x = 0;x<5;x++){
	   uint8_t single = cero[x];
		for(int s = 0; s < 8;s++){
			uint8_t bit = single & (0x80 >> s);
			if(bit != 0){
				printf("*");
			}
			else{
				printf(" ");
			}
		}
		printf("\n");
	}
}

void value_fileno(){
	FILE *f = fopen("erase.c","rb");
	FILE *f2 = fopen("library.h","rb");
    int num_descriptor = fileno(f);
     int num_descriptor2 = fileno(f2);
    printf("EL DESCRIPTOR DE ARCHIVO erase.c es : [%d]\n",num_descriptor);
    printf("EL DESCRIPTOR DE ARCHIVO library.h es : [%d]\n",num_descriptor2);

	if(f == NULL)return;
    if(f!=NULL)fclose(f);
    if(f2 == NULL)return;
    if(f2!=NULL)fclose(f2);
}

void value_hex(){
	int pixel[8] = {0};
	uint8_t y = 0x80;
	for(int x = 0; x < 8;x++){
		uint8_t masc = y ^ 1;
		if(masc != 0)pixel[x] = 1;
		}
	for(int x = 0; x < 8;x++){
		printf("[%d] ",pixel[x]);}	
		printf("\n");

	
}
void module(){
	int numero = 64;
    for(int x = 0; x <120;x++){
    	int s = x % numero;
    	printf("MODULE DE %d : [%d]\n",x,s);}
}
void bit_bit(){
	uint8_t a = 0xA;
	uint8_t b = 0xB;

    a |= b;
    printf("VALUE: 0x%02X\n",a);
}


void seek(char*filename){
   FILE *f = fopen(filename,"rb");
   if(!f)return;

   fseek(f,0,SEEK_END); //EL CURSOR SE POSICIONA AL FINAL DE EL ARCHIVO
   long tam = ftell(f);

   fseek(f,0,SEEK_SET); //EL CURSOR SE POSICIONA AL PRINCIPIO DE EL ARCHIVO
   double num_result = tam / 1000;
   num_result = fabs(num_result);
   printf("El tam de el archivo es de : %zu\n",tam);
   fclose(f);
}



void cut_text(char *elementos,int i){
	printf("tam de texto ahora es : %s\n",elementos);
	char *new_text = "texto nuevo";
	size_t len_new = strlen(new_text);
	size_t len_old = strlen(elementos);
	if(i < 0 || i>(int)len_old)return;
	memmove(&elementos[i+len_new],&elementos[i],len_old - i +1);// elementos[i+len_new] = crea espacion en blanco // tercer y cuarto param
	//copia desde el indice dado hasta el final de la cadena en este caso o hasta el indice dado osea tenemos que marcar princ y fin
	memcpy(&elementos[i],new_text,len_new);
		printf("tam de texto es : %s\n",elementos);
}
	

float resta_flotante(float n,float s){
	float i = n - s;
	return i;}


//fabs
void quitar_signo(float *a){
   
    *a = fabs(*a);
   
}


//stat
uint8_t path_file(char *path){
	struct stat info;
	if(stat(path,&info) !=0)return 0x0;

	uint8_t i = ((info.st_mode) & 0xf000)>>12;
	return i;
}
//sscanf
void sscanff(){
	float x,y;
	char *m = "lisando 1 2 lisandro";
	int numero = sscanf(m,"lisandro %f %f",&x,&y);
	if(numero > 0){printf("%f %f\n",x,y);}
	else{printf("Parámetros incorrectos\n");}}
//isspace
void space(){
	char mensaje[] = "Hello World . . hello wordl hi world hola mundo";
	int count = 0;
	int swittch = 0;
	for(int x = 0; mensaje[x] != '\0';x++){
		if(isspace((unsigned char)mensaje[x])){
			swittch = 0;}
		else if(swittch == 0){
			swittch = 1;
			count++;}
	}  
  printf("El numero de palabras que se encontro en mensaje %s \n%d\n",mensaje,count);}

//mkdir
int  folderr(char *name_FOLDER){
   if(mkdir(name_FOLDER,0755)== -1){
       if(errno == EEXIST) {printf("THE FOLDER EXIST!!\n");return 1;}
       else{
       	printf("AN ERROR HAS OCURRED!!!\n");
       	
       	return 0;}}}


//fwrite
int copy_file(char *src,char *dst){
	FILE *f_src;
	FILE *f_dst;
	f_src = fopen(src,"rb");
	f_dst = fopen(dst,"wb");
	if((!f_src) || (!f_dst)){printf("CANNOT CREATE OR MAKE INSTANCE OF FILE DESCRITPOR\n");return 0;}

    char buffer[1024];
    memset(buffer,0,sizeof(buffer));
    size_t tam;

    while((tam = fread(buffer,1,sizeof(buffer),f_src))	> 0){
    	fwrite(buffer,1,tam,f_dst);
    }

  if(f_src != NULL)fclose(f_src);
  if(f_dst != NULL)fclose(f_dst);    
  return 1;
	
}

void executing_copy_file(){
	char *name_FOLDER = "LISANDRO_FOLDER";
	int status_folder = folderr(name_FOLDER);
	if(status_folder !=1)return;
	FILE *command;
	command = popen("ls","r");
	if(command == NULL){printf("CANNOT EXECUTE THE COMMAND");return;}
	char constructor[1024];
	char buffer[1024];
	while(fgets(buffer,sizeof(buffer),command) !=NULL){
        buffer[strcspn(buffer,"\n")] = '\0';	
        uint8_t single_ = path_file(buffer);
        if(single_ == 8){
        	snprintf(constructor,sizeof(constructor),"%s/%s",name_FOLDER,buffer);
        	printf("%s\n",constructor);
        	int status_copy_file = copy_file(buffer,constructor);
        	
        }	    	
	
	}
	if(command !=NULL)pclose(command);
}


int main(){
  Termios *term_ = calloc(1,sizeof(Termios));
  			term_->get_term_old = get_term_old;
  			term_->get_term_new = get_term_new;
  		    term_->take_back    = take_back;

get_term_old(&old);
get_term_new(&new,&old);

while(true){
    stdout_fileno();
	printf("Ejecutando.....");
	getchar();
}



//take_back(&old);
 if(term_ != NULL)free(term_);
return 0;
}
