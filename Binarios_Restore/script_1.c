#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<stdbool.h>
#include<fcntl.h>
#include<unistd.h>
#include<string.h>
#define UNIDAD 512
typedef struct{
    uint64_t byte_por_sector;       // 00 02            512 bytes (0x0200)
    uint64_t sectores_por_cluster;      //   10             16 sectores por cluster
    uint64_t sectores_reservados;    //  6E 09           2414 sectores (0x096E)
    uint64_t numero_de_fat;             // 02              2 copias de la tabla FAT    
    uint64_t sectores_por_fat;       //C4 DA 01 00       121,540 sectores (0x0001DAC4)
    uint64_t inicio_raiz;            //02 00 00 00       Cluster número 2
}__attribute__((packed)) Info_base;



typedef struct{
    uint8_t nombre[8];
    uint8_t extension[3];
    uint8_t type;
    uint8_t date_made[2];
    uint8_t date_made_2[2];
    uint8_t last_access[2];
    uint8_t high_cluster[2];
    uint8_t saved[4];
    uint8_t low_cluster[2];
    uint8_t size[4];
   } __attribute__((packed)) Ficha;


typedef struct{
    int fd;
    uint64_t fat_init; //2048
    uint64_t lba_partition;
    uint8_t *re;
}data;
data data_st;




Info_base info_base = {0};
int filled_sectors = 0;
uint8_t arr_global[512*16]={0};
uint64_t indice_global =0;
char *rojo = "\033[31m";
char *reset = "\033[0m";
char *color;

void arr_g(uint8_t *ptr);
uint64_t show_fat32(uint8_t *ptr,uint8_t tam);
uint64_t formula(uint8_t *ptr,uint64_t inicio_fat);
void show_info(uint8_t *ptr,int index);
void show_info_root(uint8_t *ptr,int index);
void show_info_name(uint8_t *ptr,const char* name);
int list_item();
void jump(int fd,uint64_t num);
void reading_election(uint8_t *ptr,int factor);
void last_time(Ficha *ptr);
void size_file(uint8_t *ptr);
//******************************************SIZE FILE********************************************************************************
void size_file(uint8_t *ptr){
uint64_t high_cluster = show_fat32(&ptr[20],2);
uint64_t low_cluster = show_fat32(&ptr[26],2);
printf("HIGH CLUSTER : [%lu] LOW CLUSTER : [%lu]\n",high_cluster,low_cluster);
}
//hola




//********************************************LAST TIME ********************************************************************************
void last_time(Ficha *ptr){
   uint16_t convert_byte = (uint16_t)ptr->last_access[0] | ((uint16_t)ptr->last_access[1] << 8);
   
   int anio = ((convert_byte >> 9) & 0x7F) + 1980;
   int mes  = (convert_byte >> 5) & 0x0F;
   int dia  = (convert_byte & 0x1F);
   printf("Ultimo acceso: DD : %02d/M : %02d/Y : %d\n", dia, mes, anio);

}



//*******************************************************READING ELECTION**********************************************************

void reading_election(uint8_t *ptr,int factor){
if(factor == 0){  
   char choice [34];
printf("[0]READ BYTES......\n[1]READ NAME...... \n");
fgets(choice,sizeof(choice),stdin);
int nchoice_r = atoi(choice);

if(nchoice_r == 0){
color = rojo;
 for(int z = 0; z < 32; z++){
     printf("%s%02X%s ",color,ptr[z],color);
     if((z + 1) % 32 == 0)printf("\n");
     }
     color = reset;
  }
if(nchoice_r == 1){
  color = rojo;
  for(int z = 0; z < 32; z++){
     for(int s = 0; s < 8;s++){
       if(ptr[s] != ' '){
        printf("%s%c%s",color,ptr[s],color);}
        }
      if(!(ptr[11] & 0x10)){
      printf(".");
      for(int j = 8; j < 11;j++){
         printf("%s%c%s",color,ptr[j],color);}
      }else{printf("/");}
      printf("\n");
      break;}
      
      color = reset;
      }
else{
    color = rojo;
    printf("%sElection not possible...%s",color,color);
    color = reset;
}

}
if(factor == 1){
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
         printf("%c",lt[m]);}}
         else{printf("/");}
         printf("\n");
         indece_election++;}
         
int numero_election = list_item(indece_election); 
data_st.re = &arr_global[numero_election * 32]; //ESTA LINEA LLENA UN ARRAY DE LOS 32 BYTE DE LA ELECCION DE EL USUARIO
  


}//

      }
