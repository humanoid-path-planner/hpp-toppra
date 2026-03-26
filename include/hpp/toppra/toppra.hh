#ifndef HPP_TOPPRA_PATH_OPTIMIZATION_TOPPRA_HH
#define HPP_TOPPRA_PATH_OPTIMIZATION_TOPPRA_HH

#include <hpp/core/path-optimizer.hh>

#include <toppra/toppra.hpp>

namespace hpp {
namespace toppra {
namespace pathOptimization {

class TOPPRA;
typedef shared_ptr<TOPPRA> TOPPRAPtr_t;

class TOPPRA : public core::PathOptimizer {
 public:
   enum InterpolationMethod {
     ConstantAcceleration,
     Hermite,
   };
   enum GridpointMethod {
     EvenlyTimeSpaced,
     EvenlyParamSpaced,
   };

  static TOPPRAPtr_t create(const core::ProblemConstPtr_t &p);

  core::PathVectorPtr_t optimize(const core::PathVectorPtr_t &path);

  // TODO remove when
  // https://github.com/humanoid-path-planner/hpp-core/pull/305
  // is released.
  core::TimeParameterizationPtr_t lastTimeParameterization_;

  /// Effort rescaling value. Negative to disable torque constraints.
  core::value_type effortScale;
  /// Velocity rescaling value.
  core::value_type velocityScale;
  /// Acceleration limits vector. Empty to disable acceleration constraints.
  core::vector_t accelerationLimits;
  /// Solver: 0 = Seidel, 1 = GLPK, 2 = qpOASES.
  core::size_type solver;
  /// Minimal number of sampling points.
  core::size_type N;
  /// Interpolation method: "hermite" or "constant_acceleration".
  std::string interpolationMethod_;
  /// Gridpoint method: "param_space" or "time_space".
  std::string gridpointMethod_;

 protected:
  TOPPRA(const core::ProblemConstPtr_t &p);

 private:
  void inputSerialization(core::PathPtr_t path) const;
  ::toppra::LinearConstraintPtrs constraints();
  InterpolationMethod interpolationMethod() const;
  GridpointMethod gridpointMethod() const;
};  // class TOPPRA

}  // namespace pathOptimization
}  // namespace toppra
}  // namespace hpp

#endif  // HPP_TOPPRA_PATH_OPTIMIZATION_TOPPRA_HH
