#include "MyGraphViewer.h"
#include <iostream>
#include <chrono>
#include <unistd.h>

MyGraphViewer::MyGraphViewer(const unsigned int &width, const unsigned int &height) : GraphViewer(), Graph<DeliveryPlace>()
{
    this->createWindow(width, height);
}

void MyGraphViewer::addNode(const unsigned int &id, const DeliveryPlace &info, const sf::Vector2f &position)
{
    if (id == 0)
    {
        std::cerr << "You cannot create a node with id 0 - Reserved for the Padaria" << std::endl;
        return;
    }

    if (!Graph<DeliveryPlace>::addVertex(id, info))
    {
        std::cerr << "You cannot create a node with id "<< id << " - Already exists" << std::endl;
        return;
    }

    GraphViewer::Node &node = GraphViewer::addNode(id, position);
    GraphViewer::lock();
    node.setSize(info.getIdealTime() != Time() ? 80 : 20);
    node.setLabel(info.getIdealTime() != Time() ? info.getNameAndTimeWindow() : info.getName());

    if (info.getIdealTime() == Time())
        node.setColor(sf::Color::Yellow);
    GraphViewer::unlock();
}

void MyGraphViewer::addPadaria(const sf::Vector2f &position)
{
    DeliveryPlace info(Time(7, 0), "Padaria");

    if (!Graph<DeliveryPlace>::addVertex(0, info))
    {
        std::cerr << "You cannot create another Padaria - Already exists" << std::endl;
        return;
    }

    GraphViewer::Node &node = GraphViewer::addNode(0, position);
    GraphViewer::lock();
    node.setSize(60);
    node.setLabel(info.getName() + "\n [07:00]");
    node.setColor(GraphViewer::ORANGE);
    GraphViewer::unlock();
}

void MyGraphViewer::addUnDirEdge(const unsigned int &edge_id_to, const unsigned int &edge_id_from, const unsigned int &from_id, const unsigned int &to_id, const unsigned int &w)
{
    if (Graph<DeliveryPlace>::addEdge(edge_id_to, from_id, to_id, w) == false || Graph<DeliveryPlace>::addEdge(edge_id_from, to_id, from_id, w) == false)
    {
        std::cerr << "You cannot create this undirected edge." << edge_id_to << ", " << edge_id_from << " - " << from_id << " | " << to_id << std::endl;
        return;
    }

    GraphViewer::Node &node_from = GraphViewer::getNode(from_id);
    GraphViewer::Node &node_to = GraphViewer::getNode(to_id);

    GraphViewer::Edge &edge = GraphViewer::addEdge(edge_id_to, node_from, node_to, GraphViewer::Edge::UNDIRECTED, edge_id_from);
    GraphViewer::lock();
    edge.setWeight(w);
    edge.setColor(GraphViewer::GRAY);
    GraphViewer::unlock();
}

void MyGraphViewer::addDirEdge(const unsigned int &edge_id_to, const unsigned int &from_id, const unsigned int &to_id, const unsigned int &w)
{
    if (Graph<DeliveryPlace>::addEdge(edge_id_to, from_id, to_id, w) == false)
    {
        std::cerr << "You cannot create this directed edge." << edge_id_to << " - " << from_id << " -> " << to_id << std::endl;
        return;
    }

    GraphViewer::Node &node_from = GraphViewer::getNode(from_id);
    GraphViewer::Node &node_to = GraphViewer::getNode(to_id);

    GraphViewer::Edge &edge = GraphViewer::addEdge(edge_id_to, node_from, node_to, GraphViewer::Edge::DIRECTED);
    GraphViewer::lock();
    edge.setWeight(w);
    edge.setColor(GraphViewer::GRAY);
    GraphViewer::unlock();
}

void MyGraphViewer::minPath(std::priority_queue<DeliveryMan> dm)
{
    std::vector<Result> results;

    std::chrono::_V2::system_clock::time_point start = std::chrono::high_resolution_clock::now();

    std::priority_queue<DeliveryMan> dmCpy = dm;

    while (!dm.empty())
    {
        DeliveryMan d = dm.top();
        dm.pop();
        results.push_back(Graph<DeliveryPlace>::minPath(d));
    }

    std::chrono::_V2::system_clock::time_point stop = std::chrono::high_resolution_clock::now();

    Result r = calculateAvgResult(results);

    std::cout << "AVERAGE TIME: " << r.getTotalTime() << std::endl;
    std::cout << "AVERAGE DELAY: " << r.getTotalDelay() << std::endl;
    std::cout << "EXECUTION TIME: " << std::chrono::duration_cast<std::chrono::milliseconds>(stop - start).count() << " ms" << std::endl;

    std::cout << "--------------------------------------------------------------------------" << std::endl;

    this->visualizePath(results, dmCpy);
}

void MyGraphViewer::visualizePath(const std::vector<Result>& results, std::priority_queue<DeliveryMan> dm) {
    std::cout << "Get path visual representation? (y/n)" << std::endl;
    char c = std::cin.get();

    if (c == 'y')
    {
        for (Result r : results) {
            std::this_thread::sleep_for(std::chrono::seconds(2));
            std::cout << "Path of " << dm.top().getName() << std::endl;
            dm.pop();
            for (std::vector<unsigned> v : r.getPathAnimationData())
            {
                GraphViewer::lock();
                GraphViewer::getNode(v[0]).setColor(GraphViewer::BLUE);
                GraphViewer::unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
                GraphViewer::lock();
                GraphViewer::getNode(v[0]).setColor(v[0] == 0 ? GraphViewer::ORANGE : GraphViewer::RED);
                GraphViewer::unlock();
                for (int i = 1; i < v.size() - 1; i++)
                {
                    GraphViewer::lock();
                    GraphViewer::getEdge(v[i]).setColor(GraphViewer::BLUE);
                    GraphViewer::unlock();
                    std::this_thread::sleep_for(std::chrono::milliseconds(750));
                    GraphViewer::lock();
                    GraphViewer::getEdge(v[i]).setColor(GraphViewer::GRAY);
                    GraphViewer::unlock();
                }
                GraphViewer::lock();
                GraphViewer::getNode(v[v.size() - 1]).setColor(GraphViewer::BLUE);
                GraphViewer::unlock();
                std::this_thread::sleep_for(std::chrono::milliseconds(750));
                GraphViewer::lock();
                GraphViewer::getNode(v[v.size() - 1]).setColor(v[v.size() - 1] == 0 ? GraphViewer::ORANGE : GraphViewer::RED);
                GraphViewer::unlock();
            }
        }
        std::cout << "Visualization finished!" << std::endl;
    }
}
