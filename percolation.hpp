#include <iostream>
#include <iomanip>
#include <vector>
#include <set>
#include <cmath>
#include <random>
#include <algorithm>

#include "unionfind.hpp"
#include "utils.hpp"

class BondPercolation{
public:
    int L, N;
    double p;
    UnionFind uf;

    BondPercolation(int l, double prob);
    int pos2idx(int ix, int iy);
    void connect(int i, int j, std::mt19937& mt);
    void one_step(std::mt19937& mt);
    double percolation_probability();
    double average_cluster_size();
    double finite_average_cluster_size();
    void mc(int type, int n_loop);
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
    for (int k=0; k<L-1; k++)
    {
        connect(pos2idx(L-1, k), pos2idx(L-1, k+1), mt);
        connect(pos2idx(k, L-1), pos2idx(k+1, L-1), mt);
    }
}

double BondPercolation::percolation_probability()
{
    int max_cluster_size = uf.maxSize();
    return static_cast<double>(max_cluster_size) / N;
}

double BondPercolation::average_cluster_size()
{
    std::vector<int> sizes = uf.allSize();
    long long int moment2 = 0;
    for (int s: sizes) moment2 += s*s;
    return static_cast<double>(moment2) / N;
}

double BondPercolation::finite_average_cluster_size()
{
    std::set<int> parents_north, parents_east, parents_west, parents_south;
    for (int i=0; i<L; i++)
    {
        parents_north.insert(uf.findRoot(pos2idx(i, 0)));
        parents_east.insert(uf.findRoot(pos2idx(L-1, i)));
        parents_west.insert(uf.findRoot(pos2idx(0, i)));
        parents_south.insert(uf.findRoot(pos2idx(i, L-1)));
    }
    std::set<int> parents_ns, parents_ew;
    std::set_intersection(
        parents_north.begin(), parents_north.end(),
        parents_south.begin(), parents_south.end(),
        std::inserter(parents_ns, parents_ns.end())
    );
    std::set_intersection(
        parents_east.begin(), parents_east.end(),
        parents_west.begin(), parents_west.end(),
        std::inserter(parents_ew, parents_ew.end())
    );
    std::set<int> parents_percolate;
    std::set_union(
        parents_ns.begin(), parents_ns.end(),
        parents_ew.begin(), parents_ew.end(),
        std::inserter(parents_percolate, parents_percolate.end())
    );
    std::vector<int> roots = uf.Roots();
    std::set<int> finite_roots;
    std::set_difference(
        roots.begin(), roots.end(),
        parents_percolate.begin(), parents_percolate.end(),
        std::inserter(finite_roots, finite_roots.end())
    );
    long long int moment2 = 0;
    for (int root: finite_roots) moment2 += std::pow(-uf.parents[root], 2);
    return static_cast<double>(moment2) / N;
}

void BondPercolation::mc(int type, int n_loop)
{
    std::mt19937 mt;
    std::vector<double> observables;
    if (type == 0)
    {
        for (int i=0; i<n_loop; i++)
        {
            one_step(mt);
            observables.push_back(percolation_probability());
        }
    }
    else if (type == 1)
    {
        for (int i=0; i<n_loop; i++)
        {
            one_step(mt);
            observables.push_back(average_cluster_size());
        }
    }
    else if (type == 2)
    {
        for (int i=0; i<n_loop; i++)
        {
            one_step(mt);
            observables.push_back(finite_average_cluster_size());
        }
    }
    
    std::cout << std::fixed << std::setprecision(15) << L << " " << p << " " << mean(observables) << " " << interval(observables) << std::endl;
}