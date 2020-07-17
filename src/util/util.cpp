
#include <iostream>
#include <fstream>
#include <string>

#include <unistd.h>

#include "util.h"

using namespace std;

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

