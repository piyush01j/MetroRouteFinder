#ifndef STATION_HPP
#define STATION_HPP
#include <string>
using namespace std;
class station{
    string name;
    int id;
    string color;
    public:
    station(string name, int id,string colour){
        this->name=name;
        this->id=id;
        this->color=colour;
    }
    string get_name(){
        return name;
    }
    int get_id(){
        return id;
    }
    string get_color(){
        return color;
    }
    void set_color(string color){
        this->color=color;
    }
    void set_name(string name){
        this->name=name;
    }
    void set_id(int id){
        this->id=id;
    }
};
#endif