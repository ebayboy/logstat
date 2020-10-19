
#include <iostream>
#include <string>
#include <vector>
#include <map>
#include <algorithm>
#include <ctime>
#include <sstream>
#include <cstdio>
#include <sys/time.h>
#include <fstream>
#include <chrono>
#include <thread>
#include <getopt.h>
#include <cstring>

#include <nlohmann/json.hpp>
#include <base64/base64.h>

using json = nlohmann::json;

#define ERR() \
    do { \
        cerr << "Error:" << __func__ << ":" << __LINE__ << endl;   \
    } while(0)

#ifdef DEBUG
#define DD() \
    do { \
        cout << "DEBUG:" << __func__ << ":" << __LINE__ << endl;   \
    } while(0)
#else
#define DD() 
#endif


using namespace std;

static vector<string> cols;
static string tmp;

inline void stringSplit(std::string const s, std::string sep, std::vector<std::string> &strs)
{
    std::string::size_type pos = 0, n;

    while (pos != std::string::npos)
    {
        n = s.find(sep, pos);
        if (n == std::string::npos)
        {
            break;
        }
        strs.push_back(s.substr(pos, n - pos));
        pos = n + sep.size();
    }

    strs.push_back(s.substr(pos, s.size() - pos));
}



void updateUsedCols(vector<int> usedColsIdx, vector<string> vals, vector<string> &strs)
{
    for (size_t i = 0; i < usedColsIdx.size(); i++)
    {
        int idx = usedColsIdx[i];
        strs[idx] = vals[i];
    }
}

string getLocalTime()
{
    //29/May/2020:16:38:19 +0800 nginx_log
    vector<string> mon = {
        "Jan",
        "Feb",
        "Mar",
        "Apr",
        "May",
        "Jun",
        "Jul",
        "Aug",
        "Sep",
        "Oct",
        "Nov",
        "Dec"};
    time_t t;
    tm *lt;
    t = time(NULL);
    lt = localtime(&t);

    stringstream ss;
    string stm;
    int tm_year = lt->tm_year + 1900;
    //int tm_month = lt->tm_mon + 1;

    ss << lt->tm_mday << "/" << mon[lt->tm_mon] << "/" << tm_year << ":" << lt->tm_hour << ":" << lt->tm_min << ":" << lt->tm_sec << " +0800 nginx_log";

    return ss.str();
}

string getCurrentTimeMsec()
{
    struct timeval tv;
    stringstream ss;

    gettimeofday(&tv, NULL);

    ss << tv.tv_sec << "." << tv.tv_usec/1000;

    return ss.str();
}

int testCase(size_t hostSize, size_t ipSize, size_t ipQPS, string logfile)
{
	vector<string> usedCols = {
		"time_local nginx_log", //0 //13/Jul/2020:19:13:19 +0800 nginx_log
		"instance_id",          //1 //123
		"host",                 //2 //10.226.133.8
		"remote_addr",          //3 //10.226.149.215
		"msec",                 //4 //1590741499.339
		"status",               //5 //200 | 400
		"uri",                  //6 //  /
		"http_user_agent",      //7 // Mozilla/5.0
		"anti_typ",             //8 // ""
		"anti_risk_fid",        
		"anti_risk_raw" 
	};

	vector<int> usedColsIdx;
	for (size_t i = 0; i < usedCols.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; j < cols.size(); j++)
		{
			if (usedCols[i].compare(cols[j]) == 0)
			{
				usedColsIdx.push_back(j);
				found = true;
				break;
			}
		}

		if (!found)
		{
			cout << "Error: not find index!" <<  usedCols[i] << endl;
			return -1;
		}
	}

    cout << "usedColsIdx.size():" << usedColsIdx.size() << endl;
    if(usedCols.size() != usedColsIdx.size()) {
        cerr << "size not match: usedCols.size:" << usedCols.size()  << " usedColsIdx.size:" <<  usedColsIdx.size() << endl;
        return -1;
    }

	string sep = "#?#  :";
	vector<string> strs;
	stringSplit(tmp, sep, strs);

	vector<string> hosts;
	vector<string> remote_addrs;
	for (size_t i = 0; i < hostSize; i++)
	{
		// 100 hosts
		stringstream ss;
		ss << "host@" << "10.226.133." << i;
		hosts.push_back(ss.str());
	}

	stringstream ss1;
	for (size_t j = 0; j < ipSize; j++)
	{
		ss1 << "10.226.1." << j;
		remote_addrs.push_back(ss1.str());
		ss1.str("");
	}

	string instance_id = "waf-ins_cn-north-1_3f5abca5a72d";
	string status = "200";
	string uri = "/";
	string user_agent = "Mozilla/5.0";
	string anti_typ = "";
	string host = "risk01.00.com";
	string remote_addr;
	string localtime;
	string msec;
	string anti_risk_fid;

    //  to json -> to base64
    string username = "admin";
    string passwd = "123456";
	string raw_str = "{ \"event\" : { \"username\" : \"" + username +  "\",\"passwd\" : \"" + passwd + "\" } }";
	json raw_json = json::parse(raw_str);
    std::string anti_risk_raw = raw_json.dump();

    char *raw_base64 = new char[BASE64_ENCODE_OUT_SIZE(anti_risk_raw.size())];
    base64_encode((const unsigned char *)anti_risk_raw.c_str(), anti_risk_raw.size(), raw_base64);
    cout << "raw_base64:" << raw_base64 << endl;

	stringstream ss;

	ofstream of(logfile, ios::app);
	if (of.bad()) {
		cout << "Error open:" << logfile << endl;
		return -1;
	}

	for (size_t i = 0; i < hosts.size(); i++)
	{
		host = hosts[i];
		for (size_t j = 0; j < remote_addrs.size(); j++)
		{
			for(size_t n = 0; n < ipQPS; n++) {
				for (size_t k = 0; k < strs.size(); k++) 
				{
					vector<string> usedColsVals = {"111", "123", "10.226.133.8", "10.226.149.215", "555", "666", "777", "888", "999", "anti_risk_fid", "anti_risk_raw" };

					remote_addr = remote_addrs[j];
					anti_risk_fid = "FFIIDD" + remote_addrs[j];
					localtime = getLocalTime();
					msec = getCurrentTimeMsec();

					//set vals
					usedColsVals[0] = localtime;
					usedColsVals[1] = instance_id;
					usedColsVals[2] = host;
					usedColsVals[3] = remote_addr;
					usedColsVals[4] = msec;
					usedColsVals[5] = status;
					usedColsVals[6] = uri;
					usedColsVals[7] = user_agent;
					usedColsVals[8] = anti_typ;
					usedColsVals[9] = anti_risk_fid;
					usedColsVals[10] = raw_base64;

					updateUsedCols(usedColsIdx, usedColsVals, strs);

					ss << strs[k];
                    if (k < strs.size()-1) {
                        ss << sep;
                    }
				}       

				cout << ss.str() << endl;

				of << ss.str() << endl;
				ss.str("");
				std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
			}
		}
	}

	of.close();

	return 0;
}

