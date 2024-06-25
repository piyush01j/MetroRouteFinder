#include <iostream>
#include "route.hpp"
#include "station.hpp"
#include "metro.hpp"
using namespace std;
int main()
{
    Metro DelhiMetro("DelhiMetroDatabase.csv");
    DelhiMetro.printStations();

    int startStation, endStation;
    cout << "Enter the start station id: ";
    cin >> startStation;
    cout << "Enter the end station id: ";
    cin >> endStation;

    Route r1 = DelhiMetro.shortestPath(startStation, endStation);
    r1.printRoute();

    return 0;
}
