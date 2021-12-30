#include "edge.h"
#include "vertex.h"

#include <iostream>

using namespace std;

namespace myg2o
{
unsigned long global_edge_id = 0;

Edge::Edge(int residual_dimension, int num_verticies, const std::vector<std::string>& verticies_types) {
  residual_.resize(residual_dimension, 1);

  if (!verticies_types.empty()) {
    verticies_types_ = verticies_types;
  }

  jacobians_.resize(num_verticies);
  id_ = global_edge_id++;

  MatXX information(residual_dimension, residual_dimension);
  information.setIdentity();

  information_ = information;
}

Edge::~Edge() {}

double Edge::Chi2() {
  return residual_.transpose() * information_ * residual_; // todo
}

bool Edge::CheckValid() {
  if (!verticies_types_.empty()) {
    for (size_t i = 0; i < verticies_.size(); ++i) {
      if (verticies_types_[i] != verticies_[i]->TypeInfo()) {
        cout << "Vertex type does not match, should be " << verticies_types_[i]
          << ", but set to " << verticies_[i]->TypeInfo() << endl;
        return false;
      }
    }
  }
  // todo
  return true;
}

} // namespace myg2o
