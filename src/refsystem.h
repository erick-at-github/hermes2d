// This file is part of Hermes2D.
//
// Hermes2D is free software: you can redistribute it and/or modify
// it under the terms of the GNU General Public License as published by
// the Free Software Foundation, either version 2 of the License, or
// (at your option) any later version.
//
// Hermes2D is distributed in the hope that it will be useful,
// but WITHOUT ANY WARRANTY; without even the implied warranty of
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
// GNU General Public License for more details.
//
// You should have received a copy of the GNU General Public License
// along with Hermes2D.  If not, see <http://www.gnu.org/licenses/>.

#ifndef __H2D_REFSYSTEM_H
#define __H2D_REFSYSTEM_H

#include "linsystem.h"
#include "nonlinsystem.h"
#include "views/order_view.h"

class Mesh;
class ExactSolution;

///
///
///
class H2D_API RefSystem : public NonlinSystem
{
public:
  RefSystem(LinSystem* base, int order_increase = 1, int refinement = 1);
  virtual ~RefSystem();

  /// Do not call in this class - contains just an error message.
  void set_spaces(Tuple<Space*> spaces);
  /// Do not call in this class - contains just an error message.
  void set_pss(Tuple<PrecalcShapeset*> pss);

  /// Performs global mesh refinement and related things.
  void global_refinement();

  /// Sets order increases (same for all components)
  void set_order_increase(int order_increase);

  /// Creates reference (fine) meshes and spaces and assembles the
  /// reference system.
  void assemble(bool rhsonly = false);

  bool solve_exact(ExactFunction exactfn, Solution* sln);

protected:

  LinSystem* base;
  Mesh** meshes;
  int order_increase;
  int refinement;
};


#endif
