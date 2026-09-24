BEFORE TO SEND BYTES BY THE NETWORK WE NEED TO COONVERT OR TRANSFORM OF BIG ENDIAN TO LITTLE ENDIAN
SO THIS IS THE MAIN FUNCION OF THE FUNCTIONS CALLED htons IN C

SO WE GOT A DIFFERENT FORMAT I MEAN TO TRANSFORM TO SPECIFIC VALUE TO ANOTHER HEADING THAT OCCUR TOW THINGS
A) A TYPE NUMBER LIKE INTEGER OR MABY SHORT OR LONG NUMBER INTO A BYTE FORMAT
B) THEN THE BIG ENDIAN (KNOWN TOO Network Byte Order) TRANSFORM INTO LITTLE ENDIAN


WHEN THE COMPUTER SAVE DATA IN BYTE FORMAT THAT ITS KNOWN LIKE:_ Host Byte Order

hotons (host to network short) REFERRING THE NAME OF _Host Byte Order 
htonl  (host to network long)  REFERRING THE NAME OF _Host Byte Order

STRUCTS_ addrinfo
*****************
sruct addrinfo _THIS STRUCT ITS AN INVENTION ACTUAL WHERE HIS MAIN USE IS PREPARE ANOTHER KIND OF STRUCTS
SO TO INITILIZIE THE STRUCT WE USE THE FUNCTION getaddrinfo()
	
struct addrinfo {
		int ai_flags;		// AI_PASSIVE, AI_CANONNAME, etc.
		
		int ai_family;		// AF_INET, AF_INET6, AF_UNSPEC
		
        int ai_socktype;    // SOCK_STREAM, SOCK_DGRAM
        
        int ai_protocol;    // utilice 0 para "cualquiera"
        
		size_t ai_addrlen;  // tamaño de ai_addr en bytes
		
  		struct sockaddr *ai_addr; // struct sockaddr_in o _in6
  		
		char *ai_canonname; // nombre de host canónico completo
		
		struct addrinfo *ai_next //LINKED LIST IF WE WANT TO GET SOME INFO 
}
*******************************************************************************************

                        ^ 
STRUCTS_ sockaddr ______| 
*****************
_THIS STRUCT APPEAR LIKE A VARIABLE POINTER OF STRUCT addrinfo AND ITS MAIN PROPOSE IS
STABLISH AND DEFINE VALUE TO RELATIONSHIP WITH SOCKETS 

struct sockaddr {
		unsigned short sa_family  //familia de direcciones, AF_xxx;

        char sa_data[14]          // 14 bytes de dirección de protocolo
}
*******************************************************************************************

STRUCTS_ sockaddr_in 
********************
_THIS STRUCT WAS MADE TO DEAL WITH THE STRUCT sockaddr AND THE BIG DEAL HERE ITS THAT WHEN WE PASS 
THE ARGUMENTE INTO THE FUNCTION getaddrinfo WE CAN MAKE A CAST TO THIS ONE INTO ANOTHER AT THE ULTIMATE INSTANCE

struct sockaddr_in {
		short int sin_family;    // Familia de direcciónes, AF_INET
        unsigned short int sin_port; // Número de puerto.
        struct in_addr sin_addr;     // Dirección de Internet
 		unsigned char sin_zero[8]; // Mismo tamaño que struct sockaddr
};
********************************************************************************************


                      ^ 
STRUCTS_ in_addr  ____|
****************
THIS STRUCT PIONT REFERENCSE AT THE FOUR BYTES OF THE IP NUMBER
// (sólo IPv4; véase struct in6_addr para IPv6)
// Dirección de Internet (una estructura por razones históricas)
struct in_addr {
		uint32_t s_addr; // es un int de 32 bits (4 bytes)
};
********************************************************************************************


inet_pton()
***********
THIS FUNCTION CALLED : PRESENTATION TO NETOWRK IS FUNCTION ITS CONVERT A FORMAT STRING NUMBER THAT 
WE NEED TO CONVERT INTO THE FORMAT IP ADDRESS AND THE PASS THE ARGUMENTES INTO THE STRUCT add_in SO

struct sockaddr_in sa; // IPv4
struct sockaddr_in6 sa6; // IPv6

inet_pton(AF_INET, "10.12.110.57", &(sa.sin_addr)); // IPv4
inet_pton(AF_INET6, "2001:db8:63b3:1::3490", &(sa6.sin6_addr)); // IPv6
*********************************************************************************************



inet_ntop()
**********
THIS FUNCTION ITS CONVERT A FORMAT NUMBER ADDRESS INTO  A CHAR OF CHARCTER TO MAKE IT READEBLE ITS LIKE
THE OPOSITE TO THE FUNCTION inet_pton()

// IPv4:
char ip4[INET_ADDRSTRLEN];		// espacio para la cadena IPv4

struct sockaddr_in sa;          // pretender que esto se carga con algo

inet_ntop(AF_INET, &(sa.sin_addr), ip4, INET_ADDRSTRLEN);

printf("The IPv4 address is: %s\n", ip4);

// IPv6:

char ip6[INET6_ADDRSTRLEN];    // espacio para la cadena IPv6

struct sockaddr_in6 sa6;       // pretender que esto se carga con algo

inet_ntop(AF_INET6, &(sa6.sin6_addr), ip6, INET6_ADDRSTRLEN);

printf("The address is: %s\n", ip6);
********************************************************************************************


NAT : NETWORK ADDRESS TRANSLATION  


