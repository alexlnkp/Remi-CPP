#ifndef IO_H
#define IO_H

inline bool file_exists(const std::string& name) {
    std::ifstream f(name.c_str());
    return f.good();
}

#endif