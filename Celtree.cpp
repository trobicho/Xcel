#include "Celtree.h"
#include "stdio.h"

Celtree* Celtree::calc_nextGen()
{
	if(m_parent != nullptr)
		return nullptr;
	Celtree *treeNG = new Celtree(nullptr, m_center, m_min, m_max);
	treeNG->set_rules(m_rules);
	treeNG->set_maxObject(m_max_obj);
	parse(treeNG, 0, 0);
	return treeNG;
}

int Celtree::parse(Celtree *treeNG, int sens, int nT)
{
    int tagIn[4], ret = -1;

	if(m_sons)
	{
		tagIn[0] = m_sons[0].parse(treeNG, sens, nT);
		tagIn[1] = m_sons[1].parse(treeNG, sens, tagIn[0]);
		tagIn[2] = m_sons[2].parse(treeNG, sens, (m_adjCenter)?(tagIn[0]==-1?tagIn[1]:tagIn[0]):tagIn[1]);
        for(int i = 0; ret == -1 && i < 3; i++){ret = tagIn[i];}
		tagIn[3] = m_sons[3].parse(treeNG, sens, ret);
        if(ret == -1)
            ret = tagIn[3];
        if(ret != -1)
            parse_adjCel(treeNG, ret);
	}
	else if(m_nbObj)
		return sheet_parse(treeNG, nT);
	return ret;
}

int Celtree::sheet_parse(Celtree *treeNG, int nT)
{
	t_celNeigh celNeigh[m_nbObj * (m_rules->get_nbNeigh() + 1)];
	int nbCelNeigh = m_rules->put_celNeigh(m_obj, m_nbObj, celNeigh);
	int newNeighTag = m_adjCel->size();
	int i, s;
	s_cel celN;

    if(nT != -1)
    {
        for(i=0; i < nbCelNeigh; i++)
        {
			celNeigh[i].adj = adj_test(celNeigh[i]);
            if(celNeigh[i].adj == ADJ_IN || celNeigh[i].adj == ADJ_IN_OUT)
            {
                int r = verif_adj(celNeigh[i], nT);
                if(m_debugLevel >= 2)
                    printf("(%d, %d) %d\n", celNeigh[i].x, celNeigh[i].y, r);
            }
        }
    }
	for(i = 0; i < nbCelNeigh; i++)
	{
		if(nT == -1)
			celNeigh[i].adj = adj_test(celNeigh[i]);
		if(celNeigh[i].adj == ADJ_NO && (s = m_rules->cel_nextState(celNeigh[i])))
		{
			celN = celNeigh[i];
			celN.state = s;
			treeNG->obj_add(celN);
		}
        else if(celNeigh[i].adj && celNeigh[i].adj!=ADJ_DEL)
        {
            m_adjCel->push_back(celNeigh[i]);
		}
	}

    if(newNeighTag != m_adjCel->size())
        return newNeighTag;
    else
        return -1;
}

