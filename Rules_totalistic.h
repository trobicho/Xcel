#pragma once
#include "Rules.h"

class Rules_totalistic: public Rules
{
	public:
		Rules_totalistic(): Rules(){};
		int get_nbNeigh(){return m_nbNeigh;}
		int get_radius(){return m_radius;}
		int put_celNeigh(t_cel *cel, int nbCel, t_celNeigh *celNeigh);

	private:
		int m_radius = 1;
		int m_nbNeigh = 8;
};
