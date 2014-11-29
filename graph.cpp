/*=============================================================================
 * Project : GraphCut
 * Code : graph.cpp
 * Written : N.Takayama, UEC
 * Date : 2014/11/26
 * Copyright (c) 2014 N.Takayama <takayaman@uec.ac.jp>
 * Implementation of graphcut_base::Graph
 * Graph for cut 
 *===========================================================================*/

/*=== Include ===============================================================*/

#include <graph.h>
#include <stdint.h>
#include <float.h>
#include <glog/logging.h>

/*=== Local Define / Local Const ============================================*/

/*=== Class Implementation ==================================================*/

namespace graphcut_base {


/*--- Constructor / Destructor / Initialize ---------------------------------*/

/* Defoult constructor */
Graph::Graph(void)
    : m_source(NULL),
      m_sink(NULL)
{
    m_vertexes.clear();
}

/* Default destructor */
Graph::~Graph(void) {
    while(!m_vertexes.empty()){
        if(NULL != m_vertexes.back())
            delete m_vertexes.back();
        m_vertexes.pop_back();
    }
}

/*  Copy constructor */
Graph::Graph(const Graph& rhs) {
}

/* Assignment operator */
Graph& Graph::operator=(const Graph& rhs) {
  if (this != &rhs) {
    // TODO(N.Takayama): implement copy
  }
  return *this;
}

/*--- Operation -------------------------------------------------------------*/
void Graph::reset(void)
{
    for(size_t i = 0; i < m_vertexes.size(); i++){
        Vertex* vertex = m_vertexes[i];
        vertex->reset();
    }
}

Vertex* Graph::addVertex(std::string name)
{
    Vertex* vertex = new Vertex(name);
    m_vertexes.push_back(vertex);
    return vertex;
}

bool Graph::addFlowPath(Vertex *startvertex, Vertex *endvertex, double value)
{
    Vertex *start = NULL, *end = NULL;
    bool can_findstart = false, can_findend = false;

    /* 頂点名を基に始点と終点を探索 */
    for(size_t i = 0; i < m_vertexes.size(); i++){
        if(startvertex == m_vertexes[i]){
            start = m_vertexes[i];
            can_findstart = true;
            if(can_findend)
                break;
        }
        if(endvertex == m_vertexes[i]){
            end = m_vertexes[i];
            can_findend = true;
            if(can_findstart)
                break;
        }
    }
    /* 始点が見つからない場合はエラー */
    if(NULL == start){
        LOG(ERROR) << "Can not find startvertex : " << startvertex->m_name << std::endl;
        return false;
    }
    /* 終点が見つからない場合は追加 */
    if(NULL == end && NULL != endvertex){
        end = addVertex(endvertex->m_name);
    }
    start->addFlowPath(end, value);
    return true;
}

bool Graph::searchMaxFlow(void)
{
    /* 最大流パスを幅優先探索で求め,エッジに求めた流量を追加
     * パスが見つからなくなるまで繰り返す
     */
    while(flowFirstSearch()){
        Vertex* vertex = m_sink;
        while(vertex != m_source){
            Edge* edge = vertex->m_parentpath;
            edge->addFlow(m_sink->getValue());
            LOG(INFO) << "add flow to " << edge->m_startvertex->m_name.c_str() << "-" \
                      << edge->m_endvertex->m_name.c_str() << " by " \
                      << m_sink->getValue() << std::endl;
            vertex = vertex->m_parent;
        }
    }
    return true;
}

bool Graph::flowFirstSearch(void)
{
    LOG(INFO) << "start priority-first search" << std::endl;

    // 初期化
    reset();

    m_source->setValue(DBL_MAX);

    Vertex* vertex = m_source;
    bool can_findsource2sink = false;
    bool can_findmax = false;
    do{
        vertex->visit();
        double value = vertex->getValue();

        /* 新たに訪問済みになったvertexの隣接頂点の流量の更新 */
        std::vector<Edge*> vectorflowpath = vertex->m_vectorflowpath;
        for(size_t i = 0; i < vectorflowpath.size(); i++){
            /* 未訪問の終点とエッジを探索 */
            Edge* adjacency_edge = vectorflowpath[i];
            Vertex* adjacency_vertex = adjacency_edge->m_endvertex;
            if(adjacency_vertex->isVisited())
                continue;

            /* 流量の更新
             * vertexを経由した場合のadjacency_vertexへの流量を求める
             */
            double flow = -(adjacency_edge->getFlow());
            double size = adjacency_edge->getSize();
            if(0 < size)
                flow += size;
            if(flow > value)
                flow = value;
            /* 求めたadjacency_vertexへの流量が設定されていた流量を上回る場合
             * ->すなわち,より多い流量をadjacency_vertexに流せる場合
             * adjacency_vertexへの経路と流量を更新する
             */
            if(adjacency_vertex->getValue() < flow){
                adjacency_vertex->setValue(flow);
                adjacency_vertex->m_parent = vertex;
                adjacency_vertex->m_parentpath = adjacency_edge;
            }
        }

        /* 流量最大の頂点を求める */
        double maxvalue = 0.0;
        int maxindex = -1;

        for(size_t i = 0; i < m_vertexes.size(); i++){
            Vertex *next = m_vertexes[i]            ;
            if(next->isVisited())
                continue;
            if(next->getValue() > maxvalue){
                maxvalue = next->getValue();
                maxindex = i;
            }
        }

        /* 流量最大の頂点が見つかった */
        if(0 <= maxindex){
            can_findmax = true;
            vertex = m_vertexes[maxindex];
            if(vertex == m_sink){
                /* sourceからsinkへの経路が見つかった */
                can_findsource2sink = true;
                break;
            }
        }
    }while(can_findmax);

    return can_findsource2sink;
}

void Graph::searchMinCut(Vertex *source)
{
    m_mincut.push_back(source);
    source->visit();

    std::vector<Edge*> vectorflowpath = source->m_vectorflowpath;
    for(size_t i = 0; i < vectorflowpath.size(); i++){
        Edge* adjacency_edge = vectorflowpath[i];
        Vertex* adjacency_vertex = adjacency_edge->m_endvertex;
        if(adjacency_vertex->isVisited())
            continue;
        // 飽和した前向き辺や流量ゼロの後ろ向き辺でない場合
        if((0 < adjacency_edge->getSize() && adjacency_edge->getFlow() != adjacency_edge->getSize())
                || (0 > adjacency_edge->getSize() && 0 != adjacency_edge->getFlow())){
            searchMinCut(adjacency_vertex);
        }
    }

}

void Graph::displayMinCut(void)
{
    LOG(INFO) << "display mincut" << std::endl;
    for(size_t i = 0; i < m_mincut.size(); i++){
        Vertex *vertex = m_mincut[i];
        LOG(INFO) << vertex->m_name.c_str() << std::endl;
    }
}


/*  Log output operator */
google::LogMessage& operator<<(google::LogMessage& lhs, const Graph& rhs) {
  lhs.stream() << "graphcut_base::Graph{" <<
      // TODO(N.Takayama): implement out stream of memder data
      "}" << std::endl;
  return lhs;
}

/*--- Accessor --------------------------------------------------------------*/

/*--- Event -----------------------------------------------------------------*/

}  // namespace graphcut_base


