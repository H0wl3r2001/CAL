/*
 * Graph.h
 */
#ifndef GRAPH_H_
#define GRAPH_H_

#include <vector>
#include <queue>
#include <stack>
#include "MutablePriorityQueue.h"
#include <limits>
#include "DeliveryMan.h"
#include "Time.h"
#include <algorithm>

#define INF std::numeric_limits<double>::max()

template <class T>
class Edge;
template <class T>
class Graph;
template <class T>
class Vertex;

class Result;

/****************** Provided structures  ********************/

template <class T>
class Vertex
{
    unsigned int id;
    T info;                     // contents
    std::vector<Edge<T> *> adj; // list of outgoing edges

    //dijsktra
    Vertex<T> *path = NULL;
    double dist = 0.0;
    int queueIndex = 0;

    //path calc
    bool in_path = false;

    void addEdge(const unsigned int &id, Vertex<T> *dest, const double &w);
    bool operator<(Vertex<T> &vertex) const; // required by MutablePriorityQueue

public:
    T getInfo() const;
    Vertex(const unsigned int &id, const T &in);
    friend class Graph<T>;
    friend class MutablePriorityQueue<Vertex<T>>;
};

template <class T>
class Edge
{
    unsigned int id;
    Vertex<T> *dest; // destination vertex
    double weight;   // edge weight
public:
    bool operator<(const Edge<T> &rhs) const;
    Edge(const unsigned int &id, Vertex<T> *d, const double &w);
    friend class Graph<T>;
    friend class Vertex<T>;
};

template <class T>
class Graph
{
    std::vector<Vertex<T> *> vertexSet = std::vector<Vertex<T> *>(); // vertex set

public:
    Vertex<T> *findVertex(const unsigned int &id) const;
    Edge<T> *findEdge(const unsigned int &id) const;
    int getNumVertex() const;
    bool addVertex(const unsigned int &id, const T &in);
    bool addEdge(const unsigned int &id, const unsigned int &sourc_id, const unsigned int &dest_id, const double &w);
    void dijkstraShortestPath(const unsigned int &origin_id);

    void resetGraph();

    //Alg
    Result minPath(DeliveryMan dm);
    void printPath(const unsigned int &from, const unsigned int &to) const;
    std::vector<unsigned> getAnimationDataPath(const unsigned int &from, const unsigned int &to) const;
};

/****************** Provided constructors and functions ********************/

template <class T>
Vertex<T>::Vertex(const unsigned int &id, const T &in) : info(in), id(id) {}

template <class T>
bool Vertex<T>::operator<(Vertex<T> &vertex) const
{
    return this->dist < vertex.dist;
}

template <class T>
T Vertex<T>::getInfo() const
{
    return this->info;
}

template <class T>
Edge<T>::Edge(const unsigned int &id, Vertex<T> *d, const double &w) : id(id), dest(d), weight(w) {}

template <class T>
int Graph<T>::getNumVertex() const
{
    return vertexSet.size();
}

template <class T>
Vertex<T> *Graph<T>::findVertex(const unsigned int &id) const
{
    for (Vertex<T> *v : this->vertexSet)
        if (v->id == id)
            return v;
    return NULL;
}

template <class T>
Edge<T> *Graph<T>::findEdge(const unsigned int &id) const
{
    for (Vertex<T> *v : this->vertexSet)
    {
        for (Edge<T> *e : v->adj)
        {
            if (e->id == id)
                return e;
        }
    }
    return NULL;
}

template <class T>
bool Graph<T>::addVertex(const unsigned int &id, const T &in)
{
    if (this->findVertex(id) != NULL)
        return false;
    this->vertexSet.push_back(new Vertex<T>(id, in));
    return true;
}

template <class T>
bool Graph<T>::addEdge(const unsigned int &id, const unsigned int &sourc_id, const unsigned int &dest_id, const double &w)
{
    if (this->findEdge(id) != NULL)
        return false;
    if (sourc_id == dest_id)
        return false;
    Vertex<T> *sr = this->findVertex(sourc_id);
    Vertex<T> *des = this->findVertex(dest_id);
    if (sr == NULL || des == NULL)
        return false;
    sr->addEdge(id, des, w);
    return true;
}

template <class T>
void Vertex<T>::addEdge(const unsigned int &id, Vertex<T> *d, const double &w)
{
    this->adj.push_back(new Edge<T>(id, d, w));
}

template <class T>
void Graph<T>::dijkstraShortestPath(const unsigned int &origin_id)
{
    Vertex<T> *vertex = this->findVertex(origin_id);
    for (Vertex<T> *v : this->vertexSet)
    {
        v->path = NULL;
        v->dist = INF;
        v->queueIndex = 0;
    }
    vertex->dist = 0;

    MutablePriorityQueue<Vertex<T>> que;
    que.insert(vertex);

    while (!que.empty())
    {
        Vertex<T> *v = que.extractMin();

        for (Edge<T> *edge : v->adj)
        {
            Vertex<T> *ve = edge->dest;
            if (ve->dist > v->dist + edge->weight)
            {
                ve->dist = v->dist + edge->weight;
                ve->path = v;
                if (edge->dest->queueIndex)
                {
                    que.decreaseKey(ve);
                }
                else
                {
                    que.insert(ve);
                }
            }
        }
    }
}

template <class T>
void Graph<T>::resetGraph()
{
    for (Vertex<T> *v : this->vertexSet)
    {
        v->path = NULL;
        v->dist = INF;
        v->queueIndex = 0;
        v->in_path = false;
    }
}

template <class T>
std::vector<unsigned> Graph<T>::getAnimationDataPath(const unsigned int &from, const unsigned int &to) const {
    std::vector<unsigned> res;
    Vertex<T> *destV = this->findVertex(to);
    Vertex<T> *fromV = this->findVertex(from);
    res.push_back(to);
    while (true)
    {
        Vertex<T> * ant = destV->path;
        if (ant == NULL)
            break;
        for (Edge<T> *edg : ant->adj)
        {
            if (edg->dest == destV)
            {
                res.push_back(edg->id);
                break;
            }
        }
        destV = ant;
    }
    res.push_back(from);

    std::reverse(res.begin(), res.end());

    return res;
}

template <class T>
bool Edge<T>::operator<(const Edge<T> &rhs) const
{
    return this->weight < rhs.weight;
}

/**
 * @brief Class that represents a result from the min path algorithm
 */
class Result
{
private:
    /**
     * @brief Total trip time
     */
    Time totalTime;
    /**
     * @brief Total delay
     */
    int totalDelay;
    /**
     * @brief result path data that will be used to draw the animation
     *
     * @note format - [idOfInitVertex, [...idOfEdges], [idOfEndVertex]] - each of these vectors cooresponds to a travel between 2 delivery places (does not include intermediate nodes data)
     */
    std::vector<std::vector<unsigned>> pathAnimationData;

public:
    Result(const Time &totalTime, const int &totalDelay, const std::vector<std::vector<unsigned>>& pathAnimationData);

    Result(const Time &totalTime, const int &totalDelay);

    friend std::ostream &operator<<(std::ostream &os, const Result &r);

    /**
     * @brief Calculates the avr result of a group of results
     *
     * @param results vector of results
     * @return Result average result
     */
    friend Result calculateAvgResult(const std::vector<Result>& results);

    Time getTotalTime() const;

    int getTotalDelay() const;

    std::vector<std::vector<unsigned>> getPathAnimationData() const;
};



#endif /* GRAPH_H_ */
