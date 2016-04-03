#include <stdlib.h>
#include <stdio.h>

#include "server.h"

struct server_setting* server_setting_create (char* host, char* domain)
{
  struct server_setting* server;
  server = (struct server_setting*) malloc (sizeof(struct server_setting));
  
  //server->host = "127.0.0.1";
  //server->domain = "dotty.su";
  server->host = host;
  server->domain = domain;
  
  return server;
}

char* get_header_server (struct server_setting* srv)
{
  char* str = (char*) malloc (64);
  sprintf (str,
           "server %s\n",
           srv->host);
  
  return str;
}
