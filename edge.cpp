/*=============================================================================
 * Project : GraphCut
 * Code : edge.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * Implementation of graphcut_base::Edge
 * Edge for graphcut
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <edge.h>
#include <stdint.h>
#include <glog/logging.h>

/*=== Local Define / Local Const ============================================*/

/*=== Class Implementation ==================================================*/

namespace graphcut_base {


/*--- Constructor / Destructor / Initialize ---------------------------------*/

/* Defoult constructor */
Edge::Edge(void)
    : m_startvertex(NULL),
      m_endvertex(NULL),
      m_reverseedge(NULL),
      m_flow(0.0),
      m_size(0.0)
{
}

Edge::Edge(Vertex *startvertex, Vertex *endvertex, double size)
    : m_startvertex(startvertex),
      m_endvertex(endvertex),
      m_flow(0.0),
      m_size(size)
{
}

/* Default destructor */
Edge::~Edge() {
}

/*  Copy constructor */
Edge::Edge(const Edge& rhs) {
    if (this != &rhs) {
        m_startvertex = rhs.m_startvertex;
        m_endvertex = rhs.m_endvertex;
        m_reverseedge = rhs.getReverseEdge();
        m_flow = rhs.getFlow();
        m_size = rhs.getSize();
    }
}

/* Assignment operator */
Edge& Edge::operator=(const Edge& rhs) {
    if (this != &rhs) {
        m_startvertex = rhs.m_startvertex;
        m_endvertex = rhs.m_endvertex;
        m_reverseedge = rhs.getReverseEdge();
        m_flow = rhs.getFlow();
        m_size = rhs.getSize();
    }
    return *this;
}

/*--- Operation -------------------------------------------------------------*/
double Edge::addFlow(double flow)
{
    m_flow += flow;
    if(m_reverseedge)
        m_reverseedge->setFlow(-flow);
    return flow;
}


/*  Log output operator */
google::LogMessage& operator<<(google::LogMessage& lhs, const Edge& rhs) {
  lhs.stream() << "graphcut_base::Edge{" \
               << "start : " << rhs.m_startvertex->m_name.c_str() \
               << "end : " << rhs.m_endvertex->m_name.c_str() \
               << "flow : " << rhs.getFlow() \
               << "size : " << rhs.getSize() \
               << "}" << std::endl;
  return lhs;
}

/*--- Accessor --------------------------------------------------------------*/
void Edge::setFlow(double flow)
{
    m_flow = flow;
}

double Edge::getFlow(void) const
{
    return m_flow;
}

void Edge::setReverseEdge(Edge *reverseedge)
{
    m_reverseedge = reverseedge;
}

Edge* Edge::getReverseEdge(void) const
{
    return m_reverseedge;
}

double Edge::getSize(void) const
{
    return m_size;
}

/*--- Event -----------------------------------------------------------------*/

}  // namespace graphcut_base


