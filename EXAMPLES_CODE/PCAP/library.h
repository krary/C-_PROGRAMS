#include<stdio.h>
#include<stdlib.h>
#include<stdint.h>
#include<unistd.h>
#include<pcap.h>
#include<string.h>
#include<arpa/inet.h>
#include<netinet/ip.h>

#ifndef LIBRARY_H
#define LIBRARY_H
/*
    #include <stdio.h>
    #include <stdlib.h>
    #include <pcap.h>
    #include <arpa/inet.h>
    #include <netinet/ip.h>
    
    // Función callback: pcap la ejecuta automáticamente cada vez que llega un paquete
    void procesar_paquete(u_char *user_data, const struct pcap_pkthdr *pkthdr, const u_char *packet) {
        // Los primeros 14 bytes corresponden a la cabecera Ethernet
        // Apuntamos la estructura iphdr justo después de la cabecera Ethernet
        struct iphdr *ip_header = (struct iphdr *)(packet + 14);
    
        struct in_addr ip_origen;
        ip_origen.s_addr = ip_header->saddr;
    
        printf("Paquete capturado | IP Origen: %s | Tamaño: %d bytes\n", 
               inet_ntoa(ip_origen), 
               pkthdr->len);
    }
    
    int main() {
        char errbuf[PCAP_ERRBUF_SIZE];
        pcap_t *handle;
    
        // 1. Obtener el nombre de la interfaz por defecto (o puedes usar un string como "eth0")
        char *device = pcap_lookupdev(errbuf);
        if (device == NULL) {
            printf("Error al buscar interfaz: %s\n", errbuf);
            return 1;
        }
        printf("Escuchando en la interfaz: %s\n", device);
    
        // 2. Abrir la interfaz para captura en vivo
        // Argumentos: dispositivo, tamaño máximo a capturar (BUFSIZ), modo promiscuo (1 = sí), timeout en ms (1000)
        handle = pcap_open_live(device, BUFSIZ, 1, 1000, errbuf);
        if (handle == NULL) {
            printf("No se pudo abrir el dispositivo %s: %s\n", device, errbuf);
            return 1;
        }
    
        // 3. Iniciar el bucle de captura (0 indica captura indefinida)
        printf("Iniciando captura de paquetes...\n");
        pcap_loop(handle, 0, procesar_paquete, NULL);
    
        // 4. Cerrar la interfaz al finalizar
        pcap_close(handle);
        return 0;
    }


*/



#endif
