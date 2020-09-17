
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

using namespace std;

vector<string> cols = {
    "time_local nginx_log",
    "hostname",
    "pid",
    "msec",
    "remote_addr",
    "remote_port",
    "document_uri",
    "status",
    "bytes_sent",
    "request_length",
    "ssl_protocol",
    "ssl_session_reused",
    "C_IDC",
    "tcpinfo_rtt",
    "host",
    "server_addr",
    "server_port",
    "upstream_http_name",
    "upstream_addr",
    "upstream_http_port",
    "upstream_connect_time",
    "upstream_header_time",
    "upstream_response_time",
    "request_time",
    "connections_active",
    "connections_reading",
    "connection_requests",
    "connections_writing",
    "server_name",
    "http_user_agent",
    "anti_reason",
    "anti_action",
    "request_id",
    "request_method",
    "http_referer",
    "scheme",
    "uri",
    "instance_id",
    "host@instance_id",
    "server_protocol",
    "sent_http_content_range",
    "content_type",
    "content_length",
    "body_bytes_sent",
    "upstream_bytes_received",
    "upstream_status",
    "request_uri",
    "anti_remote_addr",
    "anti_status",
    "anti_payload",
    "user_pin",
    "upstream_cache_status",
    "anti_typ",
    "upstream_err",
    "anti_req_raw",
    "anti_resp_raw",
    "anti_risk_fid",
    "anti_risk_raw"
};


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

//strs.push_back(s.substr(pos, s.size() - pos));
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
		"anti_typ"              //8 // ""
	};

	vector<int> usedColsIdx;
	for (size_t i = 0; i < usedCols.size(); i++)
	{
		bool found = false;
		for (size_t j = 0; i < cols.size(); j++)
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
			cout << "Error: not find index!" << endl;
			return -1;
		}
	}

    string s = "17/Sep/2020:18:46:13 +0800 nginx_log#?#  :hb1-waf-jfe-01#?#  :95601#?#  :1600339573.897#?#  :124.228.143.217#?#  :20930#?#  :/customer/getMyPing#?#  :200#?#  :770#?#  :1005#?#  :TLSv1.2#?#  :0#?#  :LF-1-PUB-NX#?#  :46684#?#  :lzdz-isv.isvjcloud.com#?#  :116.198.3.129#?#  :443#?#  :-#?#  :114.67.237.193:80#?#  :-#?#  :0.000#?#  :0.081#?#  :0.081#?#  :0.083#?#  :4699#?#  :4#?#  :28#?#  :1254#?#  :lzdz-isv.isvjcloud.com#?#  :Mozilla/4.0 (compatible; MSIE 9.0; Windows NT 6.1; 125LA; .NET CLR 2.0.50727; .NET CLR 3.0.04506.648; .NET CLR 3.5.21022)#?#  :-#?#  :-#?#  :711a8cc95f34603b8783026320e3344a#?#  :POST#?#  :https://lzdz-isv.isvjcloud.com/customer/getMyPing#?#  :https#?#  :/customer/getMyPing#?#  :waf-ins_cn-north-1_1782fe8ad23d#?#  :lzdz-isv.isvjcloud.com@waf-ins_cn-north-1_1782fe8ad23d#?#  :HTTP/1.1#?#  :-#?#  :application/x-www-form-urlencoded; Charset=UTF-8#?#  :-#?#  :171#?#  :751#?#  :200#?#  :/customer/getMyPing#?#  :10.160.159.122#?#  :200#?#  :-#?#  :ecop-070#?#  :-#?#  :#?#  :FT_STATUS#?#  :#?#  :#?#  :Hengyang#?#  :#?#  :";

	string sep = "#?#  :";
	vector<string> strs;
	stringSplit(s, sep, strs);

	vector<string> hosts;
	vector<string> remote_addrs;
	for (size_t i = 0; i < hostSize; i++)
	{
		// 100 hosts
		stringstream ss;
		ss << "10.226.133." << i;
		hosts.push_back(ss.str());
	}

	stringstream ss1;
	for (size_t j = 0; j < ipSize; j++)
	{
		ss1 << "10.226.1." << j;
		remote_addrs.push_back(ss1.str());
		ss1.str("");
	}

	string instance_id = "123";
	string status = "200";
	string uri = "/";
	string user_agent = "Mozilla/5.0";
	string anti_typ = "";
	string host;
	string remote_addr;
	string localtime;
	string msec;
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
					vector<string> usedColsVals = {"111", "123", "10.226.133.8", "10.226.149.215", "555", "666", "777", "888", "999"};
					remote_addr = remote_addrs[j];
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

					updateUsedCols(usedColsIdx, usedColsVals, strs);
					ss << strs[k] << sep;
				}       
				//cout << ss.str() << endl;
				of << ss.str() << endl;
				ss.str("");
				std::this_thread::sleep_for(std::chrono::milliseconds(10)); 
			}
		}
	}

	of.close();

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
        for_each(strs.begin(), strs.end(), [&](string x) -> void { cout << "[" << x << "]" << endl;} );
        cerr << "Error: size not equal!" << endl;
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