void Celtree::parse_adjCel(Celtree *treeNG, int nT)
{
    int s, i, a, d, b_outIn=0;
	s_cel celN;

    //------------C'EST PAS TOP TOUS SA
    for(i=nT; i<m_adjCel->size(); i++)
    {
        if(m_adjCel->at(i).adj == ADJ_IN || m_adjCel->at(i).adj == ADJ_IN_OUT)
        {
            for(a=i+1; a<m_adjCel->size(); a++)
            {
                if((m_adjCel->at(a).adj == ADJ_IN || m_adjCel->at(a).adj == ADJ_IN_OUT) && m_adjCel->at(i).pos() == m_adjCel->at(a).pos())
                {
                    m_adjCel->at(a).adj = ADJ_DEL;
                    m_adjCel->at(i).nbNeigh += m_adjCel->at(a).nbNeigh;
                    m_adjCel->at(i).state = (m_adjCel->at(a).state>m_adjCel->at(i).state)?m_adjCel->at(a).state:m_adjCel->at(i).state;
                    if(m_debugLevel>=2)
                        printf("tattoutesta (%d, %d)\n", m_adjCel->at(i).x, m_adjCel->at(i).y);
                }
            }
        }
    }
    //---------------------------------
    for(i=nT; i<m_adjCel->size(); i++)
    {
        if(m_adjCel->at(i).adj==ADJ_IN)
        {
			if(s = m_rules->cel_nextState(m_adjCel->at(i)))
			{
				celN = m_adjCel->at(i);
				celN.state = s;
				treeNG->obj_add(celN);
                if(m_debugLevel>=1)
                    printf("add (%d, %d) (neigh=%d, state=%d)\n", m_adjCel->at(i).x, m_adjCel->at(i).y, m_adjCel->at(i).nbNeigh, m_adjCel->at(i).state);
            }
            else
            {
                if(m_debugLevel>=2)
                    printf("(%d, %d) to del\n", m_adjCel->at(i).x, m_adjCel->at(i).y);
            }
            m_adjCel->at(i).adj=ADJ_DEL;
        }
        else if(m_adjCel->at(i).adj==ADJ_IN_OUT)
            m_adjCel->at(i).adj=ADJ_OUT;
        if(m_adjCel->at(i).adj==ADJ_OUT)
        {
            if(m_debugLevel>=2)
                printf("out (%d, %d)", m_adjCel->at(i).x, m_adjCel->at(i).y);
            m_adjCel->at(i).adj = adj_test(m_adjCel->at(i));
            if(m_adjCel->at(i).adj==ADJ_IN)
            {
                if(m_debugLevel>=2)
                    printf(" to in\n");
                b_outIn=1;
            }
            else
            {
                if(m_debugLevel>=2)
                    printf("\n");
            }
        }
    }
    for(i=nT, d=0; i<m_adjCel->size(); i++)
    {
        if(m_adjCel->at(i).adj == ADJ_DEL)
			m_adjCel->erase(m_adjCel->cbegin() + i);
		/*
        if(m_adjCel->at(i).adj == ADJ_DEL)
            d++;
        else if(d)
        {
            for(a=i-d; a < m_adjCel->size()-d; a++)
            {
                //m_adjCel->at(a) = m_adjCel[a+d];
            }
            //m_adjCel->size()-=d;
            d=0;
        }
		*/
    }
}

e_adj Celtree::adj_test(t_pos2D pos) //IN R a faire
{
    if(pos.x == m_min.x || pos.x == m_min.x-1 || pos.x == m_max.x-1 || pos.x == m_max.x\
        || pos.y == m_min.y || pos.y == m_min.y-1 || pos.y == m_max.y-1|| pos.y == m_max.y)
    {
		if(m_parent)
		{
			t_pos2D fMin, fMax, fCenter;
			fCenter = m_parent->get_minMax(&fMin, &fMax);
			if(pos.x == fMin.x || pos.x == fMax.x-1 || pos.y == fMin.y || pos.y == fMax.y-1\
					|| pos.x == fMin.x-1 || pos.x == fMax.x || pos.y == fMin.y-1 || pos.y == fMax.y)
			{
				if((pos.x != fMin.x-1 && pos.x != fMax.x && pos.y != fMin.y-1 && pos.y != fMax.y)\
						&& (pos.x == fCenter.x || pos.x == fCenter.x-1 || pos.y == fCenter.y || pos.y == fCenter.y-1))
					return ADJ_IN_OUT;
				return ADJ_OUT;
			}

			if((pos.x == fCenter.x || pos.x == fCenter.x-1) && (pos.y == fCenter.y || pos.y == fCenter.y-1))
				m_parent->set_adjCenter(true);
		}
		return ADJ_IN;
	}
	return ADJ_NO;
}

int Celtree::verif_adj(t_celNeigh &celNeigh, int neighTag)
{
	int i, r=0;
	for(i = neighTag; i < m_adjCel->size(); i++)
	{
		if(m_adjCel->at(i).adj != ADJ_DEL && celNeigh.x == m_adjCel->at(i).x && celNeigh.y == m_adjCel->at(i).y)
		{
			celNeigh.state=(m_adjCel->at(i).state>celNeigh.state)?m_adjCel->at(i).state:celNeigh.state;
			celNeigh.nbNeigh+=m_adjCel->at(i).nbNeigh;
			m_adjCel->at(i).adj=ADJ_DEL;
			return m_adjCel->at(i).nbNeigh;
		}
	}
	return 0;
}
