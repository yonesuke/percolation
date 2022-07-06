#include <vector>
#include <utility>
#include <map>

class UnionFind{
public:
    int n;
    std::vector<int> parents;

    UnionFind() {};
    UnionFind(int num);
    void init(int num);
    int findRoot(int x);
    bool unite(int x, int y);
    int setSize(int x);
    bool isSame(int x, int y);
    std::vector<int> setMember(int x);
    std::vector<int> Roots();
    int maxSize();
    std::vector<int> allSize();
    std::map<int, std::vector<int>> AllGroupMap();
    std::vector<std::vector<int>> AllGroupVec();
};

UnionFind::UnionFind(int num)
{
    n = num;
    parents.assign(n, -1);
}

void UnionFind::init(int num)
{
    n = num;
    parents.assign(n, -1);
}

int UnionFind::findRoot(int x)
{
    if (parents[x] < 0)
    {
        return x;
    }
    else
    {
        parents[x] = findRoot(parents[x]);
        return parents[x];
    }
}

bool UnionFind::unite(int x, int y)
{
    int root_x = findRoot(x);
    int root_y = findRoot(y);
    if (root_x == root_y)
    {
        return false;
    }
    else
    {
        if (parents[root_x] > parents[root_y]) std::swap(root_x, root_y);
        parents[root_x] += parents[root_y];
        parents[root_y] = root_x;
        return true;
    }
}

int UnionFind::setSize(int x)
{
    return -parents[findRoot(x)];
}

bool UnionFind::isSame(int x, int y)
{
    return (findRoot(x) == findRoot(y));
}

std::vector<int> UnionFind::setMember(int x)
{
    int root = findRoot(x);
    std::vector<int> m;
    for (int i=0; i<n; i++)
    {
        if (parents[i] == root) m.push_back(i);
    }
    return m;
}

std::vector<int> UnionFind::Roots()
{
    std::vector<int> roots;
    for (int i = 0; i<n; i++)
    {
        if (parents[i] < 0) roots.push_back(i);
    }
    return roots;
}

int UnionFind::maxSize()
{
    std::vector<int> roots = Roots();
    int max_size = 0;
    for (int i=0; i<roots.size(); i++)
    {
        int size = -parents[roots[i]];
        if (size > max_size) max_size = size;
    }
    return max_size;
}

std::vector<int> UnionFind::allSize()
{
    std::vector<int> sizes;
    for (int i=0; i<n; i++)
    {
        if (parents[i] < 0) sizes.push_back(-parents[i]);
    }
    return sizes;
}

std::map<int, std::vector<int>> UnionFind::AllGroupMap()
{
    std::map<int, std::vector<int>> g;
    for (int i=0; i<n; i++)
    {
        int root = findRoot(i);
        if (g.count(root)) g.at(root).push_back(i);
        else g[root] = std::vector<int> {i};
    }
    return g;
}

std::vector<std::vector<int>> UnionFind::AllGroupVec()
{
    std::map<int, std::vector<int>> g = AllGroupMap();
    std::vector<std::vector<int>> g_vec;
    for (const auto &item : g)
    {
        g_vec.push_back(item.second);
    }
    return g_vec;
}