#ifndef MYG2O_VERTEX_H
#define MYG2O_VERTEX_H

#include "eigen_types.h"

namespace myg2o
{
class Vertex {
public:
  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  explicit Vertex(int num_dimension, int local_dimension = -1);

  virtual ~Vertex();

  int Dimension() const { return parameters_.rows(); }

  int LocalDimension() const { return local_dimension_; }

  unsigned long Id() const { return id_; }

  VecX Parameters() const { return parameters_; }

  void SetParameters(const VecX& params) { parameters_ = params; }

  virtual void Plus(const VecX& delta);

  int OrderingID() const { return ordering_id_; }

  void SetOrderingID(unsigned long id) { ordering_id_ = id; }

  void SetFixed(bool fixed = true) { fixed_ = fixed; }

  bool isFixed() const { return fixed_; }

private:
  unsigned long id_;
  VecX parameters_;
  int local_dimension_;

  unsigned long ordering_id_;

  bool fixed_ = false;

};

} // namespace myg2o



#endif // MYG2O_VERTEX_H