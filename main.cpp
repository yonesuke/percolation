#include <vector>

#include "percolation.hpp"

int main(int argc, char *argv[])
{
    int L = atoi(argv[1]);
    int n_iter = atoi(argv[2]);

    double dp = 0.02;
    int n_p = 50;
    for (int i=0; i<=n_p; i++)
    {
        double p = dp * i;
        BondPercolation model(L, p);
        model.mc(n_iter);
    }
}