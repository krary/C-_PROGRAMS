#include<stdlib.h>
#include<stdio.h>
#include<stdint.h>
#include<string.h>
#include<unistd.h>
#include<fcntl.h>
uint8_t arr_global[512];
uint8_t *arr_folder;
int fd;

void root(){
fd = open("/dev/sdb",O_RDONLY);
read(fd,arr_global,512);

uint8_t sectores_por_cluster;
uint16_t byte_por_sectores;
uint16_t sectores_reservados;
int num_fat;
uint32_t sectores_por_fat;
uint32_t num_cluster;

uint64_t lba_partition;
memcpy(&lba_partition,arr_global + (446+8),4);
lseek(fd,lba_partition * 512,SEEK_SET);
read(fd,arr_global,512);

memcpy(&sectores_por_cluster,arr_global + 10,1);
memcpy(&byte_por_sectores,arr_global + 11,2 );
memcpy(&sectores_reservados,arr_global + 14,2 );
memcpy(&num_fat,arr_global + 16,1 );
memcpy(&sectores_por_fat,arr_global + 36,4 );
memcpy(&num_cluster,arr_global + 44,4 );

uint64_t region_data = sectores_reservados + (num_fat * sectores_por_fat) + lba_partition; 
lseek(fd,region_data * 512,SEEK_SET);
read(fd,arr_global,512);

}
void reading_data(uint8_t *lector){

for(int x = 0; x < 512;x++){
if((x+1) % 16 == 0)printf("\n");
printf("%c",lector[x]);}

printf("\n");		
	
		
}

int main(){
root();
reading_data(arr_global);



return 0;}
