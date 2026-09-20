#include "library.h"

/*1[+]DEFINIDMOS LAS CABEZERAS DE ------- IP       void init_ip()  */
/*2[+]DEFINIDMOS LAS CABEZERAS DE ------- TCP      void init_tcp   */
/*3[+]UNIMOS LAS CABEZERAS DE IP + TCP Y LO METEMOS DENTRO DE UN BUFFER  void init_buffer_header()  */

/*************************CABEZERAS PERSONALIZADAS *****************************/

void init_ip(struct iphdr *i){
//CONFIGURANDO LAS CABEZERAS IP MANUALMENTE
    char datagram[DATAGRAM_LEN];
    memset(datagram,0,sizeof(DATAGRAM_LEN));
    i = (struct iphdr*)datagram;
    
	i->version = 4; // IPV4;
	i->ihl     = 5; //Tamaño de cabezera 5;
	i->protocol = IPPROTO_TCP; // Indica que adentro va el TCP;
    i->saddr = inet_addr("192.168.1.2"); //Ip fuente definida real o no
    i->daddr = inet_addr("1.1.1.1");	 //IP destino;
    i->tos = 0;                          
    i->id = htons(1989);                 //ID de el paquete por si se fragmenta;
    i->check = 0;                        //Variable que se usa para guardar un resultado de un algoritmo matematica para comprobar las cabezeras IP 
    i->frag_off = 0;                     //Numero de 16 bits que contiene los offset de los fragmentos que postumamente si iran reconstruyendo .....
    i->ttl = 64;                         //Time to live cada vez que el paquete pasa por un router el numero se resta y cuando vale cero aparece el mensaje de Time Exceeded....  
 }



 
void init_tcp(struct tcphdr *t){
//CONFIGURANDO LAS CABEZERAS TCP MANUALMENTE
    t = (struct tcphdr*) (datagram + sizeof(struct iphdr));
    
	t->source = htons(12345); // Puerto de origen; 
	t->dest =   htons(80);    // Puerto de destino;
    t->syn  =    1;           //Activar la bandera SYN(Inicio de conexión )
    t->doff = 5;              //Tamaño de la cabezera TCP (5 X 4 = 20 bytes)
    t->window = htons(5840);  //Tamaño de la ventana...
    t->check = 0;             //Variable que se usa para guardar un resultado de un algoritmo matematica para comprobar las cabezeras TCP
    t->seq = 0;               //Numero de secuencia ...
    t->urg_ptr = 0;
    t->ack_seq = 0;   
    }


    
