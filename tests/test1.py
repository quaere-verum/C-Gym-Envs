import numpy as np 
import cpp_gym_envs as cg
import gymnasium as gym

np.random.seed(123)

class TestEnv(gym.Env):
	def __init__(self, prices, predictions, capital, trading_fees, episode_bars, episode_length, lookback_window):
		super().__init__()
		self.t = lookback_window
		self.prices = prices
		self.predictions = predictions
		self.episode_bars = episode_bars
		self.episode_length = episode_length
		self.lookback_window = lookback_window

		self._step = None
		self.episode_start_t = None
		self.cpp_env = cg.MarginTradingEnv(capital, trading_fees)

	def reset(self):
		self._step = 0
		self.episode_start_t = self.t
		self.t = self.episode_start_t + self.cpp_env.reset(self.prices[self.t:self.t+self.episode_bars+1], self.predictions[self.t:self.t+self.episode_bars+1])
		return self.prices[self.t-self.lookback_window:self.t+1], None

	def step(self, action):
		t, reward = self.cpp_env.step(position=int(np.sign(action[0])), allocation=action[0], take_profit=action[1], stop_loss=action[2], hold_time=int(action[3]), leverage=1.)
		if t < 0 or self._step > self.episode_length:
			if self.episode_start_t + self.cpp_env.t >= len(self.predictions) - 1:
				self.t = self.lookback_window
			return self.prices[self.t-self.lookback_window:self.t+1], 0, True, True, None
		self.t = self.episode_start_t + t
		self._step += 1
		return self.prices[self.t-self.lookback_window:self.t+1], reward, False, False, None



prices = np.exp(np.cumsum(np.random.normal(0, 0.05, 200)))
predictions = np.random.binomial(1, 0.5, 200)

testenv = TestEnv(prices, predictions, 100, 0.001, 100, 10, 5)


print(prices)
print(predictions)
for _ in range(10):
	done, truncated = False, False
	obs, info = testenv.reset()
	total_reward = 0
	while not done and not truncated:
		obs, reward, done, truncated, info = testenv.step(np.array([-0.5, 0.05, -0.05, 6]))
		total_reward += reward
	print(f"Episode terminated at time {testenv.t}. Total reward: {total_reward:.2f}")
