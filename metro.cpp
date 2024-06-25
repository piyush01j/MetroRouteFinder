#include <bits/stdc++.h>
using namespace std;

class station{
    string name;
    int id;
    string color;
    public:
    station(string name, int id,string colour=""){
        this->name=name;
        this->id=id;
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

void getMetroData(vector<vector<pair<int, double > > > &metroGraph, vector<station> &stations)
{
    ifstream file("./metro_database.csv");
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
        vector<pair<int,double> > temp;
        while (getline(ss, word, ','))
        {
            wordNumber++;
            if(wordNumber==1){
                station temp(word, stations.size());
                stations.push_back(temp);
                continue;
            }
            if(wordNumber==2){
                stations[stations.size()-1].set_color(word);
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

void printStations(vector<station> &stations)
{
    for (int i = 0; i < stations.size(); i++)
    {
        cout << stations[i].get_id() << ". " << stations[i].get_name() << " - " << stations[i].get_color() << endl;
    }
}

void getSourceAndDestination(int &startStation, int &endStation)
{
    cout << "Enter the start station id: ";
    cin >> startStation;
    cout << "Enter the end station id: ";
    cin >> endStation;
}

double shortestPath(vector<vector<pair<int, double> > > &metroGraph, int startStation, int endStation, vector<int> &path)
{
    int n = metroGraph.size();
    vector<double> distance(n, INT_MAX);
    priority_queue<pair<double, int>, vector<pair<double, int> >, greater<pair<double, int> > > pq;
    distance[startStation] = 0;
    pq.push(make_pair(0, startStation));
    vector<int> parent(n, -1);
    for(int i=0;i<n;i++){
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
    int temp=endStation;
    while(temp!=startStation){
        path.push_back(temp);
        temp=parent[temp];
    }
    path.push_back(startStation);
    return distance[endStation];
}

void printPath(vector<int> &path, vector<station> &stations, double distance)
{
    cout<<"\n\nShortest Path: \n\n";
    cout<<"Number of stations: "<<path.size()<<endl;
    cout<<"Distance: "<<distance<<"Km\n";
    cout<<"Path: ";
    for (int i = path.size() - 1; i >= 0; i--)
    {
        cout << stations[path[i]].get_name() << " -> ";
    }
}

int main()
{
    vector<station> stations;
    vector<vector<pair<int, double> > > metroGraph;
    getMetroData(metroGraph, stations);
    printStations(stations);

    int startStation, endStation;
    getSourceAndDestination(startStation, endStation);

    vector<int> path;
    double distance=shortestPath(metroGraph, startStation, endStation, path);
    printPath(path, stations, distance);

    return 0;
}
