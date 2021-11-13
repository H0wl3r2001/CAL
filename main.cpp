#include <iostream>
#include <queue>
#include "MyGraphViewer.h"
#include "Time.h"
#include "DeliveryPlace.h"
#include "Place.h"
#include "DeliveryMan.h"

int main()
{
    // CREATE GRAPH
    MyGraphViewer gv(800, 600);

    // NODES
    gv.addPadaria(sf::Vector2f(-300, -100));
    gv.addNode(1, DeliveryPlace(Time(10, 0), "Entrega B", 10), sf::Vector2f(-100, 100));
    gv.addNode(2, DeliveryPlace(Time(9, 0), "Entrega A", 100), sf::Vector2f(100, -200));
    gv.addNode(3, DeliveryPlace(Time(10, 5), "Entrega C", 10), sf::Vector2f(300, 100));
    gv.addNode(4, Place(), sf::Vector2f(-300, 200));

    // BIDIRECTIONAL EDGES
    gv.addUnDirEdge(1, 2, 1, 2, 5 * 60);
    gv.addUnDirEdge(3, 4, 0, 1, 3 * 60);
    gv.addUnDirEdge(7, 8, 2, 3, 5 * 60);
    gv.addUnDirEdge(9, 10, 1, 3, 5);
    gv.addUnDirEdge(5, 6, 0, 4, 60);
    gv.addUnDirEdge(11, 12, 4, 2, 60);

    // DIRECTIONAL EDGES
    gv.addDirEdge(13, 2, 0, 60);

    // DELIVERY MANS
    DeliveryMan dm1("Manel", 10, 10);
    DeliveryMan dm2("Jao", 100, 5);

    std::priority_queue<DeliveryMan> q;
    q.push(dm1);
    q.push(dm2);

    // CALCULATE MIN PATH FROM EACH DELIVERY MAN
    gv.minPath(q);

    // RESET THE GRAPH
    gv.resetGraph();

    // JOIN THE EXECUTION THREAD
    gv.join();
}
