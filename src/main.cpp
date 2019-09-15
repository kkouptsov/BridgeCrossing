
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
        // Load all test descriptions (YAML documents) as a vector
        std::vector<YAML::Node> tests = YAML::LoadAllFromFile(argv[1]);
        for(auto &t : tests) {
            try {
                // dig into a single YAML document to get individual test parameters
                if (t.Type() != YAML::NodeType::Map) {
                    throw BridgeCrossing::Exception::TestFileFormat(argv[1]);
                }
                YAML::Node data = t["test"];
                if (data.Type() != YAML::NodeType::Map) {
                    throw BridgeCrossing::Exception::TestFileFormat(argv[1]);
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
            catch(BridgeCrossing::Exception::TestFailed & e) {
                // If a test failed for some reason, skip it and continue
                // with the rest of the tests.
                std::cerr << "Test " << e.what() << " failed." << std::endl;
            }
        }
    }
    catch(YAML::BadFile &) {
        std::cerr << "Could not open file " << argv[1] << std::endl;
        exit(-1);
    }
    catch(BridgeCrossing::Exception::TestFileFormat & e) {
        std::cerr << "Could not parse file " << e.what() << std::endl;
        exit(-2);
    }
    catch(...) {
        std::cerr << "Unknown error." << std::endl;
        exit(-3);
    }
    exit(0);
}
