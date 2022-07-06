#include <iostream>
#include <iomanip>
#include <vector>
#include <random>
#include <algorithm>

#include "unionfind.hpp"

class BondPercolation{
public:
    int L, N;
    double p;
    UnionFind uf;

    BondPercolation(int l, double prob);
    int pos2idx(int ix, int iy);
    std::vector<int> idx2pos(int i);
    void connect(int i, int j, std::mt19937& mt);
    void one_step(std::mt19937& mt);
    double percolation_probability();
    double average_cluster_size();
    int cluster_number();
    void mc(int n_loop);
};

BondPercolation::BondPercolation(int l, double prob)
{
    L = l;
    N = l * l;
    p = prob;
    uf.init(N);
}

int BondPercolation::pos2idx(int ix, int iy)
{
    ix = (ix + L) % L;
    iy = (iy + L) % L;
    return ix + iy * L;
}

std::vector<int> BondPercolation::idx2pos(int i)
{
    int ix = i % L;
    int iy = (i - ix) % L;
    return std::vector<int> {ix, iy};
}

void BondPercolation::connect(int i, int j, std::mt19937& mt)
{
    std::uniform_real_distribution<> dist(0.0, 1.0);
    if (dist(mt) <= p) uf.unite(i, j);
}

void BondPercolation::one_step(std::mt19937& mt)
{
    uf.init(N);
    for(int iy=0; iy<L-1; iy++)
    {
        for (int ix=0; ix<L-1; ix++)
        {
            int i = pos2idx(ix, iy);
            connect(i, pos2idx(ix + 1, iy), mt);
            connect(i, pos2idx(ix, iy + 1), mt);
        }
    }
}

double BondPercolation::percolation_probability()
{
    int max_cluster_size = uf.maxSize();
    // std::cout << "    max_cluster_size: " << max_cluster_size << std::endl;
    return static_cast<double>(max_cluster_size) / N;
}

double BondPercolation::average_cluster_size()
{
    std::vector<int> sizes = uf.allSize();
    long long int moment1 = 0;
    long long int moment2 = 0;
    for (int s: sizes)
    {
        moment1 += s;
        moment2 += s*s;
    }
    return static_cast<double>(moment2) / static_cast<double>(moment1);
}

int BondPercolation::cluster_number()
{
    return uf.Roots().size();
}

void BondPercolation::mc(int n_loop)
{
    std::mt19937 mt;
    double pp = 0.0;
    double Sp = 0.0;
    for (int i=0; i<n_loop; i++)
    {
        one_step(mt);
        pp += percolation_probability();
        Sp += average_cluster_size();
    }
    pp = pp / static_cast<double>(n_loop);
    Sp = Sp / static_cast<double>(n_loop);
    std::cout << std::fixed << std::setprecision(15) << p << " " << pp << " " << Sp << std::endl;
}