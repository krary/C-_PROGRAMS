#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>

int filled_sectors = 0;
#define UNIDAD 512
uint8_t arr_global[512*16]={0};
uint8_t indice[16];
uint64_t indice_global =0;

void arr_g(uint8_t *ptr);
uint64_t show_fat32(uint8_t *ptr,uint8_t tam);
uint64_t formula(uint8_t *ptr,uint64_t inicio_fat);
void show_info(uint8_t *ptr,int index);
void show_info_root(uint8_t *ptr,int index);
void show_info_name(uint8_t *ptr,const char* name);
int list_item();
void jump(int fd,uint64_t num);
 
 
 //****************************************************************LIST_ITEM********************************************************************************
 int list_item(){
char option[16];
int m;
while(1){
printf("Elije una opcion de 1 ... 16\n");
fgets(option,sizeof(option),stdin);
m = atoi(option);
if(m == 0){
break;
}

if(m > filled_sectors || m < 0 ){printf("Fuera de rango debe de elejir de el 1 a 16...\n");continue;}
else{break;}
}

return m;
}


//************************************************************************************************************************************************************
//******************************************************************FORMULA***********************************************************************************
uint64_t formula(uint8_t *ptr,uint64_t inicio_fat){
   
   uint64_t bytes_por_sector =  show_fat32(&ptr[11],2);           //REALIZAR OPERACIONES INVERSAS PARA OBTENER EL HEXDUMP DE UN DECIMAL
   uint64_t sectors_por_cluster = show_fat32(&ptr[13],1);
   uint64_t sectors_reservado = show_fat32(&ptr[14],2);
   uint64_t numero_de_fat = show_fat32(&ptr[16],1);
   uint64_t sectores_por_fat = show_fat32(&ptr[36],4);
   uint64_t inicio_del_cluster= show_fat32(&ptr[44],4);
  /*printf("Byts por sector:  %lu\n",bytes_por_sector);
   printf("Sectores por cluster: %lu\n",sectors_por_cluster);
    printf("Sectores reservados :%lu\n",sectors_reservado);
     printf("Numero de FAT :%lu\n",numero_de_fat);
      printf("Sectores reservados por fat: %lu\n",sectores_por_fat);
      printf("Valor de inicio_del_cluster: %lu\n",inicio_del_cluster);*/
      //REALIZANDO EL CALCULO
      
      uint64_t zonas_fat = sectores_por_fat * numero_de_fat;
    uint64_t sectores_raiz = inicio_fat + sectors_reservado + zonas_fat;
      //printf("TOTAL : [%lu]\n",sectores_raiz);
    return sectores_raiz;
  }
//****************************************************************************************************************************************************************

//*******************************************************SHOW INFO************************************************************************************************
void show_info(uint8_t *ptr,int index){
   const char *verde = "\033[34m";
   const char *reset = "\033[0m";
   const char *color = reset;
   for(int x = 0 ; x < index; x++){
      printf("%s%02X %s",color,ptr[x],color);
      if((x + 1) == 11 || (x+1) == 12){color = verde;}
      if((x + 1)== 36 || (x +1) == 37|| (x +1) == 38|| (x +1) == 39){color=verde;}
     else{color = reset;}
      if((x + 1) % 16== 0){printf("\n");}}
      }

//******************************************************************SHOW INFO ROOT*****************************************************************
void show_info_root(uint8_t *ptr,int index){
   const char *verde = "\033[34m";
   const char *reset = "\033[0m";
   const char *color = reset;
   for(int x = 0 ; x < index; x++){
     
      uint8_t *information = &ptr[x * 32];
      if(x == 0){color = verde;}
      printf("%s%02X%s ",color,ptr[x],color);
      if((x + 1) % 32== 0){printf("\n");
      color = verde;}
      else{color = reset;}
      }
  
      }
