#include <random>
#include <vector>

template<class T = int>
class Random {
	public:
		Random(T b = 100, T a = 0) {
			engine.seed(rd());
			dist = std::uniform_int_distribution<T>(a, b);
		}

		T get() {
			return( dist(engine) );
		}

		void seed(int seed) {
			engine.seed(seed);
		}

	private:
		std::mt19937 engine;
		std::random_device rd;
		std::uniform_int_distribution<T> dist;
};

template<class T = int>
auto get_random_number_vector(uint64_t Nnumbers, Random<T> &rand) {
	std::vector<T> data;
	data.reserve(Nnumbers);
	for(auto i=0; i<Nnumbers; ++i) {
		data.push_back(rand.get());
	}
	return(data);
}
