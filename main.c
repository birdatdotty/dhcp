#include <stdlib.h>
#include <stdio.h>
#include <unistd.h>
#include <string.h>

#include "ip.h"
#include "server.h"
#include "config.h"

void nsupdate_add (struct host_ip *ip,
                   struct server_setting* server,
                   char* hostname)
{
  char* str;
  str = strdup (get_header_server(server));
  strcat (str, host_ip_dhcp_add_ip(ip, server, hostname));
  strcat (str, NSUPDATE_END);
  strcat (str, host_ip_dhcp_add_arpa(ip, server, hostname));
  strcat (str, NSUPDATE_END);
  
  puts (str);
  FILE *nsupdate = popen (NSUPDATE_FULL, "w"); 
  fprintf (nsupdate, str);
  fflush (nsupdate);
  pclose (nsupdate);
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
  fprintf (nsupdate, str);
  fflush (nsupdate);
  pclose (nsupdate);
//  execl (NSUPDATE_FULL, NSUPDATE, str, NULL);
}

int
main (int argc, char ** argv)
{
  struct host_ip *ip;
  char *hostname;
  struct server_setting* server;
  
  server = server_setting_create ();

  if (argv[2])
    {
      ip = host_ip_create (argv[2]);
      if (argv[3])
        hostname = argv[3];
      else
        {
          hostname = "Any_host";
          puts (hostname);
        }
    }
  else
    {
      ip = host_ip_create ("192.168.4.2");
      hostname = "Any_host";
    }
  
  char* str;
  str = strdup (get_header_server(server));
  strcat (str, host_ip_dhcp_add_ip(ip, server, hostname));
  strcat (str, host_ip_dhcp_add_arpa(ip, server, hostname));
  strcat (str, NSUPDATE_END);

  if (!strcmp (argv[1], "add"))
    nsupdate_add (ip, server, hostname);
  
  if (!strcmp (argv[1], "delete"))
    nsupdate_delete (ip, server, hostname);
  
/*  if (!strcmp (argv[1], "./add"))
    nsupdate_add (ip, server, hostname);
  
  if (!strcmp (argv[1], "./delete"))
     nsupdate_delete (ip, server, hostname);
  
*/
  host_ip_destroy (ip);
  
  return EXIT_SUCCESS;
}
