/*=============================================================================
 * Project : GraphCut
 * Code : main.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * GraphCut Test
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <stdint.h>
#include <glog/logging.h>

#include "graph.h"

/*=== Local Define / Local Const ============================================*/

/*=== Local Variable ========================================================*/

/*=== Local Function Define =================================================*/

/*=== Local Function Implementation =========================================*/

/*=== Global Function Implementation ========================================*/

int main(int argc, char *argv[]) {
  /* Initialize */
  google::InitGoogleLogging(argv[0]);
  FLAGS_logtostderr = true;

  graphcut_base::Graph graph;
  graphcut_base::Vertex *vertex_a = graph.addVertex("a");
  graphcut_base::Vertex *vertex_b = graph.addVertex("b");
  graphcut_base::Vertex *vertex_c = graph.addVertex("c");
  graphcut_base::Vertex *vertex_d = graph.addVertex("d");
  graphcut_base::Vertex *vertex_e = graph.addVertex("e");
  graphcut_base::Vertex *vertex_f = graph.addVertex("f");

  graph.addFlowPath(vertex_a, vertex_b, 6);
  graph.addFlowPath(vertex_a, vertex_c, 8);
  graph.addFlowPath(vertex_b, vertex_d, 6);
  graph.addFlowPath(vertex_b, vertex_e, 3);
  graph.addFlowPath(vertex_c, vertex_d, 3);
  graph.addFlowPath(vertex_c, vertex_e, 3);
  graph.addFlowPath(vertex_d, vertex_f, 8);
  graph.addFlowPath(vertex_e, vertex_f, 6);

  graph.m_source = vertex_a;
  graph.m_sink = vertex_f;

  graph.searchMaxFlow();
  // 頂点のvisitの初期化が必要
  graph.reset();
  graph.searchMinCut( graph.m_source );
  graph.displayMinCut();

  /* Finalize */
  google::InstallFailureSignalHandler();

  return EXIT_SUCCESS;
}
