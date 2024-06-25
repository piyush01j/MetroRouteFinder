#ifndef METRO_HPP
#define METRO_HPP
#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>
#include <string>
#include <queue>
#include "route.hpp"
// #include "station.hpp" // station.hpp is included in route.hpp
using namespace std;

class Metro{
    vector<vector<pair<int, double > > > metroGraph;
    vector<station> stations;
    string fileAddress;
    public:
    Metro(string fileAddress){
        this->fileAddress=fileAddress;
        LoadGraph();
    }
    vector<station> getStations(){
        return stations;
    }
    void LoadGraph(){
        ifstream file(fileAddress);
        if (!file.is_open()) {
            throw runtime_error("Could not open file metro_database.csv");
        }
        string line;
        while (getline(file, line))
        {
            stringstream ss(line);
            string word;
            int wordNumber = 0;
            int station_to;
            double distance;
            string station_name;
            vector<pair<int,double> > temp;
            while (getline(ss, word, ','))
            {
                wordNumber++;
                if(wordNumber==1){
                    station_name=word;
                    continue;
                }
                if(wordNumber==2){
                    station temp(station_name, stations.size(),word);
                    stations.push_back(temp);
                    continue;
                }
                else if(wordNumber==3 || wordNumber==4){
                    continue;
                }
                else if (wordNumber%2==1)
                {
                    station_to = atoi(word.c_str());
                }
                else
                {
                    distance = atof(word.c_str());
                    temp.push_back(make_pair(station_to-1, distance));// did -1 to make the station id 0 based
                }
            }
            metroGraph.push_back(temp);
        }
        file.close();
    }

    void printStations(){
        for (int i = 0; i < stations.size(); i++)
        {
            cout << stations[i].get_id() << ". " << stations[i].get_name() << " - " << stations[i].get_color() << endl;
        }
    } 
    Route shortestPath(int startStation, int endStation)
    {
        int n = metroGraph.size();
        vector<double> distance(n+1, INT_MAX);
        distance[startStation] = 0;
        priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
        pq.push(make_pair(0, startStation));
        vector<int> parent(n+1, -1);
        for(int i=0;i<n+1;i++){
            parent[i]=i;
        }
        while (!pq.empty())
        {
            int u = pq.top().second;
            pq.pop();
            for(auto i: metroGraph[u]){
                int v = i.first;
                double weight = i.second;
                if (distance[v] > distance[u] + weight)
                {
                    distance[v] = distance[u] + weight;
                    pq.push(make_pair(distance[v], v));
                    parent[v]=u;
                }
            }
        }
        vector<string> path;
        if(distance[endStation]==INT_MAX){
            path.push_back("No path exists");
            return Route(path, INT_MAX);
        }
        int temp=endStation;
        while(temp!=startStation){
            path.push_back(stations[temp].get_name());
            temp=parent[temp];
        }
        path.push_back(stations[startStation].get_name());
        reverse(path.begin(),path.end());
        Route route(path, distance[endStation]);
        return route;
    }
};
#endif