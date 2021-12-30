#include <iostream>
#include <fstream>
#include <Eigen/Dense>
#include <glog/logging.h>
#include "problem.h"
#include "utils/timer.h"

// todo

namespace myg2o
{

Problem::Problem(ProblemType problem_type) : problem_type_(problem_type) {
  verticies_marg_.clear();
}

Problem::~Problem() {}

bool Problem::AddVertex(std::shared_ptr<Vertex> vertex) {
  if (verticies_.find(vertex->Id()) != verticies_.end()) {
    return false;
  }
  else {
    verticies_.insert(std::pair<ulong, std::shared_ptr<Vertex>>(vertex->Id(), vertex));
  }

  return true;
}

bool Problem::AddEdge(std::shared_ptr<Edge> edge) {
  if (edges_.find(edge->Id()) != edges_.end()) {
    return false;
  }
  else {
    edges_.insert(std::pair<ulong, std::shared_ptr<Edge>>(edge->Id(), edge));
  }

  for (auto& vertex : edge->Vertices()) {
    vertex_to_edge_.insert(std::pair<ulong, std::shared_ptr<Edge>>(vertex->Id(), edge));
  }

  return true;
}

bool Problem::Solve(int iterations) {
  if (edges_.size() == 0 or verticies_.size() == 0) {
    std::cerr << "Cannot solve problem without edges or verticies!" << std::endl;
    return false;
  }

  Timer timer;

  // todo

  bool stop = false;
  int iter = 0;
  while (!stop and (iter < iterations)) {
    std::cout << "iter: " << iter << ", chi: " << current_chi_ << ", lambda: " << current_lambda_ << std::endl;
    bool onestep_success = false;
    int false_count = 0;

    while (!onestep_success) {
      AddLambdaToHessiaanLM();
    }
  }

}
} // namespace myg2o
