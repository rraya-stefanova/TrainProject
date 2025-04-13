#pragma once
#include <string>
#include <fstream>
#include <vector>
#include <unordered_map>


class MapReader {

    std::string cityName;   
    std::unordered_map<std::string,std::unordered_map<std::string,int>> cityGraph;

    
public:

    MapReader(std::string cityName) {
        this -> cityName = cityName;
    }
    
    std::unordered_map<std::string,std::unordered_map<std::string,int>> createMap(int& n, int& m, int& maxTime){
            
        try{
            std::ifstream inputFile;
            inputFile.open("cityRoutes/" + cityName + ".txt");
            if(!inputFile.is_open()){
                throw std::ios_base::failure("Failed to open file.");
            }
    
            
            // extract fullTime in this city (the last line from given file)
            
            inputFile.seekg(-1, std::ios::end);
            int pos = inputFile.tellg();
    
            char ch;
            while(pos > 0){
                inputFile.seekg(pos--);
                inputFile.get(ch);
    
                if(ch == '\n'){
                    break;
                }
            }
        
            inputFile >> maxTime;
            inputFile.seekg(0, std::ios::beg);
        
    
            // extract k and r from the first line of the file
            
            inputFile >> n >> m;
            cityGraph.reserve(n);
    
            // read destinations and times
            std::string dest1, dest2;
            int time;
            while(  inputFile >> dest1 >> dest2 >> time ){
                //std::cout << dest1 << " " << dest2 << " " << time << std::endl;
                if(cityGraph.find(dest1) != cityGraph.end()){
                    cityGraph[dest1].insert({dest2,time});
                }
                else{
                    cityGraph.insert({dest1,{}});
                    cityGraph[dest1].insert({dest2,time});
                }

                if(cityGraph.find(dest2) != cityGraph.end()){
                    cityGraph[dest2].insert({dest1,time});
                }
                else{
                    cityGraph.insert({dest2,{}});
                    cityGraph[dest2].insert({dest1,time});
                }

            }
            inputFile.close();
            return cityGraph;
    
        } 
        catch (std::exception e){
            throw std::ios_base::failure("Failed to open file.");
            //std::cerr << "Failed to open file." << std::endl;
        }
        
    }   
};