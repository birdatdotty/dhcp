#include <stdlib.h>
#include <stdio.h>

#include "config.h"
#include "kinit.h"

int init_comand ()
{
//  system (INIT_CMD);
  FILE *kinit_cmd = popen (KINIT_CMD, "w");
  puts (KINIT_CMD);
  puts (KINIT_PWD);
  fprintf (kinit_cmd, "%s\n", KINIT_PWD);
  fflush (kinit_cmd);
  pclose (kinit_cmd);
}
