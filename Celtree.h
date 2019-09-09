#pragma once
#include "Quadtree.h"
#include "cel.h"
#include "Rules.h"

class Celtree: public Quadtree<Celtree, t_cel>
{
	public:
		Celtree(Celtree *parent = nullptr): Quadtree<Celtree, t_cel>(parent){init();}
		Celtree(Celtree *parent, t_pos2D min, t_pos2D max): Quadtree<Celtree, t_cel>(parent, min, max){init();}
		Celtree(Celtree *parent, t_pos2D center, t_pos2D min, t_pos2D max):
			Quadtree<Celtree, t_cel>(parent, center, min, max){init();}
		~Celtree(){if(m_parent == nullptr){delete m_adjCel;}}
		void init(){if(m_parent == nullptr){m_adjCel = new std::vector<t_celNeigh>;} 
			else {m_adjCel = m_parent->get_adjVec(); m_rules = m_parent->get_rules();}}

		Celtree* calc_nextGen();

		Celtree	*get_sons(){return m_sons;}
		t_cel	*get_cel(int *c = nullptr){if(c){*c = m_nbObj;} return m_obj;}
		Rules	*get_rules(){return m_rules;}
		void	set_adjCenter(bool adjC){m_adjCenter = adjC;}
		void	set_rules(Rules *rules){m_rules = rules;}
		std::vector<t_celNeigh>	*get_adjVec(){return m_adjCel;}

	private:
		int		parse(Celtree *treeNG, int sens, int nT);
		int		sheet_parse(Celtree *treeNG, int nT);
		void 	parse_adjCel(Celtree *treeNG, int nT);
		int		verif_adj(t_celNeigh &celNeigh, int neighTag);
		e_adj	adj_test(t_pos2D pos);

		bool	m_adjCenter = false;
		int		m_debugLevel = 0;

		std::vector<t_celNeigh>	*m_adjCel = nullptr;
		Rules	*m_rules = nullptr;
};
