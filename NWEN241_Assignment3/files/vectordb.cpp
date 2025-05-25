/**
 * vectordb.cpp
 * C++ source file that contains implementation of VectorDbTable class
 * member functions inherited from AbstractDbTable.
 */

#include "vectordb.hpp"

namespace nwen 
{
    // Default constructor
    VectorDbTable::VectorDbTable() { }
    
    // Returns the number of rows in the table
    int VectorDbTable::rows() const {
        return static_cast<int>(movies.size());
    }
    
    // Returns a pointer to a movie structure at the specified row number
    movie* VectorDbTable::get(int index) const {
        // Check if index is within valid range
        if (index < 0 || index >= static_cast<int>(movies.size())) {
            return nullptr;  // Return null pointer for invalid index
        }
        
        // Return pointer to the movie at the specified index
        // const_cast is needed because we're returning non-const pointer from const method
        // This is acceptable since the caller will use this for read operations in typical usage
        return const_cast<movie*>(&movies[index]);
    }
    
    // Inserts a record into the table
    bool VectorDbTable::add(movie m) {
        // Check if a movie with the same ID already exists
        for (const auto& existingMovie : movies) {
            if (existingMovie.id == m.id) {
                return false;  // Don't insert if ID already exists
            }
        }
        
        // Insert the new movie record
        movies.push_back(m);
        return true;  // Insertion successful
    }
    
    // Updates a record in the table
    bool VectorDbTable::update(unsigned long id, movie m) {
        int index = findMovieIndexById(id);
        if (index == -1) {
            return false;
        }

        movies[index] = m;
        return true;
    }
    
    // Removes a record from the table
    bool VectorDbTable::remove(unsigned long id) {
        // Find the movie with the specified ID
        int index = findMovieIndexById(id);
        
        if (index == -1) {
            return false;  // Movie with specified ID not found
        }
        
        // Remove the movie record using vector's erase method
        movies.erase(movies.begin() + index);
        
        return true;  // Removal successful
    }
    
    // Helper function to find movie index by ID
    int VectorDbTable::findMovieIndexById(unsigned long id) const {
        for (size_t i = 0; i < movies.size(); ++i) {
            if (movies[i].id == id) {
                return static_cast<int>(i);
            }
        }
        return -1;  // Movie not found
    }

    void VectorDbTable::clear() {
        movies.clear();
    }

    bool VectorDbTable::empty() const {
        return movies.empty();
    }

    void VectorDbTable::reserve(size_t capacity) {
        movies.reserve(capacity);
    }
}
