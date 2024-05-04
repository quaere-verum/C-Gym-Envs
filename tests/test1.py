import numpy as np 
import cpp_gym_envs as cg
import gymnasium as gym

np.random.seed(123)

class TestEnv(gym.Env):
	def __init__(self, prices, predictions, capital, trading_fees, episode_length, lookback_window):
		super().__init__()
		self.t = lookback_window
		self.prices = prices
		self.predictions = predictions
		self.episode_length = episode_length
		self.lookback_window = lookback_window

		self.cpp_env = cg.MarginTradingEnv(capital, trading_fees)

	def reset(self):
		if self.t >= len(self.predictions) -1:
			self.t = lookback_window
		self.t += self.cpp_env.reset(self.prices[self.t:self.t+self.episode_length+1], self.predictions[self.t:self.t+self.episode_length+1])
		return self.prices[self.t-self.lookback_window:self.t+1], None

	def step(self, action):
		t, reward = self.cpp_env.step(action)
		if t < 0:
			print('x')
			return self.prices[self.t-self.lookback_window:self.t+1], 0, True, True, None
		self.t += t
		return self.prices[self.t-self.lookback_window:self.t+1], reward, False, False, None



prices = np.exp(np.cumsum(np.random.normal(0, 0.05, 200)))
predictions = np.random.binomial(1, 0.5, 200)

testenv = TestEnv(prices, predictions, 100, 0.001, 100, 5)


print(prices)
print(predictions)

done, truncated = False, False
obs, info = testenv.reset()
while not done and not truncated:
	obs, reward, done, truncated, info = testenv.step(np.array([-0.5, 0.05, -0.05, 6]))
	print("Reward", reward)
