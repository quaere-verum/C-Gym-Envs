// TradingEnv.cpp : Defines the entry point for the application.
//

#include "tradingenvs/tradingenv.h"
#include <pybind11/pybind11.h>
#include <pybind11/stl.h>

namespace py = pybind11;

int main() {
	return 0;
}

PYBIND11_MODULE(cpp_gym_envs, m) {
	py::class_<MarginTradingEnv>(m, "MarginTradingEnv")
		.def(py::init<float, float>())
		.def("reset", &MarginTradingEnv::reset)
		.def("step", &MarginTradingEnv::step)
		.def_readonly("t", &MarginTradingEnv::t);
}
