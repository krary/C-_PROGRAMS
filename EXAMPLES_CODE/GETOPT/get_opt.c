 #include<stdio.h>
 #include<stdlib.h>
 #include<unistd.h>


 int main(int argc,char *argv[]){

int param;
while((param = getopt(argc,argv,"nsil:")) != 1){
	switch(param){
		case 'n': printf("[PARAMETER N]\n");break;
		case 's': printf("[PARAMETER S]\n");break;
		case 'i': printf("[PARAMETER I]\n");break;
		case 'l': printf("[PARAMETER L]\n");break;
		default : printf("NO PARAMETER HAS BEEN INTRODUCE...\n");break;
        argv++;
	   
	}break;
}
 }
