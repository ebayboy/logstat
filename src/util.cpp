
#include <iostream>
#include <nlohmann/json.hpp>
#include <fstream>
#include <string>
#include <unistd.h>

#include "util.h"

using json = nlohmann::json;
using namespace std;

int readCfg(std::string filename)
{
    try
    {
        std::ifstream fs(filename);
        if (!fs.is_open()) {
            cerr << "Error: open file failed!" << endl;
            return -1;
        }
        json j;
        fs >> j;
        std::string s = j.dump();
        cout << s << endl;
    }
    catch (std::exception & e)
    {
        cout << "Error: open file!" << e.what() << endl;
    }

    return 0;
}

void readargs(int argc, char * const argv[], string &c, string &d)
{
    int ch;
    while ((ch = getopt(argc, argv, "c:d:v:h")) != -1) {
        switch (ch) {
            case 'c': 
                c = string(optarg); 
                break;
            case 'v': 
                cout << "Version: 1.0.0" << endl;
                break;
            case 'h': 
                cout << "Usage: \n\t-c config file\n\t-v version\n" << endl;
                break;
			case 'd':
				d = string(optarg);
				break;
        }
    }
}

