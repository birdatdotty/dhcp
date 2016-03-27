#ifndef IP_H
#define IP_H
#include "server.h"

struct host_ip {
  unsigned int oct0:8;
  unsigned int oct1:8;
  unsigned int oct2:8;
  unsigned int oct3:8;
};

struct host_ip* host_ip_create (char *str);
char* get_ip (struct host_ip* ip);
char* get_arpa_ip (struct host_ip* ip);
int host_ip_destroy (struct host_ip* ip);

char* host_ip_dhcp_add_ip (struct host_ip* ip, struct server_setting* server, char* host);
char* host_ip_dhcp_add_arpa (struct host_ip* ip, struct server_setting* srv, char* host);

char* host_ip_dhcp_delete_ip (struct host_ip* ip, struct server_setting* server, char* host);
char* host_ip_dhcp_delete_arpa (struct host_ip* ip, struct server_setting* srv, char* host);

#endif
