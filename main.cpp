#include <iostream>
 #define maxWeight  10
// #define maxVertices 10

 using namespace std;


 template<class T, class E>
 class Graphmtx
 {
 protected:
    virtual int getVertexPos(T vertex);
 private:
 //    friend ostream& operator << (ostream &os, Graphmtx<T,E> &G);
 //    friend istream& operator >> (istream &in, Graphmtx<T,E> &G);
     T *VerticesList;
     E **Edge;
     int maxVertices;
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
     Graphmtx(int m_maxVertices)
     {
         numVertices = 0;
         numEdge = 0;
         maxVertices = m_maxVertices;
         //int maxWeight = m_maxWeight;
         VerticesList = new T[maxVertices];
         Edge = new E*[numVertices];    //?????
         //Edge = (E**) new E *[maxVertices];
         for(int i=0; i<maxVertices; i++)
         {
             Edge[i] = new E[maxVertices];
         }
         for(int i=0; i<maxVertices; i++)
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
     //int NumberOfVertices();
     //int NumberOfEdge();

 /*  *深度优先搜索**********************************************************************************  */
//     void DFS(Graphmtx<T,E> &G, const T&v);
//     void DFS(Graphmtx<T,E> &G, const T&v, bool visited[]);
     void DFS( const T&v);
     void DFS( const T&v, bool visited[]);

 /*  ***********************************************************************************************  */
     friend istream& operator >> (istream &in, Graphmtx<T,E> &G)
     {
         int n, m; //顶点数n， 边数m
         in >> n >> m;
         T e1, e2;
         E weight;
         for(int i=0; i<n; i++)
         {
             in >> e1;
             G.insertVertex(e1);
         }
         int i = 0;
         int j, k;  //已插入顶点的索引,建立顶点之间边的weight
         while(i<m)
         {
             in >> e1 >> e2 >> weight;
             j = G.getVertexPos(e1);
             k = G.getVertexPos(e2);
             G.insertEdge(j, k, weight);
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
int Graphmtx<T,E>::getVertexPos(T vertex)
 {
     for(int i=0; i<numVertices; i++)
     {
         if(VerticesList[i]==vertex)
         return i;
     }
     return -1;
 }
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
         if(Edge[v][i]>0&&Edge[v][i]<maxWeight)return i;    //////
     }
     return -1;
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
     }
     return -1;
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
// /*  *深度优先搜索**(main Process)******************************************************************  */
//  template<class T, class E>
//  void Graphmtx<T,E>::DFS(Graphmtx<T,E> &G, const T&v)
//  {
//      int n = G.getnumVertex();
//      bool *visited = new bool[n];
//      for(int i=0; i<n; i++)
//      {
//          visited[i] = false;
//      }
//      int loc = getVertexPos(v);
//      DFS(G, loc, visited);
//      delete []visited;
//  }
// /*  *深度优先搜索**(subProcess)********************************************************************  */
//  template<class T, class E>
//  void Graphmtx<T,E>::DFS(Graphmtx<T,E> &G, const T&w, bool visited[])
//  {
//      cout << G.getvalue(w) << " ";
//      visited[w] = true;
//      int loc;
//      loc = G.getFirstNeibor(w);
//      while(loc!=-1)
//      {
//          if(visited[w]==false)DFS(G, loc, visited);
//          loc = G.getNextNeighbor(w, loc);
//      }
//  }
 /*  *深度优先搜索**(main Process)******************************************************************  */
  template<class T, class E>
  void Graphmtx<T,E>::DFS( const T&v)
  {
      int n = this->getnumVertex();
      bool *visited = new bool[n];
      for(int i=0; i<n; i++)
      {
          visited[i] = false;
      }
      int loc = this->getVertexPos(v);
      DFS( loc, visited);
      delete []visited;
  }
 /*  *深度优先搜索**(subProcess)********************************************************************  */
  template<class T, class E>
  void Graphmtx<T,E>::DFS( const T&w, bool visited[])
  {
      cout << this->getvalue(w) << " ";
      visited[w] = true;
      int loc;
      loc = this->getFirstNeibor(w);
      while(loc!=-1)
      {
          if(visited[loc]==false)DFS(loc, visited);
          loc = this->getNextNeighbor(w, loc);
      }
  }
 /*  ***********************************************************************************************  */
 int main()
 {

     Graphmtx<int,int> G(6);    //测试1： 5 5   0 1 2 3 4    0 1 1  1 2 1  2 3 1  3 4 1  0 4 1
     cin >> G;                  //测试2： 3 3      1 2 3      1 2 1  2 3 2   1 3 4
     cout << G;                 //测试3： 3 3      0 1 2      0 1 1  1 2 2   0 2 4          //顶点的索引与顶点信息分开。

     G.DFS(0);
     return 0;
 }
