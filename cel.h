#pragma once
#include "pos2D.h"

typedef struct s_cel: public s_pos2D
{
	s_cel(){};
	s_cel(int x, int y, int s): s_pos2D(x, y), state(s){};
	t_pos2D pos(){return (s_pos2D){x, y};}
	int state;
}t_cel;

typedef enum {ADJ_NO=0, ADJ_IN, ADJ_OUT, ADJ_IN_OUT, ADJ_DEL}e_adj;
typedef struct s_celNeigh: public s_cel
{
	int nbNeigh;
	e_adj adj;
}t_celNeigh;

