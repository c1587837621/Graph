#include <iostream>
#define maxWeight  5
#define maxVertices 10

using namespace std;

//template<class T>
//class Vertices
//{
//private:
//    int numVertices;
//    T data;
//};

template<class T, class E>
class Graphmtx
{
private:
//    friend ostream& operator << (ostream &os, Graphmtx<T,E> &G);
//    friend istream& operator >> (istream &in, Graphmtx<T,E> &G);
    T *VerticesList;
    E **Edge;
    int numVertices;
    int numEdge;
    int getVertex(T vertex)
    {
        for(int i=0; i<numVertices; i++)
        {
            if(VerticesList[i]==vertex)return i;
            return -1;
        }
    }
public:
/*  ***********************************************************************************************  */
    Graphmtx(int m_numVertices = 0)
    {
        numVertices = m_numVertices;
        numEdge = 0;
        //int maxWeight = m_maxWeight;
        VerticesList = new T[maxVertices];
        //Edge = new E*[numVertices];    //?????
        Edge = (E**) new E *[maxVertices];
        for(int i=0; i<maxVertices; i++)    //numVertices
        {
            Edge[i] = new E[maxVertices];
        }
        for(int i=0; i<maxVertices; i++)      //numVertices
        {
            for(int j=0; j<maxVertices; j++)
            {
                Edge[i][j] = (i==j)? 0:maxWeight;
            }
        }
    }
/*  ***********************************************************************************************  */
    ~Graphmtx(){
        delete []VerticesList;
        delete []Edge;
    }
/*  ***********************************************************************************************  */
    T getvalue(int i);
    int getFirstNeibor(int v);
    int getWeight(int v1, int v2);
    int getNextNeighbor(int v, int w);
    bool insertVertex(const T&vertex);
    bool insertEdge(int v1, int v2, E cost);
    bool removeVertex(int v);
    bool removeEdge(int v1, int v2);
    int getnumVertex(){return numVertices;}
    int getnumEdge(){return numEdge;}
/*  ***********************************************************************************************  */
    friend istream& operator >> (istream &in, Graphmtx<T,E> &G)
    {
        int n = 5;                            // int n = G.getnumVertex();
        int m = 4;                            //int m = G.getnumEdge(); //顶点数n， 边数m
        T e1, e2;
        E weight;
        for(int i=0; i<n; i++)
        {
            in >> e1;
            G.insertVertex(e1);
        }
        int i = 0;
        while(i<m)
        {
            in >> e1 >> e2 >> weight;
            G.insertEdge(e1, e2, weight);
            i++;
        }
        return in;
    }
/*  ***********************************************************************************************  */
    friend ostream& operator << (ostream &os, Graphmtx<T,E> &G)
    {
        int w;
        int n = G.getnumVertex();
        int m = G.getnumEdge();
        os << n << " ," << m << endl;
        int e1, e2;
        for(int i=0; i<n; i++)
        {
            for(int j=0; j<n; j++)
            {
                w = G.getWeight(i,j);
                if(w>0 && w<maxWeight)
                {
                    e1 = G.getvalue(i);
                    e2 = G.getvalue(j);
                    os << "(" << e1 << "," << e2 << "," << w << ")" << endl;
                }
            }
        }
        return os;
    }
};
/*  ***********************************************************************************************  */
template<class T, class E>
T Graphmtx<T,E>::getvalue(int i)
{
    return i<0||i>=numVertices?NULL:VerticesList[i];
}

/*  ***********************************************************************************************  */
template<class T, class E>
int Graphmtx<T,E>::getFirstNeibor(int v)
{
    for(int i=0; i<numVertices; i++)
    {
        if(Edge[v][i]>0)return i;    //////
        return -1;
    }
}

/*  ***********************************************************************************************  */
template<class T, class E>
int Graphmtx<T,E>::getWeight(int v1, int v2)
{
    if(v1>=0&&v1<numVertices&&v2>=0&&v2<numVertices)return Edge[v1][v2];
    return maxWeight;
}

/*  ***********************************************************************************************  */
template<class T, class E>
int Graphmtx<T,E>::getNextNeighbor(int v, int w)
{
    if(v != -1 && w != -1)
        for(int i=w+1; i<numVertices; i++)
    {
        if(Edge[v][i]>0&&Edge[v][i]<maxWeight)return i;
        return -1;
    }
}

/*  ***********************************************************************************************  */
template<class T, class E>
bool Graphmtx<T,E>:: insertVertex(const T&vertex)
{
    if(numVertices==maxVertices)return false;
    VerticesList[numVertices++] = vertex;
    return true;
}

/*  ***********************************************************************************************  */
template<class T, class E>
bool Graphmtx<T,E>::insertEdge(int v1, int v2, E cost)
{
    //if(Edge[v1][v2]==0)return false;
    Edge[v1][v2] = cost;
    numEdge++;
    return true;
}

/*  ***********************************************************************************************  */
template<class T, class E>
bool Graphmtx<T,E>::removeVertex(int v)
{
    if(v<0||v>=numVertices)return false;
    if(numVertices==1)return false;
    VerticesList[v] = VerticesList[maxVertices-1];   //delete
    for(int i=0; i<numEdge; i++)
    {
        if(Edge[v][i]>0&&Edge[v][i]<maxWeight)numEdge--;
    }
    for(int i=0; i<numVertices; i++)
        if(Edge[v][i]>0&&Edge[v][i]<maxWeight)Edge[v][i] = Edge[numVertices][i];   //用最后一行填补第v行
    for(int i=0; i<numVertices; i++)
        Edge[i][v] = Edge[i][numVertices-1];  //用最后一列填补第v列 ？？？？
    numVertices--;
    return true;
}

/*  ***********************************************************************************************  */
template<class T, class E>
bool Graphmtx<T,E>::removeEdge(int v1, int v2)
{
    if(v1>=0&&v1<numVertices&&v2>=0&&v2<numVertices&&Edge[v1][v2]>0&&Edge[v1][v2]<maxWeight)
    {
        Edge[v1][v2] = Edge[v2][v1] = maxWeight;
        numEdge--;
        return true;
    }
    return false;
}


/*  ***********************************************************************************************  */
int main()
{

    Graphmtx<int,int> G;    //测试： 0 1 2 3 4 0 1 1 1 2 1 2 3 1 3 4 1
    cin >> G;
    cout << G;
//    cout << "Hello world!" << endl;
    return 0;
}
