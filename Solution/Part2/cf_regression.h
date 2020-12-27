#include <iostream>
#include <vector>

class cf_regression {
public:
	static void fit_polyreg(std::vector<float> x, std::vector<float> y, const int order);
	static void predict_polyreg(float x);

	static void fit_mlreg(std::vector<std::vector<float>> x, std::vector<float> y, const int order);
};