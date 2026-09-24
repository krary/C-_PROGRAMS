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
		
		struct addrinfo *ai_next
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


