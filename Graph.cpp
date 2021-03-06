#include "Graph.h"
#include "DeliveryPlace.h"
#include <iostream>
#include <vector>
#include <tuple>
#include <algorithm>

/**
 * @brief Prints the path from node with id \p from to node with id \p to generated by the dijkstra algorithm
 *
 * @tparam DeliveryPlace
 * @param from node id from
 * @param to node id to
 */
template <>
void Graph<DeliveryPlace>::printPath(const unsigned int &from, const unsigned int &to) const
{
    std::vector<DeliveryPlace> res;
    Vertex<DeliveryPlace> *destV = this->findVertex(to);
    Vertex<DeliveryPlace> *fromV = this->findVertex(from);
    while (destV->path != fromV)
    {
        res.push_back(destV->info);
        destV = destV->path;
    }
    res.push_back(destV->info);
    res.push_back(fromV->info);
    std::reverse(res.begin(), res.end());

    std::cout << "Path: ";
    for (size_t i = 0; i != res.size(); i++)
    {
        std::cout << res[i].getName() << ((i == res.size() - 1) ? "." : " -> ");
    }
    std::cout << std::endl;
}

/**
 * @brief Greedy algorithm that calculates the minimum path in this TIMEWINDOW problem
 *
 * @tparam DeliveryPlace
 */
template <>
Result Graph<DeliveryPlace>::minPath(DeliveryMan dm)
{
    int total_delay = 0;

    unsigned int working_node = 0;
    Time current_time = this->findVertex(0)->info.getIdealTime(); // initial node = node 0 - padaria
    Time initial_time = current_time;

    std::vector<std::vector<unsigned>> pathAnimationData;

    std::cout << "--------------------------------------------------------------------------" << std::endl;
    std::cout << "Padeiro named " << dm.getName() << " with capacity " << dm.getCapacity() << "." << std::endl;
    std::cout << "Starting at Padaria at " << current_time << "." << std::endl
              << std::endl;

    std::vector<Vertex<DeliveryPlace> *> vertCopy = std::vector<Vertex<DeliveryPlace> *>();
    for (Vertex<DeliveryPlace> *v : this->vertexSet)
    {
        if (v->info.getIdealTime() != Time() && !v->in_path && v->id != 0)
        {
            vertCopy.push_back(v);
        } // Copy the list of nodes and remove those that are intermediate nodes represented by time 00:00 or already in path or with id 0 (PADARIA)
    }

    do
    {
        this->dijkstraShortestPath(working_node); //dijkstra to find all paths from the current node

        std::tuple<Vertex<DeliveryPlace> *, double, unsigned> short_path = {NULL, INF, 0}; // Tuple with information (closest possible vertex, time to travel to that vertex, vertex id)

        for (std::vector<Vertex<DeliveryPlace> *>::iterator it = vertCopy.begin(); it < vertCopy.end(); it++) // go through all vertex
        {
            if ((*it)->dist < std::get<1>(short_path) && !(*it)->in_path && (*it)->id != working_node && (*it)->info.inTime(current_time + (*it)->dist) && dm.getCapacity() >= (*it)->info.getBreadQuatity())
            {                                                                                //if the vertex is NOT the PADARIA and NOT the current VERTEX and Closest than the current known one
                short_path = {(*it), (*it)->dist, (*it)->id}; //choose that vertex
            }
            else if ((*it)->in_path || (*it)->id == working_node)
            { //erase from the vertor the current vertex and the ones that have entered the path since the start
                vertCopy.erase(it);
                it--;
            }
        } // Basicaly calculate the closest vertex

        if (std::get<0>(short_path) == NULL) // if no path was find then the journey is done
            break;

        dm.reduceCapacity(std::get<0>(short_path)->info.getBreadQuatity());

        current_time = std::max(current_time + (int)std::get<1>(short_path), std::get<0>(short_path)->getInfo().getMinTime()); //change the current time to after the trip
        // add to the total delay
        total_delay += (std::get<0>(short_path)->getInfo().getIdealTime() > current_time ? (std::get<0>(short_path)->getInfo().getIdealTime() - current_time).getTotalMinutes() : (current_time - std::get<0>(short_path)->getInfo().getIdealTime()).getTotalMinutes());
        std::get<0>(short_path)->in_path = true; // add vertex to the inPath list (already visited and delivered)

        std::cout << "Got to " << std::get<0>(short_path)->getInfo() << " at " << current_time << " delivered " << std::get<0>(short_path)->info.getBreadQuatity() << " bread"
                  << " leaving at ";
        current_time = current_time + dm.getDeliveryTime(); // add the delivery time from the delivery man to the timer
        std::cout << current_time << ". " << dm.getName() << " has capacity " << dm.getCapacity() << "." << std::endl;

        this->printPath(working_node, std::get<2>(short_path)); // print the path
        pathAnimationData.push_back(this->getAnimationDataPath(working_node, std::get<2>(short_path)));
        std::cout << std::endl;

        working_node = std::get<2>(short_path); // change working node to the one where the delivery occurred

    } while (true);

    this->dijkstraShortestPath(working_node);                // dijkstra from the last delivery back to the padaria
    current_time = current_time + this->findVertex(0)->dist; // add that time
    std::cout << "Got back to Padaria at " << current_time << "." << std::endl;
    this->printPath(working_node, 0);
    pathAnimationData.push_back(this->getAnimationDataPath(working_node, 0));

    Result r(current_time - initial_time, total_delay, pathAnimationData);

    std::cout << std::endl << r;
    std::cout << "--------------------------------------------------------------------------" << std::endl;

    return r;
    // O(|V| * (|V| + |E|) * log |V|) - WORST CASE
}

Result::Result(const Time& totalTime, const int& totalDelay, const std::vector<std::vector<unsigned>>& pathAnimationData) {
    this->totalDelay = totalDelay;
    this->totalTime = totalTime;
    this->pathAnimationData = pathAnimationData;
}

Result::Result(const Time& totalTime, const int& totalDelay) {
    this->totalDelay = totalDelay;
    this->totalTime = totalTime;
}

std::ostream& operator<<(std::ostream& os, const Result& r) {
    os << "TOTAL TIME: " << r.totalTime << std::endl;
    os << "TOTAL DELAY: " << r.totalDelay << std::endl;
    return os;
}

Result calculateAvgResult(const std::vector<Result>& results) {
    unsigned totalMinutes = 0;
    int totalDelay = 0;
    for (Result r : results) {
        totalMinutes += r.totalTime.getTotalMinutes();
        totalDelay += r.totalDelay;
    }

    Time avgTime = Time(totalMinutes / results.size());
    int avgDelay = totalDelay / results.size();

    return Result(avgTime, avgDelay);
}

Time Result::getTotalTime() const {
    return this->totalTime;
}

int Result::getTotalDelay() const {
    return this->totalDelay;
}

std::vector<std::vector<unsigned>> Result::getPathAnimationData() const {
    return this->pathAnimationData;
}
