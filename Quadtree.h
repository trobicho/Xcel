#pragma once
#include "pos2D.h"
#include <vector>

template <class T, class S>
class Quadtree
{
	public:
		Quadtree(){};
		Quadtree(T *parent): m_parent(parent){};
		Quadtree(t_pos2D center, t_pos2D min, t_pos2D max):
			Quadtree(nullptr, center, min, max){};
		Quadtree(T *parent, t_pos2D min, t_pos2D max): Quadtree(parent, 
				(t_pos2D){.x = min.x + (max.x - min.x) / 2,
				.y = min.y + (max.y - min.y) / 2} , min, max){};
		Quadtree(T *parent, t_pos2D center, t_pos2D min, t_pos2D max);
		t_pos2D get_minMax(t_pos2D *min, t_pos2D *max){*min = m_min; *max = m_max; return m_center;}
		t_pos2D get_center(){return m_center;}

		void set_minMax(t_pos2D min, t_pos2D max){
			m_min = min; m_max = max;
			m_center.x = m_max.x + (min.x - max.x) / 2;
			m_center.y = m_max.y + (min.y - max.y) / 2;
		}
		void set_minMax(t_pos2D min, t_pos2D max, t_pos2D center){
			m_min = min; m_max = max; m_center = center;
		}
		static void set_maxObject(int max_obj){m_max_obj = max_obj;}
		void sons_add();
		void sons_rm();
		void obj_add(const S &obj);
		virtual void allocate_sons(){m_sons = new T[4]{((T*)this), ((T*)this), ((T*)this), ((T*)this)};}

	protected:
		T           *m_parent = nullptr;
		T           *m_sons = nullptr;
		t_pos2D     m_center;
		t_pos2D     m_min, m_max;
		S           *m_obj = nullptr;
		int         m_nbObj = 0;
		static int  m_max_obj;
};

template <class T, class S>
int Quadtree<T, S>::m_max_obj;

template <class T, class S>
Quadtree<T, S>::Quadtree(T *parent, t_pos2D center, t_pos2D min, t_pos2D max):
	m_parent(parent), m_center(center), m_min(min), m_max(max)
{
}

	template <class T, class S>
void Quadtree<T, S>::sons_add()
{
	allocate_sons();
	m_sons[0].set_minMax(m_min, m_center);
	m_sons[1].set_minMax((t_pos2D){.x = m_min.x, .y = m_center.y},
			(t_pos2D){.x = m_center.x, .y = m_max.y});
	m_sons[2].set_minMax(m_center, m_max);
	m_sons[3].set_minMax((t_pos2D){.x = m_center.x, .y = m_min.y},
			(t_pos2D){.x = m_max.x, .y = m_center.y});

	for(int i = 0; i < m_nbObj; i++)
		obj_add(m_obj[i]);
	delete [] m_obj;
}

	template <class T, class S>
void Quadtree<T, S>::sons_rm()
{
	delete [] m_sons;
}

	template <class T, class S>
void Quadtree<T, S>::obj_add(const S &obj)
{
	if(m_sons)
	{
		if(obj.x < m_center.x)
		{
			if(obj.y < m_center.y)
				m_sons[0].obj_add(obj);
			else
				m_sons[1].obj_add(obj);
		}
		else
		{
			if(obj.y < m_center.y)
				m_sons[3].obj_add(obj);
			else
				m_sons[2].obj_add(obj);
		}
	}

	else
	{
		if(m_obj == nullptr)
		{
			m_obj = new S[m_max_obj];
			m_obj[0] = obj;
			m_nbObj = 1;
		}
		else if(m_nbObj < m_max_obj)
		{
			m_obj[m_nbObj] = obj;
			m_nbObj++;
		}
		else
		{
			sons_add();
			obj_add(obj);
		}
	}
}
