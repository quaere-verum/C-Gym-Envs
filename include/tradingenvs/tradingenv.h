// TradingEnv.h : Include file for standard system include files,
// or project specific include files.

#pragma once

#include <iostream>
#include <pybind11/pybind11.h>
#include <pybind11/numpy.h>
#include <cmath>
#include <tradingenvs/portfolio.h>
#include <vector>

namespace py = pybind11;

class MarginTradingEnv {
public:
	MarginTradingEnv(float initialCapital_, float tradingFees_) : 
		initialCapital(initialCapital_),
		tradingFees(tradingFees_),
		portfolio(MarginPortfolio(initialCapital_, tradingFees_))
	{};

	MarginPortfolio portfolio;
	float initialCapital;
	float tradingFees;
	int step;
	int t;
	std::vector<float> priceSeries;
	std::vector<int> takeAction;

	int reset(std::vector<float> priceSeries_, std::vector<int> takeAction_) {
		priceSeries = priceSeries_;
		takeAction = takeAction_;
		portfolio.reset();
		t, step = 0;
		int act;
		while (true) {
			if (t >= takeAction.size()) {
				return -1;
			}
			act = takeAction[t];
			if (act == 1) {
				return t;
			}
			t++;
		}
	}

	std::tuple<int, float> step(py::array_t<float> action) {
		return;
	}

};
