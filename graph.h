/*=============================================================================
 * Project : GraphCut
 * Code : graph.h
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * Definition of graphcut_base::Graph
 * Graph for cut
 *===========================================================================*/

#ifndef _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_GRAPH_H_
#define _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_GRAPH_H_

/*=== Include ===============================================================*/

#include <stdint.h>
#include <glog/logging.h>

#include "vertex.h"

/*=== Define ================================================================*/

/*=== Class Definition  =====================================================*/

namespace graphcut_base {


class Graph {
 public:
  /*!
   * Defoult constructor
   */
  Graph(void);

  /*!
   * Default destructor
   */
  ~Graph(void);

  /*!
   * Copy constructor
   */
  Graph(const Graph& rhs);

  /*!
   * Assignment operator
   * @param rhs Right hand side
   * @return pointer of this object
   */
  Graph& operator=(const Graph& rhs);

  void reset(void);
  Vertex* addVertex(std::string name);
  bool addFlowPath(Vertex *startvertex, Vertex *endvertex, double value);

  bool searchMaxFlow(void);
  bool flowFirstSearch(void);
  void searchMinCut(Vertex *source);
  void displayMinCut(void);

public:
  std::vector<Vertex*> m_vertexes;
  std::vector<Vertex*> m_mincut;
  Vertex* m_source;
  Vertex* m_sink;

};

/*!
 * Log output operator
 * @param lhs Left hand side
 * @param rhs Right hand side
 * @return Pointer of google::LogSink object
 */
google::LogMessage& operator<<(google::LogMessage& lhs, const Graph& rhs);

}  // namespace graphcut_base


#endif  // _HOME_TAKAYAMAN_DOCUMENTS_PROGRAMMING_GENERAL_GRAPHCUT_GRAPHCUT_GRAPH_H_
