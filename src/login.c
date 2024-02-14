#ifdef HAVE_CONFIG_H
# include<config.h>
#endif

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "login.h"
#include<gtk/gtk.h>
int verif_login(char nom[],char pw[])
{
  if((strcmp(nom,"admin")==0)&&(strcmp(pw,"1234")==0))
		return 1;
	
	

}
