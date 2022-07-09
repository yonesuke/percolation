#include "percolation.hpp"

int main(int argc, char *argv[])
{
    // type 0: percolation probability
    // type 1: average cluster size
    // type 2: finite average cluster size
    int type = atoi(argv[1]);
    int L = atoi(argv[2]);
    int n_iter = atoi(argv[3]);

    double dp = 0.02;
    int n_p = 50;
    for (int i=0; i<=n_p; i++)
    {
        double p = dp * i;
        BondPercolation model(L, p);
        model.mc(type, n_iter);
    }
}