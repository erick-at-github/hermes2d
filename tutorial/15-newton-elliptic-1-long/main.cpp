#define H2D_REPORT_WARN
#define H2D_REPORT_INFO
#define H2D_REPORT_VERBOSE
#define H2D_REPORT_FILE "application.log"
#include "hermes2d.h"
#include "function.h"

// This is a long version of example 15-newton-elliptic-1: function solve_newton() is not used.

const int P_INIT = 2;                             // Initial polynomial degree.
const int INIT_GLOB_REF_NUM = 3;                  // Number of initial uniform mesh refinements.
const int INIT_BDY_REF_NUM = 5;                   // Number of initial refinements towards boundary.
const double NEWTON_TOL = 1e-6;                   // Stopping criterion for the Newton's method.
const int NEWTON_MAX_ITER = 100;                  // Maximum allowed number of Newton iterations.
const double INIT_COND_CONST = 3.0;               // COnstant initial condition.
MatrixSolverType matrix_solver = SOLVER_UMFPACK;  // Possibilities: SOLVER_UMFPACK, SOLVER_PETSC,
                                                  // SOLVER_MUMPS, and more are coming.

// Thermal conductivity (temperature-dependent)
// Note: for any u, this function has to be positive.
template<typename Real>
Real lam(Real u) { return 1 + pow(u, 4); }

// Derivative of the thermal conductivity with respect to 'u'.
template<typename Real>
Real dlam_du(Real u) { return 4*pow(u, 3); }

// Boundary condition types.
BCType bc_types(int marker)
{
  return BC_ESSENTIAL;
}

// Essential (Dirichlet) boundary condition values.
scalar essential_bc_values(int marker, double x, double y)
{
  return 0;
}

// Weak forms.
#include "forms.cpp"

int main(int argc, char* argv[])
{
  // Load the mesh.
  Mesh mesh;
  H2DReader mloader;
  mloader.load("square.mesh", &mesh);

  // Perform initial mesh refinements.
  for(int i = 0; i < INIT_GLOB_REF_NUM; i++) mesh.refine_all_elements();
  mesh.refine_towards_boundary(1,INIT_BDY_REF_NUM);

  // Create an H1 space with default shapeset.
  H1Space* space = new H1Space(&mesh, bc_types, essential_bc_values, P_INIT);
  int ndof = get_num_dofs(space);

  // Initialize the weak formulation.
  WeakForm wf;
  wf.add_matrix_form(callback(jac), H2D_UNSYM, H2D_ANY);
  wf.add_vector_form(callback(res), H2D_ANY);

  // Project the initial condition on the FE space to obtain initial 
  // coefficient vector for the Newton's method.
  info("Projecting to obtain initial vector for the Newton's method.");
  Vector* init_coeff_vec = new AVector(ndof);
  Solution* init_sln = new Solution();
  init_sln->set_const(&mesh, INIT_COND_CONST);
  // The NULL means that we do not want the resulting Solution, just the vector.
  project_global(space, H2D_H1_NORM, init_sln, NULL, init_coeff_vec); 

  // Perform Newton's iteration.
  info("Performing Newton's iteration.");
  bool verbose = true;
  if (!solve_newton(space, &wf, init_coeff_vec, matrix_solver, 
		    NEWTON_TOL, NEWTON_MAX_ITER, verbose)) {
    error("Newton's method did not converge.");
  };

  // Translate the resulting coefficient vector into a Solution.
  Solution sln; 
  sln.set_fe_solution(space, init_coeff_vec);

  // Visualise the solution and mesh.
  WinGeom* sln_win_geom = new WinGeom(0, 0, 440, 350);
  ScalarView s_view("Solution", sln_win_geom);
  s_view.show_mesh(false);
  s_view.show(&sln);
  WinGeom* mesh_win_geom = new WinGeom(450, 0, 400, 350);
  OrderView o_view("Mesh", mesh_win_geom);
  o_view.show(space);

  // Wait for all views to be closed.
  View::wait();
  return 0;
}
