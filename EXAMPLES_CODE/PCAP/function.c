#include "library.h"


// ABRIR LA INTERFAZ 



                         /*open_interface*/
//===============================================================================
void open_interface(PCap_info* p){
	p->handle = pcap_open_live("any",BUFSIZ,1,1000,p->error_buffer);
	if(p->handle==NULL){printf("ERROR %s\n",p->error_buffer);return;}

	printf("[EXIT] THE PROGRAM HAS CONNECT WITH THE KERNEL\n");
	
}
//================================================================================




                         /*capture_packet*/
//===================================================================================
void capture_packet(PCap_info *p){
	p->packet = pcap_next(p->handle,&p->header);
	if(p->packet == NULL){
		printf("THE PROGRMA CANNOT CAPTURE ANY PACKET PLEASE TRY LATTER...\n");return ;}
	else{
		printf("[+]NUMERO DE BYTE CAPTURADOS : %d\n",p->header.caplen);
		printf("[+]NUMERO REAL DE BYTES EN EL CABLE : %d\n",p->header.len);


	for(size_t x = 0; x < p->header.caplen; x++){
		printf("%02X ",p->packet[x]);
		if((x + 1) % 16 == 0)printf("\n");}}
printf("\n");}

//=====================================================================================



                    /*reading_packet_ascii*/
//=====================================================================================
void reading_packet_ascii(PCap_info *p){
	for(size_t x = 0; x < p->header.caplen;x++){
		u_char c = p->packet[x];
		if(isprint(c)){
			printf("%c",c);}
		else{
			printf(".");
		}
	}
printf("\n");
}
