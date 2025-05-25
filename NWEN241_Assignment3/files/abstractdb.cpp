/**
 * abstractdb.cpp
 * C++ source file that should contain implementation for member functions
 * - loadCSV()
 * - saveCSV()
  
 * You need to modify this file to implement the above-mentioned member functions
 * as specified in the hand-out (Tasks 4 and 5)
 */ 

#include "abstractdb.hpp"
#include <iostream>
#include <fstream>
#include <string>


using std::string;

using std::string;

class AbstractDbTable : public abstractdb {
  public:

  /**
   * @brief loads the data from a file to the dataBase
   * @param filename to load from
   * @return true if successful, false otherwise
   */
  bool loadCSV(string filename) {
    std::ifstream file(filename);
    if (!file) 
      return false;

    std::vector<Movie> movies;
    std::string line;

    while (std::getline(file, line)) {
      std::stringstream stringLine(line);
      string id, title, year, director;
      
      if (!std::getline(ss, idStr, ',') ||
        !std::getline(ss, title, ',') ||
        !std::getline(ss, yearStr, ',') ||
        !std::getline(ss, director) ||
        ss.rdbuf()->in_avail() != 0) { 
        return false;
      }

      std::getline(stringLine, id, ',');
      std::getline(stringLine, title, ',');
      std::getline(stringLine, year, ',');
      std::getline(stringLine, director);  

      movie m;
      m.id = std::stoi(idStr);
      m.title = title;
      m.year = std::stoi(yearStr);
      m.director = director;

      add(m);
    }
    return true;
  }

  /**
   * @brief saves the existing dataBase to a file
   * @param filename to save to
   * @return true if successful, false otherwise
   */
  bool saveCSV(string filename) {
    if(dataBase.isEmpty()) 
      return false;

    std::ofStream file(filename);
    if(!file) 
      return false;
    
    for(movie m : dataBase) {
      file << dataBase.id << "," 
           << dataBase.title << ","
           << dataBase.year << ","
           << dataBase.director << "\n";
    }

    file << endl;
    file.close();
    return true;
  }

}
