#include <iostream>
#include <vector>

struct Position {
	Position(const int& position_, const float& entryPrice_, const float& amount_, const float& takeProfit_, const float& stopLoss_, const int& holdTime_) :
	position(position_), entryPrice(entryPrice_), amount(amount_), takeProfit(takeProfit_), stopLoss(stopLoss_), holdTime(holdTime_){}
	int position;
	float entryPrice;
	float amount;
	float takeProfit;
	float stopLoss;
	int holdTime;
	int timeOpen = 0;
	

};

class Portfolio {
public:
	Portfolio(float initialCapital, float tradingFees_) : capital(initialCapital), tradingFees(tradingFees_){};

	std::vector<Position> positions;
	float capital;
	const float tradingFees;

	void openPosition(int position, float price, float amount, float takeProfit, float stopLoss) {
		capital -= amount * price*(1+tradingFees)*position;
		positions.push_back(Position(position, price, amount, takeProfit, stopLoss))
	}

	float valuate(float price) {
		float valuation = capital;
		for (int i = 0; i < positions.size(); i++) {
			valuation += positions[i].position*(price*positions[i].amount)
		}
		return valuation;
	}

	void managePositions(float price) {
		float positionReturn;
		for (int i = 0; i < positions.size(); i++) {
			positions[i].timeOpen += 1;
			positionReturn = (positions[i].entryPrice - price) / price - 1;
			if (positionReturn < positions[i].stopLoss || positionReturn > positions[i].takeProfit || positions[i].timeOpen >= positions[i].holdTime)
				capital += positions[i].amount * price * positions[i].position * (1 - tradingFees);
				positions.erase(positions.begin() + i);

		}
	}
};