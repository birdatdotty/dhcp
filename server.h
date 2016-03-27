#ifndef SERVER_H
#define SERVER_H

struct server_setting {
  char* host;
  char* domain;
};

struct server_setting* server_setting_create ();
char* get_header_server (struct server_setting* srv);

#endif
