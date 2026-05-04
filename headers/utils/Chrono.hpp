#ifndef CHRONO_HPP
# define CHRONO_HPP

#include <chrono>

class Chrono {
	using clock = std::chrono::steady_clock;

	private:
		std::chrono::time_point<clock>	_start_time;
		std::chrono::duration<double>	_elapsed{0};
		bool							_running = false;

	public:
		void	Start() {
			this->_start_time = clock::now();
			this->_running = true;
			this->_elapsed = {};
		}
		void	Stop() {
			if (!this->isRunning())
				return ;

			this->_elapsed += std::chrono::duration_cast<std::chrono::duration<double>>(clock::now() - this->_start_time);
			this->_running = false;
		}
		void	Resume() {
			this->_start_time = clock::now();
			this->_running = true;
		}
		bool	isRunning() const {
			return (this->_running);
		}
		double getElapsedSeconds() const {
			if (!this->_running)
				return this->_elapsed.count();

			auto delta = std::chrono::duration_cast<std::chrono::duration<double>>(clock::now() - this->_start_time);
			return (this->_elapsed + delta).count();
		}
};

#endif // !CHRONO_HPP