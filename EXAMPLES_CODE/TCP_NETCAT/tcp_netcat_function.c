#include "library.h"

/*1[+]DEFINIDMOS LAS CABEZERAS DE ------- IP       void init_ip()  */
/*2[+]DEFINIDMOS LAS CABEZERAS DE ------- TCP      void init_tcp   */
/*3[+]UNIMOS LAS CABEZERAS DE IP + TCP Y LO METEMOS DENTRO DE UN BUFFER  void init_buffer_header()  */

/*************************CABEZERAS PERSONALIZADAS *****************************/

void init_ip(struct iphdr *i){
//CONFIGURANDO LAS CABEZERAS IP MANUALMENTE
	i->version = 4; // IPV4;
	i->ihl     = 5; //Tamaño de cabezera 5;
	i->protocol = IPPROTO_TCP; // Indica que adentro va el TCP;
    i->saddr = inet_addr("192.168.1.2"); //Ip fuente definida real o no
    i->daddr = inet_addr("1.1.1.1");	 //IP destino;
 }
void init_tcp(struct tcphdr *t){
//CONFIGURANDO LAS CABEZERAS TCP MANUALMENTE
	t->source = htons(12345); // Puerto de origen; 
	t->dest =   htons(80);    // Puerto de destino;
    t->syn  =    1;            //Activar la bandera SYN(Inicio de conexión )
    }

void init_datagram(char *d){
memset(d,0,DATAGRAM_LEN);
	
}
