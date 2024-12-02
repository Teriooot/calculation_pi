#include <iostream>
#include <chrono>
#include <quadmath.h>
#include <stdint-gcc.h>
#include <cmath>
//#include <omp.h>

using namespace std;
using namespace chrono;

void calculation_pi(uint64_t n, uint32_t amount_threads, __float128* out)
{
	__float128 result = 1;
	auto time_start = high_resolution_clock::now();
    //omp_set_num_threads(amount_threads);

    cout << "n = " << n << endl;

	//отдельные случаи для n == 0 и n == 1
	for (uint64_t i = 1; i <= n / 2; i++)
	{
		result -= (__float128)2 / (__float128)(16 * i * i - 1);
	}
	if (n % 2)
	{
		cout << "ODD" << endl; //убрать

		result -= (__float128)1 / (__float128)n;
	}
	result *= 4;

	auto time_end = high_resolution_clock::now();
	duration<double> time = time_end - time_start;
	cout << "time = " << time.count() << " s" << endl;

	*out = result;
}

int main()
{
	string format = "%.31Qg";

	__float128 calculation_result = 0;
	uint64_t n = 0;
	uint32_t amount_threads = 0;
	uint32_t amount_chars = 0;

	while (true)
	{
		cout << "Enter n: ";
		cin >> n;

		if (n == 0)
		{
			return 0;
		}

		cout << "Enter number of threads: ";
		cin >> amount_threads;

		calculation_pi(n, amount_threads, &calculation_result);

		amount_chars = (uint32_t)quadmath_snprintf(NULL, 0, format.c_str(), calculation_result);
		string out(amount_chars + 1, '\0');
		quadmath_snprintf(&out[0], out.capacity(), format.c_str(), calculation_result);
		cout << out << endl;

		cout << endl;
	}

	return 0;
}
