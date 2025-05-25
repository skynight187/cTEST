/**
 * vectordb.hpp
 * C++ header file that contains declaration for VectorDbTable class
 * which extends AbstractDbTable and uses a vector to store movie records.
 */
#ifndef __VECTOR_DB_HPP__
#define __VECTOR_DB_HPP__

#include "abstractdb.hpp"
#include <vector>

namespace nwen 
{
    class VectorDbTable : public AbstractDbTable {
    private:
        // Vector to store movie records - provides dynamic array functionality
        // with automatic memory management and efficient random access
        std::vector<movie> movies;
        
        // Helper function to find movie index by ID
        // Returns -1 if movie with given ID is not found
        // This avoids code duplication in update() and remove() methods
        int findMovieIndexById(unsigned long id) const;
        
    public:
        // Default constructor - initializes empty vector
        // Vector's default constructor will create an empty container
        VectorDbTable();
        
        // Returns the number of movie records in the database
        virtual int rows() const override;
        
        // Returns pointer to movie at given index (0-based)
        // Returns nullptr if index is out of bounds
        // Using const to indicate this method doesn't modify the object
        virtual movie* get(int index) const override;
        
        // Adds a new movie record to the database
        // Returns true if successfully added, false if ID already exists
        // Vector's push_back provides efficient insertion at the end
        virtual bool add(movie m) override;
        
        // Updates existing movie record with given ID
        // Returns true if movie was found and updated, false otherwise
        // Searches by ID rather than index for more intuitive API
        virtual bool update(unsigned long id, movie m) override;
        
        // Removes movie record with given ID
        // Returns true if movie was found and removed, false otherwise
        // Uses vector's erase method for efficient removal
        virtual bool remove(unsigned long id) override;
        
        // Additional utility functions for vector-specific operations
        
        // Clears all movie records from the database
        // Useful for resetting the database or implementing bulk operations
        void clear();
        
        // Returns true if the database is empty
        // Convenience method that leverages vector's empty() function
        bool empty() const;
        
        // Reserves space for specified number of movies
        // Optimization method to prevent multiple reallocations when
        // the expected number of records is known in advance
        void reserve(size_t capacity);
    };
}

#endif /* __VECTOR_DB_HPP__ */
