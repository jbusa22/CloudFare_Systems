/*  Identifier = 15C1680EE94C640EC35E1694295A3625C3254CBA

    EECS 281 Lab 4: Connected Components

    For this lab, you will write a program that calculates the
    number of connected components in an undirected graph.

    Your program will receive an input file in the following format:
    1) The first line of input contains the number of vertices V and number of edges E in the graph.
    2) The next E lines list out the connections between vertices in the graph in the format of "u v",
    which indicates the existence of an edge between u and v.

    For example, the following input file would be read as follows:
    4 2  (the graph has 4 vertices (numbered from 0-3), and two edges exist in the graph)
    0 1  (the first of these edges connects vertex 0 with vertex 1)
    0 2  (the second of these edges connects vertex 0 with vertex 2)

    In this case, vertices {0, 1, 2} form a connected component, and vertex {3} forms a connected component
    (since 3 is not connected to anything). Thus, your program should print out 2.

    You will be using union-find to complete this lab. The following starter code has been provided. Feel
    free to modify this code in your implementation. Good luck!
*/

#include <iostream>
#include <algorithm>
#include <ctype.h>
#include <cstring>
#include <stdlib.h>
#include <getopt.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netdb.h>
#include <netinet/in.h>
#include <unistd.h>
#include <sstream>
#include <fstream>
#include <vector>
#include <bits/stdc++.h> 
#include <string>
#include <chrono>
typedef std::chrono::high_resolution_clock Clock;
using namespace std;

int sock;
struct sockaddr_in client;
int PORT = 80;
//https://jsonplaceholder.typicode.com/todos/1
string getHost(string url) {
  size_t found = url.find_first_of(":");
  string protocol=url.substr(0,found); 

  string url_new=url.substr(found+3);
  size_t found2 =url_new.find_first_of("/");
  string host =url_new.substr(0,found2);
  return host;
}
string getPath(string url) {
  size_t found = url.find_first_of(":");
  string protocol=url.substr(0,found); 

  string url_new=url.substr(found+3);
  size_t found1 = url_new.find_first_of("/");
  if (found1 != string::npos) {
    return url_new.substr(found1);
  }
  return "/";
}
void printResponse(string link, char* cHost, bool profile) {
  string path = getPath(link);
  struct hostent * host = gethostbyname(cHost);

  if ( (host == NULL) || (host->h_addr == NULL) ) {
      cout << "Error retrieving DNS information. Make sure the url is in the form http://" << endl;
      exit(1);
  }

  bzero(&client, sizeof(client));
  client.sin_family = AF_INET;
  client.sin_port = htons( PORT );
  memcpy(&client.sin_addr, host->h_addr, host->h_length);

  sock = socket(AF_INET, SOCK_STREAM, 0);

  if (sock < 0) {
      cout << "Error creating socket." << endl;
      exit(1);
  }

  if ( connect(sock, (struct sockaddr *)&client, sizeof(client)) < 0 ) {
      close(sock);
      cout << "Could not connect" << endl;
      exit(1);
  }

  stringstream ss;
  ss << "GET " << path << " HTTP/1.1\r\n"
      << "Host: " << string(cHost) << "\r\n"
      << "Accept: application/json\r\n"
      << "Connection: close\r\n"
      << "\r\n\r\n";
  string request = ss.str();

  if (send(sock, request.c_str(), request.length(), 0) != (int)request.length()) {
      cout << "Error sending request." << endl;
      exit(1);
  }

  int check = 0;
  char cur;
  while ( read(sock, &cur, 1) > 0 ) {
    if (check == 4 && !profile) {
      cout << cur;
    }
    else if (cur == '\r' || cur == '\n') {
      check++;
    } else {
      check = 0;
    }
  }
}
int main(int argc, char *argv[])
{
  int choice;
  int option_index = 0;
  bool shouldFetch = false;
  string url;
  int numRuns = 1;
  bool shouldProfile = false;
  option long_options[] = 
  {
    { "help", no_argument,                 nullptr, 'h' },
    { "url", required_argument,                 nullptr, 'u' },
    { "profile", required_argument,                 nullptr, 'p' },
    { nullptr, 0,                 nullptr, '\0' }
  };
  
  while ((choice = getopt_long(argc, argv, "hu:p:", 
  long_options, &option_index)) != -1) 
  {
    switch (choice) 
    {
      case 'h':
        cout << "Type --url along with a url in the form http://" << endl;
        exit(1);
      case 'u':
        shouldFetch = true;
        url = string(optarg);
      break;
      case 'p':
        shouldProfile = true;
        numRuns = stoi(string(optarg));
      break;
      default:
        cerr << "Error: invalid option type --help for help";
        exit(1);
    }
  }
 
  if (shouldFetch) {
    string host = getHost(url);
    int errors = 0;
    char cHost[host.size() + 1];
    strcpy(cHost, host.c_str());
    if (shouldProfile) {
      vector<int> times;
      for (size_t i = 0; i < numRuns; i++) {
        auto t1 = Clock::now();
        printResponse(url, cHost, shouldProfile);
        auto t2 = Clock::now();
        int time = std::chrono::duration_cast<std::chrono::nanoseconds>(t2 - t1).count();
        times.push_back(time);
      }
      sort(times.begin(), times.end());
      cout << "Run: " << numRuns << " times\n"
          << "Fastest Run: " << *times.begin() << " nanoseconds\n"
          << "Slowest Run: " << *prev(times.end()) << " nanoseconds\n"
          << "Total Time: " << accumulate(times.begin(), times.end(), 0) << " nanoseconds\n"
          << "Errors: " << errors << "\n";
    } else {
      printResponse(url, cHost, shouldProfile);
    }
  }
  return 0;
}
