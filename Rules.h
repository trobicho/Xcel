#pragma once
#include "cel.h"

class Rules
{
	public:
		Rules(){};
		virtual int get_nbNeigh() = 0;
		virtual int get_radius() = 0;
		virtual int put_celNeigh(t_cel *cel, int nbCel, t_celNeigh *celNeigh) = 0;
		virtual int cel_nextState(t_celNeigh &cel) = 0;
};