//************************************************************************************************************************************
//***********************************************************LIST_ITEM***************************************************************
 int list_item(int indice_){
char option[16];
int m;
while(1){
printf("Elije una opcion de....\n");
fgets(option,sizeof(option),stdin);
m = atoi(option);
if(m == 0){
break;
}
if(m > indice_ || m < 0 ){printf("Fuera de rango debe de elejir de el 1 a %d...\n",indice_);continue;}
else{break;}}
return m;}
//**************************************************************************************************************************************
//********************************************FORMULA***********************************************************************************
uint64_t formula(uint8_t *ptr,uint64_t inicio_fat){
   
   info_base.byte_por_sector =  show_fat32(&ptr[11],2);           //REALIZAR OPERACIONES INVERSAS PARA OBTENER EL HEXDUMP DE UN DECIMAL
   info_base.sectores_por_cluster = show_fat32(&ptr[13],1);
   info_base.sectores_reservados = show_fat32(&ptr[14],2);
   info_base.numero_de_fat = show_fat32(&ptr[16],1);
   info_base.sectores_por_fat = show_fat32(&ptr[36],4);
   info_base.inicio_raiz= show_fat32(&ptr[44],4);
   
   
   
   
   
  /*printf("Byts por sector:  %lu\n",bytes_por_sector);
   printf("Sectores por cluster: %lu\n",sectors_por_cluster);
    printf("Sectores reservados :%lu\n",sectors_reservado);
     printf("Numero de FAT :%lu\n",numero_de_fat);
      printf("Sectores reservados por fat: %lu\n",sectores_por_fat);
      printf("Valor de inicio_del_cluster: %lu\n",inicio_del_cluster);*/
      //REALIZANDO EL CALCULO
      
      uint64_t zonas_fat = info_base.sectores_por_fat * info_base.numero_de_fat;
    uint64_t sectores_raiz = inicio_fat + info_base.sectores_reservados + zonas_fat;
      //printf("TOTAL : [%lu]\n",sectores_raiz);
    return sectores_raiz;
  }
//**************************************************************************************************************************************
//***************************************************SHOWINFO**************************************************************************
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

//*****************************************************SHOW INFO ROOT*****************************************************************
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
      else{color = reset;}}}
//********************************************SHOW_INFO_NAME****************************************************************************
void show_info_name(uint8_t *ptr,const char* name){

for(int x =0; x < 512;x++){ 
uint8_t *byte = &ptr[x * 32];
if(byte[0] == 0x00){break;}
if(byte[0] == 0xE5){continue;}
if(byte[11] == 0x0F){continue;}
for(int m = 0; m < 32; m++ ){
arr_global[filled_sectors] = byte[m];
filled_sectors++;
}}
}

//********************************************SHOWFAT32********************************************************************************
uint64_t show_fat32(uint8_t *ptr,uint8_t tam){
    uint64_t out = 0;
    for(int x = 0; x < tam; x++){
       out |= (uint64_t)(ptr[x]) << (8 * x);}
    return out;}
  //************************************************************************************************************************************
//************************************************JUMP**********************************************************************************
void jump(int fd,uint64_t num){
    lseek(fd,num,SEEK_SET);

}
//***************************************************MAIN*********************************************************************************
int main(){
uint8_t arr[UNIDAD];
const char *path = "/dev/sdb";
data_st.fd = open(path,O_RDONLY);
ssize_t firma = read(data_st.fd,arr,UNIDAD);
//LLAMADAS DE FUNCIONES

 show_info(arr,UNIDAD);
printf("**************************************************\n");
//**************PRIMER SALTO HACIA FAT32 O*****************
data_st.fat_init = show_fat32(&arr[446 + 8],4);
jump(data_st.fd,data_st.fat_init * UNIDAD); 
 read(data_st.fd,arr,UNIDAD);
 //********************************************************
show_info(arr,UNIDAD);
 printf("**************************************************\n");
 
 
 //*************JUMP HACIA EL LBR RAIZ************************
  data_st.lba_partition =   formula(arr,data_st.fat_init);
 jump(data_st.fd,data_st.lba_partition*UNIDAD);
  read(data_st.fd,arr,UNIDAD);
 ///***********************************************************
 
 show_info(arr, UNIDAD);
 printf("**************************************************\n");
 //********ESTE BUCLE LLENA UN ARRAY GLOBAL [arr_global] SOLO CON INFORMACION IMPORTANTE ES DECIR SOLO 32 byte  DE CADA NOMBRE ******************************
 for(int x = 0; x < 16; x++){
         show_info_name(arr,path);
         if(arr[0] == 0x00){break;}
        if(read(data_st.fd,arr,UNIDAD) != UNIDAD){break;}
          }
//*******************************************************************************************************************************************************************************
          
//ESTE BUCLE SOLO REPRODUCE EN PANTALLA CADA UNO DE LOS ONCE BYTES DE CADA UNO DE LOS BLOQUES DE 32 BYTE EN arr_global**************************************************        
         //ESTA FUNCION DEVUELVE LA OPCION DE EL USUARIO EN PANTALLA 
   
   //uint8_t *re;
   
   reading_election(data_st.re,1);//REPRODUCE EN PANTALLA LA ELECCION DE EL USUARIO CON LOS PRIMEROS 11 BYTES
   reading_election(data_st.re,0);
    
    
    Ficha *ficha = (Ficha *)data_st.re;
    
    last_time(ficha);        //REPRODUCE EN PANTALL LA ULTIMA VEZ QUE EL USUARIO TUVO ACCESO AL ARCHIVO O FOLDER..
    size_file(data_st.re);        
   
     
     //SALTO HACIA LA FAT32 INICIO NO LBA RAIZ
  jump(data_st.fd,data_st.fat_init * UNIDAD); 
  read(data_st.fd,arr,UNIDAD);
  show_info(arr, UNIDAD);
  printf("**************************************************\n");
   
   
   
   
   
   
   
   
   

return 0;}
