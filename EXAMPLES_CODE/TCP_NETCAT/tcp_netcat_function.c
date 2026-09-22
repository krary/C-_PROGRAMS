#include "library.h"

/*1[+]DEFINIDMOS LAS CABEZERAS DE ------- IP       void init_ip()  */
/*2[+]DEFINIDMOS LAS CABEZERAS DE ------- TCP      void init_tcp   */
/*3[+]UNIMOS LAS CABEZERAS DE IP + TCP Y LO METEMOS DENTRO DE UN BUFFER  void init_buffer_header()  */

/*************************CABEZERAS PERSONALIZADAS *****************************/

void init_ip(Netcat * netcat){
//CONFIGURANDO LAS CABEZERAS IP MANUALMENTE
    //char datagram[DATAGRAM_LEN];
    //memset(datagram,0,sizeof(DATAGRAM_LEN));
    netcat->ip_hdr = (struct iphdr*)netcat->datagram;
    
    
	netcat->ip_hdr->version = 4; // IPV4;
	netcat->ip_hdr->ihl     = 5; //Tamaño de cabezera 5;
	netcat->ip_hdr->protocol = IPPROTO_TCP; // Indica que adentro va el TCP;
    netcat->ip_hdr->saddr = inet_addr("192.168.1.2"); //Ip fuente definida real o no
    netcat->ip_hdr->daddr = inet_addr("1.1.1.1");	 //IP destino;
    netcat->ip_hdr->tos = 0;                          
    netcat->ip_hdr->id = htons(1989);                 //ID de el paquete por si se fragmenta;
    netcat->ip_hdr->check = 0;                        //Variable que se usa para guardar un resultado de un algoritmo matematica para comprobar las cabezeras IP 
    netcat->ip_hdr->frag_off = 0;                     //Numero de 16 bits que contiene los offset de los fragmentos que postumamente si iran reconstruyendo .....
    netcat->ip_hdr->ttl = 64;                         //Time to live cada vez que el paquete pasa por un router el numero se resta y cuando vale cero aparece el mensaje de Time Exceeded....  
 }



 
void init_tcp(Netcat *netcat){
//CONFIGURANDO LAS CABEZERAS TCP MANUALMENTE
    netcat->tcp_hdr = (struct tcphdr*) (netcat->datagram + sizeof(struct iphdr));
    
	netcat->tcp_hdr->source = htons(12345); // Puerto de origen; 
	netcat->tcp_hdr->dest =   htons(80);    // Puerto de destino;
    netcat->tcp_hdr->syn  =    1;           //Activar la bandera SYN(Inicio de conexión )
    netcat->tcp_hdr->doff = 5;              //Tamaño de la cabezera TCP (5 X 4 = 20 bytes)
    netcat->tcp_hdr->window = htons(5840);  //Tamaño de la ventana...
    netcat->tcp_hdr->check = 0;             //Variable que se usa para guardar un resultado de un algoritmo matematica para comprobar las cabezeras TCP
    netcat->tcp_hdr->seq = 0;               //Numero de secuencia ...
    netcat->tcp_hdr->urg_ptr = 0;
    netcat->tcp_hdr->ack_seq = 0;   
    }

uint16_t checksum(uint16_t *ptr,int nbyte){
	uint32_t sum = 0;
	uint16_t answer = 0;
	while(nbyte > 1){
		sum += *(ptr++);
		nbyte-= 2;}
	if(nbyte == 1){

		*(uint8_t *)&answer = *(uint8_t *)ptr;
		sum+=answer; 
	}
	while(sum >> 16){
		sum = (sum & 0xffff) + (sum >> 16);}
	answer = ~sum;
	return answer;
	
}
    
