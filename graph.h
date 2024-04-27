#pragma once

#include <iostream>
#include <stdexcept>
#include <vector>
#include <set>
#include <map>
#include <queue>

using namespace std;

template<typename VertexT, typename WeightT>
class graph {
private:
    struct Edge {
        WeightT cost;
        WeightT time;
    };
    map<VertexT, map<VertexT, Edge>> adjList;
    vector<VertexT> vertices;

public:

    struct PathSignature {
        WeightT cost;
        WeightT time;

        PathSignature(WeightT c, WeightT t) : cost(c), time(t) {}

        bool operator<(const PathSignature& other) const {
            return (cost < other.cost) || (cost == other.cost && time > other.time);
        }
    };

    struct HeapElement {
        PathSignature pathSignature;
        VertexT vertex;

        HeapElement(const PathSignature& ps, const VertexT& v) : pathSignature(ps), vertex(v) {}

        bool operator<(const HeapElement& other) const {
            return pathSignature < other.pathSignature;
        }
    };

    using NonDominatedPathsSet = vector<PathSignature>;

    struct GraphAlgorithmState {
        priority_queue<HeapElement> priorityQueue;
        vector<NonDominatedPathsSet> nonDominatedPaths;

        GraphAlgorithmState(int numVertices) : nonDominatedPaths(numVertices) {}

        void initialize(const VertexT& source) {
            priorityQueue = priority_queue<HeapElement>();
            priorityQueue.push(HeapElement(PathSignature(0, 0), source));

            for (auto& paths : nonDominatedPaths) {
                paths.clear();
            }

            nonDominatedPaths[source].push_back(PathSignature(0, 0));
        }
    };

    graph() {}

    int NumVertices() const {
        return adjList.size();
    }

    int NumEdges() const {
        int count = 0;
        for (const auto& i : adjList) {
            count += i.second.size();
        }
        return count;
    }

    bool addVertex(const VertexT& v) {
        if (adjList.count(v) > 0) {
            return false; // Vertex already exists
        }
        adjList[v]; // Initialize empty adjacency map for vertex
        vertices.push_back(v); // Add vertex to vertices list
        return true;
    }

    bool addEdge(const VertexT& from, const VertexT& to, const WeightT& cost, const WeightT& time) {
        addVertex(from);
        addVertex(to);
    
        Edge edgeData = {cost, time};
        adjList[from][to] = edgeData;
        adjList[to][from] = edgeData; // For bidirectional edges
        return true;
    }

    bool getWeight(const VertexT& from, const VertexT& to, WeightT& cost, WeightT& time) const {
        auto it = adjList.find(from);
        if (it != adjList.end() && it->second.find(to) != it->second.end()) {
            const Edge& edgeData = it->second.at(to);
            cost = edgeData.cost;
            time = edgeData.time;
            return true;
        }
        return false;
    }

    set<VertexT> neighbors(const VertexT& v) const {
        set<VertexT> S;
        auto it = adjList.find(v);
        if (it != adjList.end()) {
            for (const auto& pair : it->second) {
                S.insert(pair.first);
            }
        }
        return S;
    }

    vector<VertexT> getVertices() const {
        return vertices;
    }

    void dump(ostream& output) const {
        output << "***************************************************" << endl;
        output << "********************* GRAPH ***********************" << endl;

        output << "**Num vertices: " << this->NumVertices() << endl;
        output << "**Num edges: " << this->NumEdges() << endl;

        output << endl;
        output << "**Vertices:" << endl;
        for (int i = 0; i < this->NumVertices(); ++i) {
            output << " " << i << ". " << this->vertices[i] << endl;
        }
        int curRow = 0;
        output << endl;
        output << "**Edges:" << endl;
        for (auto const &i : adjList) {
            output << " row " << curRow << ": "; curRow++;
            for (auto const &j : adjList) {
                if (adjList.at(i.first).count(j.first) == 0) {
                    output << "F ";
                } else {
                    output << "(T," << adjList.at(i.first).at(j.first)
                        << ") ";
                }
            }
            output << endl;
        }
        output << "**************************************************" << endl;
    }

    // New method to retrieve the path from source to destination
    vector<VertexT> getPath(const vector<int>& prev, int destination) const {
        vector<VertexT> path;
        while (destination != -1) {
            path.push_back(destination);
            destination = prev[destination];
        }
        reverse(path.begin(), path.end());
        return path;
    }
};
