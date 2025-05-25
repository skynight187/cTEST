/**
 * abstractdb.hpp
 * C++ header file that should contain declaration for
 * - struct movie (given)
 * - AbstractDbTable abstract class
 * 
 * You need to modify this file to declare AbstractDbTable abstract class 
 * as specified in the hand-out (Task 1)
 */ 
#ifndef __ABSTRACT_DB_HPP__
#define __ABSTRACT_DB_HPP__
#include <string>

namespace nwen 
{
    struct movie {
        unsigned long id;
        char title[50];
        unsigned short year;
        char director[50];
    };

    class AbstractDbTable {
    public:
        // Pure virtual functions
        virtual int rows() const = 0;
        virtual movie* get(int index) const = 0;
        virtual bool add(movie m) = 0;
        virtual bool update(unsigned long id, movie m) = 0;
        virtual bool remove(unsigned long id) = 0;
        
        // Non-pure virtual functions - declarations only
        virtual bool loadCSV(std::string filename);
        virtual bool saveCSV(std::string filename);
    };
}

#endif /* __ABSTRACT_DB_HPP__ */
