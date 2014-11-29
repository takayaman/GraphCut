/*=============================================================================
 * Project : GraphCut
 * Code : vertex.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * Implementation of graphcut_base::Vertex
 * Vertex for graphcut
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <vertex.h>
#include <stdint.h>
#include <glog/logging.h>

/*=== Local Define / Local Const ============================================*/

/*=== Class Implementation ==================================================*/

namespace graphcut_base {


/*--- Constructor / Destructor / Initialize ---------------------------------*/

/* Defoult constructor */
Vertex::Vertex(void)
    : m_parent(NULL),
      m_parentpath(NULL),
      m_name(""),
      m_value(0.0),
      is_visited(false)
{
    m_vectorflowpath.clear();
}

Vertex::Vertex(std::string name)
    : m_parent(NULL),
      m_parentpath(NULL),
      m_name(name),
      m_value(0.0),
      is_visited(false)
{
    m_vectorflowpath.clear();
}

/* Default destructor */
Vertex::~Vertex(void) {
    while(!m_vectorflowpath.empty()){
        if(NULL != m_vectorflowpath.back())
            delete m_vectorflowpath.back();
        m_vectorflowpath.pop_back();
    }
}

/*  Copy constructor */
Vertex::Vertex(const Vertex& rhs) {
}

/* Assignment operator */
Vertex& Vertex::operator=(const Vertex& rhs) {
  if (this != &rhs) {
    // TODO(N.Takayama): implement copy
  }
  return *this;
}

bool Vertex::operator ==(Vertex& rhs){
    return this->m_name == rhs.m_name;
}

/*--- Operation -------------------------------------------------------------*/

void Vertex::addFlowPath(Vertex *endvertex, double size)
{
    Edge* forwardedge = new Edge(this, endvertex, size);
    m_vectorflowpath.push_back(forwardedge);
    Edge* reverseedge = new Edge(endvertex, this, -size);
    reverseedge->setReverseEdge(forwardedge);
    forwardedge->setReverseEdge(reverseedge);
    endvertex->m_vectorflowpath.push_back(reverseedge);
}

void Vertex::visit(void)
{
    is_visited = true;
}

void Vertex::reset(void)
{
    is_visited = false;
    m_value = 0.0;
}


/*  Log output operator */
google::LogMessage& operator<<(google::LogMessage& lhs, const Vertex& rhs) {
  lhs.stream() << "graphcut_base::Vertex{" <<
      // TODO(N.Takayama): implement out stream of memder data
      "}" << std::endl;
  return lhs;
}

/*--- Accessor --------------------------------------------------------------*/
void Vertex::setValue(double value)
{
    m_value = value;
}

double Vertex::getValue(void)
{
    return m_value;
}

void Vertex::setName(std::string name)
{
    m_name = name;
}

bool Vertex::isVisited(void)
{
    return is_visited;
}


/*--- Event -----------------------------------------------------------------*/

}  // namespace graphcut_base


