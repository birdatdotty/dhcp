#include <stdlib.h>
#include <stdio.h>

#include "ip.h"
#include "server.h"

struct host_ip*
host_ip_create (char *str)
{
  struct host_ip *new_ip;
  new_ip = (struct host_ip *) malloc ( sizeof(struct host_ip) );
  unsigned int oct0, oct1, oct2, oct3;
  sscanf (str,
          "%i.%i.%i.%i",
          &oct0,
          &oct1, 
          &oct2,
          &oct3);
  
  new_ip->oct0 = oct0;
  new_ip->oct1 = oct1;
  new_ip->oct2 = oct2;
  new_ip->oct3 = oct3;
  
  return new_ip;
}

char* get_ip (struct host_ip* ip)
{
  char* str = (char*) malloc (128);
  sprintf (str, "%d.%d.%d.%d",
           ip->oct0,
           ip->oct1,
           ip->oct2,
           ip->oct3);
  
  return str;
}

char* get_arpa_ip (struct host_ip* ip)
{
  char* str = (char*) malloc (128);
  sprintf (str, "%d.%d.%d.%d.in-addr.arpa.",
           ip->oct3,
           ip->oct2,
           ip->oct1,
           ip->oct0);
  
  return str;
}

int host_ip_destroy (struct host_ip* ip)
{
  free (ip);
}

char*
host_ip_dhcp_add_ip (struct host_ip* ip, struct server_setting* srv, char* host)
{
  char* server = srv->host;
  char* domain = srv->domain;
  int time = 3600;
  char* str_ip = get_ip(ip);
  
  char* str;
  str = (char*) malloc (256);
  sprintf (str,
           "update delete %s.%s %i A\n"
           "update add %s.%s %i A %s\n",
           host,
           domain,
           time,
           host,
           domain,
           time,
           str_ip);
  return str;
}

char*
host_ip_dhcp_delete_ip (struct host_ip* ip, struct server_setting* srv, char* host)
{
  char* server = srv->host;
  char* domain = srv->domain;
  int time = 3600;
  char* str_ip = get_ip(ip);
  
  char* str;
  str = (char*) malloc (256);
  sprintf (str,
           "update delete %s.%s %i A\n",
           host,
           domain,
           time);
  return str;
}

char*
host_ip_dhcp_add_arpa (struct host_ip* ip, struct server_setting* srv, char* host)
{
  char* server = srv->host;
  char* domain = srv->domain;
  int time = 3600;
  char* str_ptr = get_arpa_ip(ip);
  
  char* str;
  str = (char*) malloc (256);
  sprintf (str,
           "update delete %s %i PTR\n"
           "update add %s %i PTR %s.%s\n",
           str_ptr,
           time,
           str_ptr,
           time,
           host,
           domain);
  
  return str;
}

char*
host_ip_dhcp_delete_arpa (struct host_ip* ip, struct server_setting* srv, char* host)
{
  char* server = srv->host;
  char* domain = srv->domain;
  int time = 3600;
  char* str_ptr = get_arpa_ip(ip);
  
  char* str;
  str = (char*) malloc (256);
  sprintf (str,
           "update delete %s %i PTR\n",
           str_ptr,
           time);
  
  return str;
}
