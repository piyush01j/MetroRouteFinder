#ifndef ROUTE_HPP
#define ROUTE_HPP
#include <vector>
#include <iostream>
#include <string>
#include "station.hpp"
using namespace std;

class Route{
    vector<string> path;
    double distance;
    public:
    Route(vector<string> path, double distance){
        this->path=path;
        this->distance=distance;
    }
    // vector<string> get_path(){
    //     return path;
    // }
    // double get_distance(){
    //     return distance;
    // }
    // void set_path(vector<string> &path){
    //     this->path=path;
    // }
    // void set_distance(double distance){
    //     this->distance=distance;
    // }
    void printRoute(){
        cout<<"Number of stations: "<<path.size()<<endl;
        cout<<"Distance: "<<distance<<endl;
        cout<<"Path: ";
        for(int i=0;i<path.size();i++){
            cout<<path[i]<<" -> ";
        }
    }
};
#endif