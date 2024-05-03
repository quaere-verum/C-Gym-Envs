﻿// TradingEnv.h : Include file for standard system include files,
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
		int position = action.at(0) < 0 ? -1 : 1;
		float amount = portfolio.capital * action.at(0);
		portfolio.openPosition(position, priceSeries[t], amount, action.at(1), action.at(2), action.at(3), 1);
		float startingValue = portfolio.valuate(priceSeries[t]);
		float currentValue;
		int act;
		while (true) {
			portfolio.managePositions(priceSeries[t]);
			currentValue = portfolio.valuate(priceSeries[t]);
			act = takeAction[t];
			if (t >= takeAction.size() - 1 || currentValue <= 0) {
				return std::make_tuple(-1, currentValue - startingValue);
			}
			if (portfolio.positions.size() == 0 && act == 1) {
				return std::make_tuple(t, currentValue - startingValue);
			}
			t++;
		}
	}

};
