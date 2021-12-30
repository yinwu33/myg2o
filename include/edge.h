#ifndef MYG2O_EDGE_H
#define MYG2O_EDGE_H

#include <memory>
#include <string>

#include "eigen_types.h"

namespace myg2o
{
class Vertex;

class Edge {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  explicit Edge(int residual_dimension, int num_verticies, const std::vector<std::string>& verticies_types = std::vector<std::string>());

  virtual ~Edge();

  unsigned long Id() const { return id_; }

  bool AddVertex(std::shared_ptr<Vertex> vertex) {
    verticies_.emplace_back(vertex);
    return true;
  }

  bool SetVertex(const std::vector<std::shared_ptr<Vertex>>& verticies) {
    verticies_ = verticies;
    return true;
  }

  std::shared_ptr<Vertex> GetVertex(int i) {
    return verticies_[i];
  }

  std::vector<std::shared_ptr<Vertex>> Vertices() const {
    return verticies_;
  }

  size_t NumVertices() const { return verticies_.size(); }

  virtual std::string TypeInfo() const = 0;

  virtual void ComputeResidual() = 0;

  virtual void ComputeJacobians() = 0;

  double Chi2();

  VecX Residual() const { return residual_; }

  std::vector<MatXX> Jacobians() const { return jacobians_; }

  void SetInformation(const MatXX& information) {
    information_ = information;
  }

  MatXX Information() const {
    return information_;
  }

  void SetObservation(const VecX& observation) {
    observation_ = observation;
  }

  VecX Observation() const { return observation_; }

  bool CheckValid();

  int OrderingId() const { return ordering_id_; }

  void SetOrderingId(int id) { ordering_id_ = id; }
protected:
  unsigned long id_;
  int ordering_id_;
  std::vector<std::string> verticies_types_;
  std::vector<std::shared_ptr<Vertex>> verticies_;

  VecX residual_;
  std::vector<MatXX> jacobians_;
  MatXX information_;
  VecX observation_;
};

} // namespace myg2o


#endif // MYG2O_EDGE_H