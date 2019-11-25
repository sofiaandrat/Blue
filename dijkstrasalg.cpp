#include "dijkstrasalg.h"

DijkstrasAlg::DijkstrasAlg(int townIdx, QVector<QVector<int> > &Table, QVector<int> &pointsOfGraph)
{
    int n = pointsOfGraph.size();
    QVector <QVector <int> > shortestPaths(n, QVector <int>(2, INT_MAX));
    bool visited[n];
    for(int i=0;i<n;i++)
    {
        if(Table[townIdx-1][i]>0)
        {
            shortestPaths[i][0]=Table[townIdx-1][i];
            shortestPaths[i][1]=townIdx;
        }
        visited[i]=false;
    }
    shortestPaths[townIdx-1][0]=0;
    shortestPaths[townIdx-1][1]=0;
    int index=0,u=0;
    for (int i=0;i<n;i++)
    {
        int min=INT_MAX;
        for (int j=0;j<n;j++)
        {
            if (!visited[j] && shortestPaths[j][0]<min)
            {
                min=shortestPaths[j][0];
                index=j;
            }
        }
        u=index;
        visited[u]=true;
        for(int j=0;j<n;j++)
        {
            if (!visited[j] && Table[u][j]!=0 && (shortestPaths[u][0]+Table[u][j]<shortestPaths[j][0]))
            {
                shortestPaths[j][0]=shortestPaths[u][0]+Table[u][j];
                shortestPaths[j][1]=u+1;
            }
        }
    }
    this->townIdx = townIdx;
    this->shortestPaths = shortestPaths;
    shortestPaths.clear();

//    for(int i = 0;i<n;i++)
//    {
//        qDebug() << i+1 << ' ' << this->shortestPaths[i][0] << ' ' << this->shortestPaths[i][1];
//    }
}

QVector<int> DijkstrasAlg::Path(bool fromTown, int pointIdx)
{
    QVector <int> path;
    path.append(pointIdx);
    for(int i = pointIdx-1;shortestPaths[i][1]!=0;i = shortestPaths[i][1]-1)
    {
        path.append(shortestPaths[i][1]);
    }
    if(fromTown)
    {
        int size = path.size();
        QVector <int> temp;
        for(int i = 0;i<size;i++)
        {
            temp.append(path[size-1-i]);
        }
        path.clear();
        path = temp;
        temp.clear();
    }
    return path;
}