static int initCols()
{
    //read cols
    ifstream is("./cols");
    if (is.bad()) {
        cerr << "Error:" << __func__ << __LINE__ << endl;
        return -1;
    }

    string line;

    while(getline(is, line)) {
        cols.emplace_back(std::move(line));
    }

#if 0
    for( auto && i:cols) {
        cout << "i:" << i << endl;
    }
#endif

    is.close();

    //read template
    ifstream it("./template");
    if (is.bad()) {
        cerr << "Error:" << __func__ << __LINE__ << endl;
        return -1;
    }

    stringstream sbuf;
    sbuf << it.rdbuf();
    it.close();

    tmp = sbuf.str();
    if (tmp[tmp.size() - 1] == '\n') {
        tmp.erase(tmp.size()-1);
    }
    printf("tmp:[%s]\n", tmp.c_str());

    return 0;
}

static void ParseLog(string fname)
{
    ifstream f(fname);
    if (f.bad()) {
        cerr << "Error: open file error!" << endl;
        return ;
    }

    stringstream sbuf;
    sbuf << f.rdbuf();

	string sep = "#?#  :";
    vector<string> strs;

	stringSplit(sbuf.str(), sep, strs);

    if (cols.size() != strs.size()) {
        cout << sbuf.str() << endl;
        cout << "size(cols):" << cols.size() << endl;
        cout << "size(log):" << strs.size() << endl;
        cerr << "Error: size not equal!" << endl;

        for (size_t i = 0; i <cols.size(); i++)  {
            printf("i:%d [%s]:[%s]\n", i, cols[i].c_str(), i > strs.size() ? nullptr : strs[i].c_str());
        }

        return ; 
    }

        for(size_t i=0; i < cols.size(); i++) {
        cout << cols[i] << ":" << strs[i] << endl;
    }

    f.close();
}

int main(int argc, char **argv)
{
	size_t hostSize = 1;
	size_t ipSize = 2;
	size_t ipQPS = 10;
	string logfile = "/export/servers/jfe/logs/access.log";
    string fname;

    if (initCols() != 0) {
        ERR();
        return -1;
    }

	int ch;
	opterr = 0;
	while((ch = getopt(argc,argv, "h:i:q:l:p:"))!= -1) {
		switch(ch)
		{
          case 'h':
              hostSize = atoi(optarg);
              break;
          case 'i':
              ipSize = atoi(optarg);
              break;
          case 'q':
              ipQPS = atoi(optarg);
              break;
          case 'l':
              logfile = optarg;
              break;
          case 'p':
              fname = optarg;
              ParseLog(fname);
              return 0;
          default:
              cout << "help:\n-h hostSize\n-i ipSize\n-q qps\n-l logfile" << endl;
				return -1;
		}
	}

	cout << "hostSize:" << hostSize << endl;
	cout << "ipSize:" << ipSize << endl;
	cout << "ipQPS:" << ipQPS << endl;
	cout << "logfile:" << logfile << endl;
	cout << "colsSize:" << cols.size() << endl;

	if (hostSize == 0 || ipSize == 0 || ipQPS == 0) {
		cout <<"Error: iput param zero error!" << endl;
		return -1;
	}

	if (testCase(hostSize, ipSize, ipQPS, logfile) == -1) {
		cerr << "Error!" << endl;
		return -1;
	}

	return 0;
}
