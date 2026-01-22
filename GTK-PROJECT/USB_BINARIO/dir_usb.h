#include<stdio.h>
#include<dirent.h>
#include<sys/stat.h>


char **dir_usb(){
	double tam_g;
	int index = 0;
	int capacity = 10;
	char **elementos = malloc(capacity * sizeof(char*));
	struct dirent *de;
	DIR *dr = opendir("/sys/class/block");
	if(dr == NULL){
	printf("Couldn`t open the directory block..\n");
	return NULL;
    }
    //printf("Devices of usb connected..\n");
    while((de = readdir(dr)) != NULL){
		if(strncmp(de->d_name, "loop",4) == 0){
		continue;}
		char path[512];
		snprintf(path,sizeof(path),"/sys/class/block/%s/partition",de->d_name);
		if(access(path,F_OK) == -1){
			
			snprintf(path,sizeof(path),"/sys/class/block/%s",de->d_name);
			if(strncmp(de->d_name , ".",1)==0){
				continue;
				}
			   	
			   char path_size[512];
			   snprintf(path_size,sizeof(path_size),"/sys/class/block/%s/size",de->d_name);
			   FILE *f = fopen(path_size,"r");
			   if(f){
				   uint64_t tam;
				   fscanf(f,"%lu",&tam);
				   tam_g = (tam * 512) / (1024 * 1024 * 1024);
				   
			   	  
			   //printf("[%d]/dev/%s[%.2f GB]\n",index,de->d_name,tam_g);
			   }
			   if(index == 0){elementos[index++] = strdup("CHOICE YOUR USB...");}
			   char pat_return[512];
			   snprintf(pat_return,sizeof(pat_return),"/dev/%s %.2f GB",de->d_name,tam_g);
			
			   if(index >= capacity - 1){
				   capacity *= 2;
				   char **tmp = realloc(elementos,capacity * sizeof(char*));
				   elementos = tmp;
				   
				   }
			
			   elementos[index++] = strdup(pat_return);
			
			}
		
		}
	
	closedir(dr);
	elementos[index] = NULL;
	return elementos;
	}
