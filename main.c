#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>
#include <fcntl.h>

#include <sys/stat.h>
#include <sys/types.h>

#include <err.h>
#include <errno.h>
#include <string.h>
#include <unistd.h>

#include "ip.h"
#include "server.h"
#include "config.h"

#define SIZE_STR 256

void nsupdate_send (char* str, char* domain);
void create_pipe (char* path, char* domain);
void nsupdate_add (struct host_ip *ip,
                   struct server_setting* server,
                   char* hostname)
{
  char* str;
  #ifdef DEBUG
  puts (NSUPDATE_FULL);
  #endif
  str = strdup (get_header_server(server));
  strcat (str, host_ip_dhcp_add_ip(ip, server, hostname));
  strcat (str, NSUPDATE_END);
  strcat (str, host_ip_dhcp_add_arpa(ip, server, hostname));
  strcat (str, NSUPDATE_END);
  
  #ifdef DEBUG
  puts (str);
  #endif
  FILE *nsupdate = popen (NSUPDATE_FULL, "w");
  #ifdef DEBUG
  puts ("----------------");
  puts (str);
  puts ("----------------");
  #endif
  fprintf (nsupdate, "%s", str);
  fflush (nsupdate);
  pclose (nsupdate);
  sleep (1);
//  execl (NSUPDATE_FULL, NSUPDATE, str, NULL);
}

void nsupdate_delete (struct host_ip *ip,
                      struct server_setting* server,
                      char* hostname)
{
  char* str;
  str = strdup (get_header_server(server));
  strcat (str, host_ip_dhcp_delete_ip(ip, server, hostname));
  strcat (str, host_ip_dhcp_delete_arpa(ip, server, hostname));
  strcat (str, NSUPDATE_END);
  
  FILE *nsupdate = popen (NSUPDATE_FULL, "w"); 
  fprintf (nsupdate, "%s\n", str);
  fflush (nsupdate);
  pclose (nsupdate);
//  execl (NSUPDATE_FULL, NSUPDATE, str, NULL);
}

int main (int argc, char ** argv)
{
  #ifdef DEBUG
  puts ("debug is enabled");
  #endif
  if (argc == 3)
    create_pipe (argv[1], argv[2]);
  
  printf ("Usage: %s path_to_socket domain.local\n  use: echo add/delete 1.2.3.4 hostname > path_to_socket\n\n", argv[0]);
  return EXIT_SUCCESS;
}



void create_pipe (char* path, char * domain)
{
  char* buffer = malloc (SIZE_STR);
  char* action = malloc (10);
  char* ip_addr = malloc (20);
  char* host_name = malloc (20);
  
  int status = mkfifo(path, S_IWUSR | S_IRUSR);
  
  if (status)
    if (errno != 17)
      err (-1, "Did't create pipe %s", path);
  
  while (1)
  {
    int fd = open(path, O_RDONLY);
    int status = read (fd, buffer, SIZE_STR);
    if (status)
      {
        #ifdef DEBUG
        puts (buffer);
        #endif
        nsupdate_send (buffer, domain);
        close (fd);
      }
    else
      printf ("did not open %s\n\n", path);
  }
}

void nsupdate_send (char* str, char* domain)
{
  char* action = malloc (50);
  char* ip_addr = malloc (100);
  char* host_name = malloc (200);
  
  // action
  char* n_action = strchr (str, ' ');
  memcpy (action, str, (n_action - str));
  
  // ip-address
  char* n_ip = strchr (n_action + 1, ' ');
  memcpy (ip_addr, n_action + 1, (n_ip - n_action - 1));
  
  // hostname
  char* n_hostname_space = strchr (n_ip + 1, ' ');
  if (n_hostname_space)
    *n_hostname_space = 0;
  #ifdef DEBUG
  #endif
  char* n_hostname_dot = strchr (n_ip + 1, '.');
  if (n_hostname_dot)
      *n_hostname_dot = 0;
  #ifdef DEBUG
  #endif  
  char* n_hostname_endline = strchr (n_ip + 1, '\n');
  if (n_hostname_endline)
    *n_hostname_endline = 0;
  char* n_hostname_0 = strchr (n_ip + 1, 0);
  char* n_hostname = n_hostname_0;
  
  memcpy (host_name, n_ip + 1, (host_name, n_ip + 1, (n_hostname - n_ip - 1)));
  #ifdef DEBUG
  printf ("hostname = %s\n", host_name);
  printf ("Domain: %s\n", domain);
  #endif
  struct server_setting* server;
  server = server_setting_create ("127.0.0.1", domain);
  struct host_ip* ip = host_ip_create (ip_addr);
  
  if (!strcmp (action, "add"))
    nsupdate_add (ip, server, host_name);
  
  if (!strcmp (action, "delete"))
    nsupdate_delete (ip, server, host_name);
}
