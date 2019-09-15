
#include <iostream>
#include <fstream>
#include <cstring>
#include <vector>
#include "exceptions.h"
#include "test.h"
#include "yaml-cpp/yaml.h"

int main(int argc, char *argv[])
{
    int err;
    if (argc != 2) {
        std::cout << "Usage: " << argv[0] << " <filename>" << std::endl;
        exit(0);
    }
    try {
        // Load all tests as a vector
        std::vector<YAML::Node> tests = YAML::LoadAllFromFile(argv[1]);
        for(auto &t : tests) {
            // dig down to get individual test parameters
            if (t.Type() != YAML::NodeType::Map) {
                throw BridgeCrossing::Exception::TestFileFormat();
            }
            YAML::Node data = t["test"];
            if (data.Type() != YAML::NodeType::Map) {
                throw BridgeCrossing::Exception::TestFileFormat();
            }

            // test parameters
            int test_id = data["test_id"].as<int>();
            int count = data["hikers"].as<int>();
            std::vector<double> walk_time = data["walk_time"].as<std::vector<double>>();

            // expected result
            double crossing_time = data["crossing_time"].as<double>();

            // run the test
            run_test(test_id, count, walk_time, crossing_time);
        }
    }
    catch(YAML::BadFile) {
        std::cerr << "Could not open file " << argv[1] << std::endl;
        exit(-1);
    }
    catch(...) {
        std::cerr << "Could not parse file " << argv[1] << std::endl;
        exit(-2);
    }
    exit(0);
}
