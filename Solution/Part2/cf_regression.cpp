#include "cf_regression.h"
#include "gauss.h"

#define SEIDEL_ITER 10

int g_order;

Gauss g_seidel, g_elemination;

void cf_regression::fit_polyreg(std::vector<float> x, 
	std::vector<float> y, const int order) {
    g_order = order;
    int k = 0;
    const int n = x.size();
    float sum = 0.0;

    const int rows = order + 1;
    const int cols = order + 2;

    float** arrnd = new float* [rows];

    for (int i = 0; i < rows; ++i) {
        arrnd[i] = new float[cols];
    }

    for (int i = 0; i < (order + 1); i++) {
        for (int j = 0; j <= i; j++) {
            k = i + j;
            sum = 0.0;

            for (int l = 0; l < n; l++) {
                sum += std::powf(x[l], k);
            }

            arrnd[i][j] = sum;
            arrnd[j][i] = sum;
        }

        sum = 0.0;

        for (int l = 0; l < n; l++) {
            sum += (y[l] * std::powf(x[l], i));
        }

        arrnd[i][order + 1] = sum;
    }

    for (int i = 0; i < (order + 1); i++) {
        for (int j = 0; j < (order + 2); j++) {
            std::cout << arrnd[i][j] << " ";
        }

        std::cout << std::endl;
    }

    std::cout << std::endl;

    g_seidel.ImportSource(arrnd, rows);
    g_seidel.ApplySeidel(SEIDEL_ITER);

    for (int i = 0; i < g_seidel.nd; i++) {
        std::cout << g_seidel.result[i] << std::endl;
    }

    std::cout << std::endl;

    g_elemination.ImportSource(arrnd, rows);
    g_elemination.Apply_Elimination();

    for (int i = 0; i < g_elemination.nd; i++) {
        std::cout << g_elemination.result[i] << std::endl;
    }

    delete arrnd;
}

void cf_regression::predict_polyreg(float x) {
    float x_val = 0.0;

    for (int i = 0; i < g_order; i++) {
        x_val += (g_seidel.result[i] * std::pow(x, i));
    }

    std::cout << "[Seidel] Y for X = " 
        << x << ": " << x_val << std::endl;

    x_val = 0.0;

    for (int i = 0; i < g_order; i++) {
        x_val += (g_elemination.result[i] * std::pow(x, i));
    }

    /*std::cout << "[elimination] Y for X = " 
        << x << ": " << x_val << std::endl;*/
}

void cf_regression::fit_mlreg(std::vector<std::vector<float>> x, 
	std::vector<float> y, const int order) {
    int n = y.size();
    float sum = 0.0;

    const int rows = order + 1;
    const int cols = order + 2;

    float** arrnd = new float* [rows];

    for (int i = 0; i < rows; ++i) {
        arrnd[i] = new float[cols];
    }

    for (int i = 0; i < order; i++) {
        for (int j = 0; j <= i; j++) {
            sum = 0.0;

            for (int l = 0; l < n; l++) {
                sum += (x[i][l] * x[j][l]);
            }

            arrnd[i][j] = sum;
            arrnd[j][i] = sum;
        }

        sum = 0.0;

        for (int l = 0; l < n; l++) {
            sum += (y[l] * x[i][l]);
        }

        arrnd[i][order + 1] = sum;
    }

    g_seidel.ImportSource(arrnd, rows);
    g_seidel.ApplySeidel(SEIDEL_ITER);

    g_elemination.ImportSource(arrnd, rows);
    g_elemination.Apply_Elimination();

    delete arrnd;
}

void cf_regression::predict_mlreg(float x) {
    float x_val = 0.0;

    for (int i = 0; i < g_order; i++) {
        x_val += (g_seidel.result[i] * std::pow(x, i));
    }

    std::cout << "[Seidel] Y for X = "
        << x << ": " << x_val << std::endl;

    x_val = 0.0;

    for (int i = 0; i < g_order; i++) {
        x_val += (g_elemination.result[i] * std::pow(x, i));
    }

    std::cout << "[elimination] Y for X = "
        << x << ": " << x_val << std::endl;
}