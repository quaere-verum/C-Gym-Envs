#include <iostream>
#include <vector>

struct Position {
	Position(const int& position_, const float& entryPrice_, const float& amount_, 
		const float& takeProfit_, const float& stopLoss_, const int& holdTime_, const float& leverageMult_) :
	position(position_), entryPrice(entryPrice_), amount(amount_), takeProfit(takeProfit_), stopLoss(stopLoss_), holdTime(holdTime_), leverageMult(leverageMult_){}
	int position;
	float entryPrice;
	float amount;
	float takeProfit;
	float stopLoss;
	int holdTime;
	float leverageMult;
	int timeOpen = 0;
	

};

class MarginPortfolio {
public:
	MarginPortfolio(float initialCapital_, float tradingFees_): 
		capital(initialCapital_),
		initialCapital(initialCapital_),
		tradingFees(tradingFees_)
	{};

	std::vector<Position> positions;
	float capital;
	const float initialCapital;
	const float tradingFees;

	void openPosition(int position, float price, float amount, float takeProfit, float stopLoss, int holdTime, float leverageMult) {
		capital -= amount * price*(1+position*tradingFees)*position;
		positions.push_back(Position(position, price, amount, takeProfit, stopLoss, holdTime, leverageMult));
	}

	float valuate(float price) {
		float valuation = capital;
		for (int i = 0; i < positions.size(); i++) {
			valuation += positions[i].leverageMult * positions[i].position * (price * positions[i].amount);
		}
		return valuation;
	}

	void managePositions(float price) {
		float positionReturn;
		for (int i = positions.size() - 1; i>= 0; i--) {
			positions[i].timeOpen += 1;
			positionReturn = ((price - positions[i].entryPrice) / positions[i].entryPrice)*positions[i].leverageMult*positions[i].position;

			if (positionReturn < positions[i].stopLoss || positionReturn > positions[i].takeProfit || positions[i].timeOpen >= positions[i].holdTime) {
				capital += positions[i].leverageMult * positions[i].amount * price * positions[i].position * (1 - positions[i].position * tradingFees);
				positions.erase(positions.begin() + i);
			}
		}
	}

	void reset() {
		capital = initialCapital;
		positions.clear();
	}
};