//*******************************************************************SHOW_INFO_NAME****************************************************************************
void show_info_name(uint8_t *ptr,const char* name){
printf("%s\n",name);
for(int x =0; x < 512;x++){ 



uint8_t *byte = &ptr[x * 32];
if(byte[0] == 0x00){break;}
if(byte[0] == 0xE5){/*printf("El archivo ha sido borrado\n");*/continue;}
if(byte[11] == 0x0F){continue;}

printf("Item %2d: [",filled_sectors);

for(int j = 0; j < 8; j++){
if(byte[j] != ' '){
printf("%c",byte[j]);
 
}
}
if (!(byte[11] & 0x10)){printf(".");
for(int j = 8 ; j < 11; j++){
    
    if(byte[j] != ' '){printf("%c",byte[j]);}

}}
else{printf("/");}

printf("]");
printf("          ");
printf("[");
for(int m = 0; m < 32; m++ ){printf("%02X ",byte[m]);
arr_global[filled_sectors] = byte[m];

filled_sectors++;

}
printf("]");

printf("\n");
printf("FilledSectors [%d]",filled_sectors);
printf("\n");

}
}

//***********************************************************************SHOW FAT32********************************************************************************
uint64_t show_fat32(uint8_t *ptr,uint8_t tam){
    uint64_t out = 0;
    for(int x = 0; x < tam; x++){
       out |= (uint64_t)(ptr[x]) << (8 * x);}
    return out;}
  //********************************************************************************************************************************************************************

//********************************************************************************JUMP**********************************************************************************
void jump(int fd,uint64_t num){
    lseek(fd,num,SEEK_SET);

}
//***********************************************************************************************************************************************************************


int main(){
uint8_t arr[UNIDAD];
const char *path = "/dev/sda";
int fd = open(path,O_RDONLY);
ssize_t firma = read(fd,arr,UNIDAD);
//LLAMADAS DE FUNCIONES

uint64_t size = show_fat32(&arr[446 + 8],4);

jump(fd,size * UNIDAD); //PRIMER SALTO HACIA FAT32 O;
 read(fd,arr,UNIDAD);
 uint64_t num_sectors = show_fat32(&arr[11],2);
 
 
  //show_info(arr,UNIDAD);
  
  
  printf("Numero Convertido : %lu\n",num_sectors);
  uint64_t sectores_raiz =   formula(arr,size);
  jump(fd,sectores_raiz * UNIDAD);
  read(fd,arr,UNIDAD);
 
int x = 0;
  
 for(x = 0; x < 16; x++){
         show_info_root(arr,UNIDAD);
         show_info_name(arr,path);
         
      if(arr[0] == 0x00){break;}
      if(read(fd,arr,UNIDAD) != UNIDAD){break;}
      //show_info_root(arr,UNIDAD);
      //printf("[%d]\n ",x); 
            indice[x] = x; 
      }
      
     int indece_election = 0;
     for(int z = 0; z < filled_sectors; z++){
         uint8_t *lt = &arr_global[z * 32];
        if(lt[0] == 0x00){break;}
         printf("[%d]",indece_election);
         
         for(int y = 0; y < 8; y++){
           if(lt[y] != ' '){
           printf("%c",lt[y]);}
           }
         if(!(lt[11] & 0x10)){
         printf(".");
         for(int m = 8 ;m < 11; m++){
         printf("%c",lt[m]);
         }
         
         }
         else{printf("/");}
         printf("\n");
         indece_election++;
     }
   
   
   uint8_t election[16];
   printf("Choose yuor election please very faster!!!!its time to make a choice mr Andersson...\n");
   fgets(election,16,stdin);
   int numero_election = atoi(election);
   
   uint8_t *re;
   
   for(int z = 0; z < filled_sectors; z++){
   re = & arr_global[z*32];
   if(numero_election <= z)break;
   numero_election--;
   }
   printf("El numero election es de : [%d]\n",numero_election);
  
   
   
   
   //*********************************************************************************************************************
   for(int z = 0; z < 32; z++){
     
     printf("%02X ",re[z]);
     }
   
   
   
   
   
   
   
   
   
   
   
   

return 0;}
