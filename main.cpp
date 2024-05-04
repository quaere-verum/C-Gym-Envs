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
		.def(py::init<float, float>(), py::arg("initial_capital"), py::arg("trading_costs"))
		.def("reset", &MarginTradingEnv::reset, py::arg("price_series"), py::arg("predictions"))
		.def("step", &MarginTradingEnv::step, py::arg("position"), py::arg("allocation"), py::arg("take_profit"), py::arg("stop_loss"), py::arg("hold_time"), py::arg("leverage"))
		.def_readonly("t", &MarginTradingEnv::t);
}
