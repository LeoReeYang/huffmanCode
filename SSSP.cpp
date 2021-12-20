#include <iostream>
#include <fstream>

using namespace std;

const double INF = 99999.9;

double table[42][42];
double dis[42];
bool visited[42];

int pre_point[42];

void way_back(int target, int start, int pre_point[], int pos)
{
    if (target == start)
    {
        cout << start << "->";
        return;
    }
    int deep = pos - 1;
    way_back(pre_point[target], start, pre_point, deep);
    if (pos != 0)
        cout << target << "->";
    else
        cout << target;
}

void way_print(int start, int pre_point[], int pos)
{
    for (int i = 0; i < 22; i++)
        if (i != start)
        {
            way_back(i, start, pre_point, 0);
            cout << endl;
        }
}

void dataInput(double table[][42], string filename, int size)
{
    fstream f(filename, ios::in);
    if (f.is_open())
    {
        double distance;
        for (int i = 0; i < size; i++)
        {
            for (int j = 0; j < size; j++)
            {
                f >> distance;
                table[i][j] = distance;
            }
        }
    }
}

void dijkstra(double table[][42], double dis[], bool visited[], int size, int s) //s为起点
{
    fill(dis, dis + size, INF);
    fill(visited, visited + size, false); //初始化dis和visited数组
    dis[s] = 0;                           //初始化起点距离为0
    pre_point[s] = -1;

    while (true)
    {
        int v = -1;
        for (int u = 0; u < size; u++)
            if (!visited[u] and (v == -1 or dis[u] < dis[v])) //找到可以更新别的点的点v
                v = u;

        if (v == -1) //再也没有可以更新的点
            break;
        visited[v] = true; //v加入已访问集合

        for (int u = 0; u < size; u++)
        {
            dis[u] = min(dis[u], dis[v] + table[u][v]); //从v更新可达点的最短距离}
            if (dis[u] == dis[v] + table[u][v])
                pre_point[u] = v;
        }
    }
}
void print(int size, int pos)
{
    for (int i = 0; i < size; i++)
        cout << dis[i] << endl;
    if (pos == 0)
        cout << "distance from 567443 to 33109: " << dis[pos] << endl;
    else
        cout << "distance from 565845 to 565667: " << dis[pos] << endl; //565845到565667
}

int main()
{
    dataInput(table, "Points_22.txt", 22);
    dijkstra(table, dis, visited, 22, 19); //567443 对应19号点;33109对应0号点（从0到21号）
    print(22, 0);
    way_print(19, pre_point, 0);
    cout << "from 567443 to 33109: ";
    way_back(0, 19, pre_point, 0);
    cout << endl;

    fill(pre_point, pre_point + 42, 0);

    dataInput(table, "Points_42.txt", 42);
    dijkstra(table, dis, visited, 42, 15);
    print(42, 2);
    way_print(15, pre_point, 0);
    cout << "from 565845 to 565667: ";
    way_back(2, 15, pre_point, 0);

    return 0;
}