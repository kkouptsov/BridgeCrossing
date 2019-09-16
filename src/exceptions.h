#include <stdexcept>

#pragma once

namespace BridgeCrossing {
namespace Exception {

    class TestFileFormat : public std::exception 
    {
    public:
        TestFileFormat(std::string filename) : m_filename{filename} {}
        const char* what() { return m_filename.c_str(); }
    private:
        std::string m_filename;
    };

    class TestFailed : public std::exception 
    {
    public:
        TestFailed(int id) : m_id{ std::to_string(id) } {}
        const char* what() { return m_id.c_str(); }
    private:
        std::string m_id;
    };

    class NodeNotFound : public std::exception 
    {
    public:
        NodeNotFound(std::string &name) : m_name{name} {}
        const char* what() { return m_name.c_str(); }
    private:
        std::string m_name;
    };
}
}
