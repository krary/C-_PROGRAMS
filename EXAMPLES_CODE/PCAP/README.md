A. Desarrollo de herramientas de inspección y metadatos (SIGINT a escala local)
********************************************************************************
No necesitas ser un ejército para procesar tráfico. Puedes escribir en C un motor superrápido basado en eBPF / XDP o pcap que:
Detecte anomalías en tiempo real dentro de una red local o servidor personal.

Implemente fingerprinting de TLS (como el algoritmo JA3/JA4): analizando únicamente los bytes planos del paquete Client Hello de TLS, 
tu código puede identificar el software o la versión exacta de la aplicación que se conecta a la red sin necesidad de descifrar nada.



B. Análisis y creación de Parsers de Red robustos
*************************************************
Escribir en C tu propio parser para protocolos específicos (como reconstruir flujos TCP en memoria, analizar paquetes DNS en profundidad o 
inspeccionar tramas de videojuegos)  te dará una visión técnica que muy pocos programadores de capas altas poseen. 
Comprenderás la gestión de memoria en C a un nivel casi quirúrgico.


C. Fuzzing y búsqueda de vulnerabilidades
*****************************************
Muchos investigadores de seguridad independientes (bug hunters) trabajan completamente solos. Utilizan herramientas de fuzzing (como AFL++ o libFuzzer) 
para inyectar millones de paquetes malformados creados por sus propios scripts en C contra software existente,
 encontrando fallos de memoria (buffer overflows, out-of-bounds read) en parsers o bibliotecas de red comerciales u open source.



pcap_live
**********
Funcion con la cual inicializamos nuestro canal es decir la configuracion necesario para la captura de datos

->handle = pcap_open_live("any",BUFSIZ,1,1000,p->error_buffer);
*****************************************************************************************************************




pcap_next()
***********

pcap_next ES UNA FUNCION INICIALIZADORA DE DATOS ALGO ASI COMO la funcion  infoaddr() es decir entregamos datos y nos devuelven structuras con datos

u_char* = pcap_next(struct pcap_t*,struct pcap_pkthdr*);
****************************************************************************************************************************************************



 //////////////////////////////////////////////////////INTERPRETACION DE PAQUETES EN CRUDOS///////////////////////////////////////////////////////

[PRIMER CAPA DE DATOS DE EL PAQUETE EN CRUDO]: LA CABEZERA DE ETHERNET

 EN REDES LOS PRIMEROS 14 BYTES DE EL PAQUETE SIEMPRE TIENE UNA STRUCTURA FIJA DE TRES CAMPOS:



										1[+]MAC Destino
										2[+]MAC ORIGEN
										3[+]EtherType (Tipo de protocolo)


UN PUNTO ESENCIAL AQUI ES QUE SI YA TENEMOS UN PUNTERO  DE DATOS DE TIPO U_CHAR A LOS BYTES CRUDOS NECESITAMOS CASTEAR ESOS DATOS A UN STRUCT YA PREPARADO
PARA INTERPRETAR ESOS DATOS Y ESE STRUCT ES [ether_header] DE LA LIBRERIA : netinet/if_ether.h QUE NOS PERMITE CAPTURAR LO ANTES EXPUESTO ES DECIR MAC DESTINO MAC ORIGNE ETHERTYPE
                                            *************

LO QUE SIGUE DESPUES DE LA LECTURA CORRECTA DE LOS CAMPOS MAC ORIGEN MAC DESTINO Y PROTOCOLO SIGUE LOS BYTES CRUDOS CORRESPONDIENTES A LOS IP DE LAS MAQUINAS
PARA ELLO ES DECIR PARA INTERPETAR LOS DATOS TENEMOS EL STRUCT [iphdr] DE LA LIBRERIA : netinet/ip.h>
															   *******


CON LOS CAMPOS EXPUESTOS DE iphdr PODEMOS SABER O CONOCER LA ETIQUETA DE EL PROTOCOLO DE EL PAQUETE CAPTURADO EJEM:

1  TIENE EL VALOR DE IPROTO_ICMP
6  TIENE EL VALOR DE TCP
17 TIENE EL VALOR DE UDP
          NOTA: LOS VALORES ANTES EXPUESTOS EN EL CAMPO DE EL STRUCT iphdr->protocol NO NECESITAN NINGUN CASTING
          O FUNCION AUXILIAR YA QUE ESO VALORES TIENE EL VALOR DE UN BYTE ES DECIR uint8_t ......
          
RESUMEN:

/*u_char *paquete_capturado*/
-----------------------------------------------------------------------------
pcap_pkthdr -> caplen   byte capturados                                     -
pcap_pkthdr -> len      numeros de bytes que realmente habian en la red     -
u_char *                puntero a memoria con los datos capturados          -
-----------------------------------------------------------------------------

/*struct ether_header*/
-----------------------------------------------------------------------------
struct ether_header * -> dhost   [index] MAC de destino                     -  
struct ether_header * -> shost   [index] MAC de origen                      -  
struct ether_header * -> type    que tipo de cabezera viene a continuacion  -  
-----------------------------------------------------------------------------

/*struct iphdr*/
-----------------------------------------------------------------------------
struct ipheader * -> daddr   IP de destino                                  -  
struct ipheader * -> saddr   IP de origen                                   -  
struct ipheader * -> protocol    que tipo de cabezera viene a continuacion  -  
-----------------------------------------------------------------------------



















                               
