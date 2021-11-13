#pragma once
#include "graphviewer.h"
#include "Graph.h"
#include "DeliveryMan.h"
#include "DeliveryPlace.h"
#include <queue>

/**
 * @brief Class that joins the GraphViewer and Graph classes
 *
 */
class MyGraphViewer : public GraphViewer, public Graph<DeliveryPlace>
{
public:
    /**
     * @brief Construct a new My Graph Viewer object
     *
     * @param width width of the window
     * @param height height of the window
     */
    MyGraphViewer(const unsigned int &width, const unsigned int &height);

    /**
     * @brief Adds a node with id its informations and its position on the GraphViewer
     *
     * @param id id of the node
     * @param info information of the node
     * @param position position of the node on the GraphViewer
     */
    void addNode(const unsigned int &id, const DeliveryPlace &info, const sf::Vector2f &position);
    /**
     * @brief Adds the PADARIA, its informations and its position on the GraphViewer
     *
     * @param position position of the node on the GraphViewer
     */
    void addPadaria(const sf::Vector2f &position);
    /**
     * @brief Adds two edges with their information to the graph. (Undirectional)
     *
     * @param edge_id_to id of the edge heading "forward".
     * @param edge_id_from id of the edge heading "backwards".
     * @param from_id id to create the node of origin.
     * @param to_id id to create the node of destination.
     * @param w weight of the resulting edge, in minutes in this case. (NOT NEGATIVE)
     */
    void addUnDirEdge(const unsigned int &edge_id_to, const unsigned int &edge_id_from, const unsigned int &from_id, const unsigned int &to_id, const unsigned int &w);
    /**
     * @brief Adds one directional edge with their information to the graph
     *
     * @param edge_id_to id of the edge heading.
     * @param from_id id to create the node of origin.
     * @param to_id id to create the node of destination.
     * @param w weight of the resulting edge, in minutes in this case. (NOT NEGATIVE)
     */
    void addDirEdge(const unsigned int &edge_id_to, const unsigned int &from_id, const unsigned int &to_id, const unsigned int &w);

    /**
     * @brief Calculates the minPath for this TIMEWINDOW Delivery problem
     *
     * @param dm Delivery Man to calculate min path on. Copy of it.
     */
    void minPath(std::priority_queue<DeliveryMan> dm);

    /**
     * @brief Visualizes the path that will be performed by the deliveryMen in dm
     *
     * @param results Results to fetch the information from.
     * @param dm Delivery Man to draw the data from. Copy of the original.
     */
    void visualizePath(const std::vector<Result>& results, std::priority_queue<DeliveryMan> dm);
};
