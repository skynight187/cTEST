#include "abstractdb.hpp"
#include <fstream>
#include <sstream>
#include <cstring>

namespace nwen {

bool AbstractDbTable::loadCSV(std::string filename) {
    std::ifstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    std::string line;
    while (std::getline(file, line)) {
        if (line.empty()) {
            continue;
        }
        std::stringstream ss(line);
        std::string idStr, title, yearStr, director;

        if (!std::getline(ss, idStr, ',')) return false;
        if (!std::getline(ss, title, ',')) return false;
        if (!std::getline(ss, yearStr, ',')) return false;
        if (!std::getline(ss, director)) return false;

        auto strip_quotes = [](std::string &s) {
            if (s.size() >= 2 && s.front() == '"' && s.back() == '"') {
                s = s.substr(1, s.size() - 2);
            }
        };
        strip_quotes(title);
        strip_quotes(director);

        movie m;
        m.id = std::stoul(idStr);
        std::strncpy(m.title, title.c_str(), sizeof(m.title) - 1);
        m.title[sizeof(m.title) - 1] = '\0';
        m.year = static_cast<unsigned short>(std::stoul(yearStr));
        std::strncpy(m.director, director.c_str(), sizeof(m.director) - 1);
        m.director[sizeof(m.director) - 1] = '\0';

        if (!add(m)) {
            return false;
        }
    }

    return true;
}

bool AbstractDbTable::saveCSV(std::string filename) {
    std::ofstream file(filename);
    if (!file.is_open()) {
        return false;
    }

    for (int i = 0; i < rows(); ++i) {
        movie *m = get(i);
        if (!m) {
            continue;
        }
        file << m->id << ",\"" << m->title << "\"," << m->year << ",\"" << m->director << "\"";
        if (i < rows() - 1) {
            file << "\n";
        }
    }
    return true;
}

}