int getaddrinfo 
**************

THIS FUNCTION IF WE INTRODUCE SOME DATA INSIDE OF IT WILL RETURN A LINKED LIST AS RESULT

int getaddrinfo(
	const char *node,		//THE NAME OF THE HOST OR IP TO CONNECT TO  "e.g www.example.com";
	const char *service,    //THIS CAN BE A NUMBER OF ANY PORT OR SEVICE LISTED INC /etc/services "e.g http or  ftp";
	const struct addrinfo *hints,  //THIS IS THE STRUCT THAT YOU FILLED BEFORE WITH RELEVANT INFORMATION
    const struct addrinfo **res,   //AND THIS IS THE LINKED LIST WITH WITH ALL THE INFORMATION OF THE NETWORK
);
********************************************************************************************


TENGO QUE PENSAR COMO EN PIEZAS DE PUZZLES PERO MAS SIMETRICOS ES DECIR 

QUIERO A SER UN SERVIDOR 
1[+]RELLENAR UNA PLANILLA CON INFORMACION PERTINENTE ES DECIR VARIABLE COMO 
addrinfo.ai_family (AF_INET , AF_UNSPEC ETC) NECESITAN SER DEFINIDAS
addrinfo.ai_socktype(DEFINIENDO EL TIPO DE CANAL OSEA EL MODO EN QUE SE VAN A TRANSMITIR LOS DATOS
VALE ESTO SERIA LO ESENCIAL AHORA EL SISTEMA ME DEVUELVE A CAMBIO UNA RESPUESTA  O DIGAMOS UN TIPO DE RESPUESTA
SEGUN MIS VALORES QUE SE GUARDAN DENTRO DE OTRO STRUCT DE LA MISMA CLASE Y MUY GENERICO 

2[+]OBTENER INFORMACION RELEVANTE ES DECIR LEER LA LISTA ENLAZADA DE LA VARIABLE ai_next QUE ME DEVUELVE EL 
SISTEMA CON struct addinfo COMO RESPUESTA PARA ELLO SE NECESITA VARIOS PASOS PERO ANTES DE TODO
TENER CLARO QUE ES LO QUE QUIERO OBTENER : OBJETIVO IP 

PARA ELLO SE CREA UNA TERCERA VARIABLE DE TIPO addrinfo  QUE PODAMOS IGUALARLA AL PUNTERO DE LA LISTA ENLAZADA
DE ADDR Y LUEGO A CADA LLAMADA PUES HACER LO MISMO ES DECIR LO QUE EQUIVALE EN UN BUCLE FOR A X++ ESO SERIA
ALGO COMO p->ai_next 

LUEGO DENTRO DE EL MISMO BUCLE FOR SE HARIA ALGO COMO OBTENER LA MISMA DIRECCION DE EL PUNTERO P QUE A CADA LLAMADA
O CICLO VA CAMBIANDO PERO ESTO POR QUÉ ?

BUENO SOSPECHO QUE ES POR UNA VARIABLE LLAMADAA sin_addr ES DECIR:
DENTRO DE NUESTRO P ES DECIR DE NUESTRO NODO P SE ENCUETRA UNA VARIABLE DE TIPO SOCKADDR ES DECIR ESTE STRUCT
SIN ENTRAR EN DETALLES DE SUS CAMPOS ES PERMUTABLES PO OTRO STRUCT DE TIPO sockaddr_in ES DECIR ESTO ES 
PRACTICABLE Y AL PARECER ES LA CLAVE DE TODO POR LO MENOS DE LO QUE ESTAMOS VIENDO:
struct sockaddr_in * ptr = (struct sockaddr_in*)p.ai_addr (SIENDO LA VARIABLE ai_addr DE TIPO sockaddr )
ES DECIR sockaddr_in = sockaddr;

AHORA PORQUE ES TAN IMOPRTANTE SO IMPORTANT la variable ai_addr BUENO EXISTE UN CAMPO DENTRO DE EL STRUCT
sockaddr_in LLAMADO sin_addr QUE CAMPO ES ESTE ? BUENO EN DEFINICION DE EL STRUCT sockaddr_in SE DEFINE COMO:
                               struct in_addr sin_addr;     // Dirección de Internet
OSEA QUE ES OTRO STRUCT DE TIPO struct in_addr
PREGUNTA QUE CONTIENE ESTE CAMPO QUE ES TAN VALIOSO?
BUNEO DENTRO TIENE ALGO VALIOSO QUE ES POR LO QUE ESTAMOS AQUI ES DECIR :
UN VALOR DE 32 BITS EL CUAL USAMDO PARA PASARLO COMO ARGUMENTO PARA OBTENER INFORMACION LEGIBLE
ACERCA DE EL IP EN FORMATO COMO LO ANTES DICHO LEGIBLE 
Y ESTO LO HACEMOS CON UNA FUNCION LLAMADA inet_ntop (NOTA NO LE PASAMOS EL VALOR EN SI SI NO 
QUE SOLO LA DIRECCION DE MEMORIA O PUNTERO DE EL STRUCT in_addr )


RESUMEN :
P[nodo]----> = ai_next(struct addrinfo) ----> ai_addr(struct sockaddr) -----> (struct sockaddr_in[cast])-----> sin_addr(struct in_addr) 
ENTONCES EN ESTE ENJAMBRE DE STUCTS TENEMOS 
addrinfo 
sockaddr = sockaddr_in
in_addr


NECESISTO DEFINIR ADDRINFO
 
