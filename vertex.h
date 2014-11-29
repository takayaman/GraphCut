/*=============================================================================
 * Project : GraphCut
 * Code : vertex.h
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * Definition of graphcut_base::Vertex
 * Vertex for graphcut
 *===========================================================================*/

#ifndef _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_VERTEX_H_
#define _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_VERTEX_H_

/*=== Include ===============================================================*/

#include <stdint.h>
#include <glog/logging.h>

#include <vector>

#include "edge.h"

/*=== Define ================================================================*/

/*=== Class Definition  =====================================================*/

namespace graphcut_base {

class Edge;

class Vertex {
public:
    /*!
    * Defoult constructor
    */
    Vertex(void);

    Vertex(std::string name);

    /*!
    * Default destructor
    */
    ~Vertex(void);

    /*!
    * Copy constructor
    */
    Vertex(const Vertex& rhs);

    /*!
    * Assignment operator
    * @param rhs Right hand side
    * @return pointer of this object
    */
    Vertex& operator=(const Vertex& rhs);

    bool operator ==(Vertex& rhs);

    /*! 自身を始点として終点との間に双方向エッジを張り,容量を設定する
    * ここで,始点->終点のエッジ容量 : size
    * 終点->始点のエッジ容量 : -size
    */
    void addFlowPath(Vertex *endvertex, double size);
    void visit(void);
    void reset(void);

    void setValue(double value);
    double getValue(void);
    void setName(std::string name);

    bool isVisited(void);

public:
    std::vector<Edge*> m_vectorflowpath;
    Vertex* m_parent;
    Edge* m_parentpath;
    std::string m_name;

private:
    double m_value;
    bool is_visited;

};

/*!
 * Log output operator
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return Pointer of google::LogSink object
 */
google::LogMessage& operator<<(google::LogMessage& lhs, const Vertex& rhs);

}  // namespace graphcut_base


#endif  // _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_VERTEX_H_
