#include<stdio.h>
#include<stdlib.h>
#include "config_datos.h"
#ifndef SHOWING_DATA_H
#define SHOWING_DATA_H

void showing_data(Info_base *i){
	if(!i)return;
  for(int x = 0; x < 512;x++){
  
  printf("%02X ",i->arr_global[x]);
  if((x +1) % 16 == 0)printf("\n");
  }

}
#endif
