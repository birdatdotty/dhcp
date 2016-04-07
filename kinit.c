#include <stdlib.h>

#include "config.h"
#include "kinit.h"

int init_comand ()
{
//  system (INIT_CMD);
  FILE *kinit_cmd = popen (KINIT_CMD, "w");
  fprintf (kinit_cmd, "%s", KINIT_PWD);
  fflush (kinit_cmd);
  pclose (kinit_cmd);
}
