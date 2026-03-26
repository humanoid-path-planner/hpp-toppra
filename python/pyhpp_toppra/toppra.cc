//
// Copyright (c) 2026 CNRS
// Authors: Florent Lamiraux
//

// Redistribution and use in source and binary forms, with or without
// modification, are permitted provided that the following conditions are
// met:
//
// 1. Redistributions of source code must retain the above copyright
//    notice, this list of conditions and the following disclaimer.
//
// 2. Redistributions in binary form must reproduce the above copyright
// notice, this list of conditions and the following disclaimer in the
// documentation and/or other materials provided with the distribution.
//
// THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
// "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
// LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
// A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
// HOLDER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
// SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
// LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
// DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
// THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
// (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
// OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH
// DAMAGE.

#include <boost/python.hpp>
#include <hpp/core/path-optimizer.hh>
#include <hpp/toppra/toppra.hh>

namespace pyhpp {
namespace toppra {
typedef hpp::pinocchio::Joint Joint;
using namespace boost::python;

void exposeToppra() {
  typedef hpp::toppra::pathOptimization::TOPPRA TOPPRA_t;
  class_<TOPPRA_t,
	 std::shared_ptr<TOPPRA_t>, bases<hpp::core::PathOptimizer>,
    boost::noncopyable> ("Toppra", no_init)
    .def("__init__",
	 make_constructor(&TOPPRA_t::create))
    .def_readwrite("effortScale", &TOPPRA_t::effortScale)
    .def_readwrite("velocityScale", &TOPPRA_t::velocityScale)
    .def_readwrite("accelerationLimits", &TOPPRA_t::accelerationLimits)
    .def_readwrite("solver", &TOPPRA_t::solver)
    .def_readwrite("N", &TOPPRA_t::N)
    .def_readwrite("interpolationMethod", &TOPPRA_t::interpolationMethod_)
    .def_readwrite("gridpointMethod", &TOPPRA_t::gridpointMethod_);
}

} // namespace toppra
} // namespace pyhpp
