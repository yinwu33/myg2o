#ifndef MYG2O_PROBLEM_H
#define MYG2O_PROBLEM_H

#include <unordered_map>
#include <map>
#include <memory> // todo

#include "eigen_types.h"
#include "edge.h"
#include "vertex.h"

namespace myg2o
{
class Problem {
public:
  enum class ProblemType {
    GENERIC_PROBLEM
  };

  typedef unsigned long ulong;
  typedef std::map<unsigned long, std::shared_ptr<Vertex>> HashVertex;
  typedef std::unordered_map<unsigned long, std::shared_ptr<Edge>> HashEdge;
  typedef std::unordered_multimap<unsigned long, std::shared_ptr<Edge>> HashVertexIdToEdge;

  EIGEN_MAKE_ALIGNED_OPERATOR_NEW;

  Problem(ProblemType problem_type);

  ~Problem();

  bool AddVertex(std::shared_ptr<Vertex> vertex);

  bool RemoveVertex(std::shared_ptr<Vertex> vertex);

  bool AddEdge(std::shared_ptr<Edge> edge);

  bool RemoveEdge(std::shared_ptr<Edge> edge);

  void GetOutlierEdges(std::vector<std::shared_ptr<Edge>>& outlier_edges);

  bool Solve(int iterations);

  bool Marginalize(std::shared_ptr<Vertex> frame_vertex, const std::vector<std::shared_ptr<Vertex>>& landmark_verticies);

  bool Marginalize(const std::shared_ptr<Vertex> frame_vertex);

  void TestComputePrior();

private:
  bool SolveGenericProblem(int iterations);

  bool SolveSLAMProblem(int iterations);

  void SetOrdering();

  void AddOrderingSLAM(std::shared_ptr<Vertex> v);

  void MakeHessian();

  void SchurSBA();

  void SolveLinearSystem();

  void UpdateStates();

private:
  double current_lambda_;
  double current_chi_;
  double stop_threshold_LM_;
  double ni_;

  ProblemType problem_type_;

  MatXX Hessian_;
  VecX b_;
  VecX delta_x_;

  MatXX H_prior_;
  VecX b_prior_;
  MatXX Jt_prior_inv_;
  VecX err_prior_;

  MatXX H_pp_schur_;
  VecX b_pp_schur_;

  MatXX H_pp_;
  VecX b_pp_;
  MatXX H_ll_;
  VecX b_ll_;

  HashVertex verticies_;

  HashEdge edges_;

  HashVertexIdToEdge vertex_to_edge_;

  ulong ordering_poses_ = 0;
  ulong ordering_landmarks = 0;
  ulong ordering_generic_ = 0;
  std::map<unsigned long, std::shared_ptr<Vertex>> idx_pose_verticies_;
  std::map<unsigned long, std::shared_ptr<Vertex>> idx_landmark_verticies_;

  HashVertex verticies_marg_;

  bool bDebug = false;
  double t_hessain_cost_ = 0.0;
  double t_PCGsolve_cost_ = 0.0;
};

} // namespace myg2o


#endif // MYG2O_PROBLEM_H