#ifndef MPC_H
#define MPC_H

#include <vector>
#include "Eigen-3.3/Eigen/Core"

using namespace std;

#define NUMSTEPS 10
#define DT 0.1 // time step duration dt in s 
#define LF 2.67

class MPC {
 public:
  MPC();

  virtual ~MPC();

  // Solve the model given an initial state and polynomial coefficients.
  // Return the first actuatotions.
  vector<double> Solve(Eigen::VectorXd state, Eigen::VectorXd coeffs);
  vector<double> mpc_x;
  vector<double> mpc_y;
};

#endif /* MPC_H */
