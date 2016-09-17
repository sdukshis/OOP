#include <iostream>
#include <map>
#include <string>
#include <vector>

using Headers = std::map<std::string, std::vector<std::string>>;

struct Request {
  Request(const std::string &method_, const std::string &url_,
          const Headers &headers_, const std::string &body_)
      : method{method_}, url{url_}, headers{headers_}, body{body_} {}
  std::string method;
  std::string url;
  Headers headers;
  std::string body;
};

std::ostream &operator<<(std::ostream &stream, const Request &req) {
  stream << req.method << ' ' << req.url << ' ' << "HTTP/1.1\r\n";
  for (auto &&header : req.headers) {
    stream << header.first << ':';
    for (auto &&value : header.second) {
      stream << value << ';';
    }
    stream << "\r\n";
  }
  stream << "\r\n";
  stream << req.body;
  return stream;
}
class RequestBuilder {
public:
  RequestBuilder &method(const std::string &method) {
    method_ = method;
    return *this;
  }

  RequestBuilder &url(const std::string &url) {
    url_ = url;
    return *this;
  }

  RequestBuilder &add_header(const std::string &name,
                             const std::string &value) {
    std::vector<std::string> values;
    values.emplace_back(value);
    return add_header(name, values);
  }

  RequestBuilder &add_header(const std::string &name,
                             const std::vector<std::string> &values) {
    headers_.emplace(name, values);
    return *this;
  }

  RequestBuilder &body(const std::string &body) {
    body_ = body;
    return *this;
  }

  Request create() { return Request{method_, url_, headers_, body_}; }

private:
  std::string method_;
  std::string url_;
  Headers headers_;
  std::string body_;
};

int main() {
  RequestBuilder builder;

  auto req = builder.method("GET")
                 .url("/some/path/")
                 .add_header("User-Agent", "webbot")
                 .create();
  std::cout << req;
}