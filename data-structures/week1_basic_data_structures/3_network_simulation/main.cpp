#include <iostream>
#include <queue>
#include <vector>

struct Request {
  Request(int arrival_time, int process_time):
    arrival_time(arrival_time),
    process_time(process_time)
  {}

  int arrival_time;
  int process_time;
};

struct Response {
  Response(bool dropped, int start_time):
    dropped(dropped),
    start_time(start_time)
  {}

  bool dropped;
  int start_time;
};

class Buffer {
public:
  Buffer(int size):
    size(size),
    finish_time()
  {}

  Response Process(const Request &request) {
    while ( ! finish_time.empty() && finish_time.front() <= request.arrival_time ) {
      finish_time.pop();
    }

    // Check if data can be pushed
    if (finish_time.size() == size) {
      return {true, -1};
    }

    int last = finish_time.empty() ? request.arrival_time : finish_time.back();
    finish_time.push(last + request.process_time);
    return {false, last};
  }
private:
  int size;
  std::queue <int> finish_time;
};

void ReadRequests(std::vector <Request> &requests) {
  int count;
  std::cin >> count;
  requests.reserve(count);
  for (int i = 0; i < count; ++i) {
    int arrival_time, process_time;
    std::cin >> arrival_time >> process_time;
    requests.push_back( {arrival_time, process_time} );
  }
}

void ProcessRequests(const std::vector <Request> &requests, Buffer &buffer, std::vector <Response> &responses) {
  for (const auto& request : requests) {
    responses.push_back( buffer.Process(request) );
  }
}

void PrintResponses(const std::vector <Response> &responses) {
  for (const auto& response : responses) {
    std::cout << (response.dropped ? -1 : response.start_time) << std::endl;
  }
}

int main() {
  int size;
  std::cin >> size;
  std::vector <Request> requests;
  ReadRequests(requests);

  Buffer buffer(size);
  std::vector <Response> responses;
  ProcessRequests(requests, buffer, responses);

  PrintResponses(responses);
  return 0;
}
