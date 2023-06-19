#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <signal.h>
#include <sys/socket.h>
#include <sys/time.h>
#include <netdb.h>
#include <arpa/inet.h>
#include <netinet/ip_icmp.h>

#define ICMP_ECHO_REQUEST 8
#define ICMP_HEADER_SIZE sizeof(struct icmphdr)
#define MAX_PACKET_SIZE 1024

// Structure to hold the necessary information for the ping program
struct ping_info {
    int sockfd;
    struct sockaddr_in addr;
    pid_t pid;
};

// Calculate the checksum for the ICMP packet
unsigned short calculate_checksum(unsigned short *ptr, int nbytes) {
    unsigned long sum;
    unsigned short oddbyte;
    unsigned short answer;

    sum = 0;
    while (nbytes > 1) {
        sum += *ptr++;
        nbytes -= 2;
    }

    if (nbytes == 1) {
        oddbyte = 0;
        *((unsigned char *)&oddbyte) = *(unsigned char *)ptr;
        sum += oddbyte;
    }

    sum = (sum >> 16) + (sum & 0xFFFF);
    sum += (sum >> 16);
    answer = (unsigned short)~sum;

    return answer;
}

// Signal handler for handling the alarm
void handle_alarm(int signum) {
    // Do nothing, just interrupt system calls
}

// Function to send an ICMP echo request
void send_ping(struct ping_info *pinfo) {
    struct icmphdr icmp_header;
    char packet[MAX_PACKET_SIZE];
    int packet_size;

    // Prepare ICMP header
    icmp_header.type = ICMP_ECHO_REQUEST;
    icmp_header.code = 0;
    icmp_header.un.echo.id = pinfo->pid;
    icmp_header.un.echo.sequence = 0;
    icmp_header.checksum = 0;
    icmp_header.checksum = calculate_checksum((unsigned short *)&icmp_header, ICMP_HEADER_SIZE);

    // Construct the packet
    memcpy(packet, &icmp_header, ICMP_HEADER_SIZE);
    packet_size = ICMP_HEADER_SIZE;

    // Send the packet
    if (sendto(pinfo->sockfd, packet, packet_size, 0, (struct sockaddr *)&pinfo->addr, sizeof(pinfo->addr)) == -1) {
        perror("sendto");
        exit(1);
    }
}

// Function to receive and process the ICMP echo reply
void receive_ping(struct ping_info *pinfo) {
    char buffer[MAX_PACKET_SIZE];
    struct sockaddr_in addr;
    socklen_t addrlen = sizeof(addr);

    if (recvfrom(pinfo->sockfd, buffer, sizeof(buffer), 0, (struct sockaddr *)&addr, &addrlen) == -1) {
        perror("recvfrom");
        exit(1);
    }

    // Process the received packet
    printf("Ping reply received from %s\n", inet_ntoa(addr.sin_addr));
}

int main(int argc, char *argv[]) {
    if (argc != 2) {
        printf("Usage: %s <hostname>\n", argv[0]);
        return 1;
    }

    char *hostname = argv[1];
    struct addrinfo hints, *res;
    struct ping_info pinfo;
    int result;

    // Set up signal handler for alarm
    signal(SIGALRM, handle_alarm);

    // Get address information for the hostname
    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_INET;
    hints.ai_socktype = SOCK_RAW;
    hints.ai_protocol = IPPROTO_ICMP;
    if (getaddrinfo(hostname, NULL, &hints, &res) != 0) {
        fprintf(stderr, "Failed to get address info for %s\n", hostname);
        return 1;
    }

    // Create socket
    pinfo.sockfd = socket(res->ai_family, res->ai_socktype, res->ai_protocol);
    if (pinfo.sockfd == -1) {
        perror("socket");
        return 1;
    }

    // Set socket options
    int ttl = 64;
    if (setsockopt(pinfo.sockfd, IPPROTO_IP, IP_TTL, &ttl, sizeof(ttl)) == -1) {
        perror("setsockopt");
        return 1;
    }

    // Store destination address
    memcpy(&pinfo.addr, res->ai_addr, res->ai_addrlen);

    // Get process ID for identification
    pinfo.pid = getpid();

    // Send and receive ping packets
    send_ping(&pinfo);
    alarm(1); // Wait for 1 second for a reply
    receive_ping(&pinfo);

    // Clean up
    freeaddrinfo(res);
    close(pinfo.sockfd);

    return 0;
}