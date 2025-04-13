#include <iostream>
#include "SkipList.hpp"
#include "MapReader.hpp"
#include <unordered_set>

void findAllPaths(
    std::string curr, 
    std::string start, 
    std::unordered_map<std::string,std::unordered_map<std::string,int>>& graph,
    std::vector<std::string> currPath, std::vector<std::vector<std::string>>& allPaths,
    std::vector<int>& allTimes,
    int currTime, int maxTime){
    
    currPath.push_back(curr);
    if(curr == start && currPath.size() > 1){
    
        // we have reached the beginning again
        for(std::vector<std::string> v : allPaths){
            if(currPath == v){
                // path is already found
                return;
            }
        }

        // new path is found

        allPaths.push_back(currPath);
        allTimes.push_back(currTime);

        return;
    }

    for(std::pair<std::string,int> nbr : graph[curr]){
        
        if(currTime  + nbr.second <= maxTime){      

            findAllPaths( nbr.first, start, graph, currPath, allPaths, allTimes, currTime + nbr.second, maxTime);
            
        }
        
    }
    return;

}

std::vector<std::string> findBestPath
    (std::unordered_map<std::string,std::unordered_map<std::string,int>>& graph, int maxTime){
    
    std::vector<std::string> currPath;
    std::vector<std::vector<std::string>> allPaths;
    std::vector<int> allTimes;

    int currTime = 0;
    findAllPaths("Railstation", "Railstation", graph, currPath, allPaths, allTimes, currTime, maxTime);

    int maxVisited = 0;
    std::vector<std::string> bestPath;
    int time, i = 0;

    for(std::vector<std::string> path : allPaths){
        std::unordered_set<std::string> visitedDestinations(path.begin(), path.end());
        visitedDestinations.erase("Railstation");
        int visitedSize = visitedDestinations.size();

        if(visitedSize > maxVisited){
            maxVisited = visitedSize;
            bestPath = path;
            time = allTimes[i];
        }
        else if(visitedSize == maxVisited){
            if(allTimes[i] < time){
                bestPath = path;
                time = allTimes[i];
            }
        }
        i ++;

    }
    //std::cout << "time = " << time << std::endl;
    return bestPath;

}
int main(){
    
    
    MapReader* mapReader = new MapReader("Sofia");
    int n, m;
    int maxTimeForVisit;
    std::unordered_map<std::string,std::unordered_map<std::string,int>> cityGraph = mapReader->createMap(n, m, maxTimeForVisit);

    /*
    for(auto i = cityGraph.begin() ; i != cityGraph.end() ; i++){
        std::cout << (i->first) << " : ";
        for(auto j = (i->second).begin() ; j != (i->second).end() ; j++){
            std::cout << (j->first) << " - " << (j->second) << "; ";
        }
        std::cout << std::endl;
    }
    */

    std::vector<std::string> bestPath = findBestPath(cityGraph, maxTimeForVisit);

    for(std::string s : bestPath){
        std::cout << s + " ";
    }
    std::cout << std::endl; 
    return 0;
}