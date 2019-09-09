#pragma once
#include "Rules_totalistic.h"

class Rules_gol: public Rules_totalistic
{
	public:
		Rules_gol():Rules_totalistic(){};
		int get_nbNeigh(){return 8;}
		int get_radius(){return 1;}
		int cel_nextState(t_celNeigh &cel){
			if(cel.nbNeigh == 3 || (cel.state && cel.nbNeigh == 2)){
				return 1;
			}
			return 0;
		}
};
