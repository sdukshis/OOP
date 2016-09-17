#include <iostream>
#include <map>
#include <memory>
#include <string>
#include <vector>

using Headers = std::map<std::string, std::vector<std::string>>;

struct Request {
  std::string method;
  std::string url;
  Headers headers;
  std::string body;
  std::string path;
};

struct Response {
  size_t response_code;
  Headers headers;
  std::string body;
};

class RequestHandler {
public:
  virtual ~RequestHandler() {}

  virtual void handle(const Request &, Response &) = 0;
};

class RequestHandlerFactory {
public:
  virtual ~RequestHandlerFactory() {}

  virtual std::unique_ptr<RequestHandler> createRequestHandler() = 0;
};

class NotFoundRequestHandler : public RequestHandler {
public:
  void handle(const Request &, Response &res) override {
    res.response_code = 404;
  }
};

class NotFoundRequestHandlerFactory : public RequestHandlerFactory {
public:
  std::unique_ptr<RequestHandler> createRequestHandler() override {
    return std::make_unique<NotFoundRequestHandler>();
  }
};

class IAmATeaPotRequestHandler : public RequestHandler {
public:
  void handle(const Request &, Response &res) override {
    res.response_code = 418;
  }
};

class IAmATeaPotRequestHandlerFactory : public RequestHandlerFactory {
public:
  std::unique_ptr<RequestHandler> createRequestHandler() override {
    return std::make_unique<IAmATeaPotRequestHandler>();
  }
};

class RequestRouter {
public:
  bool
  addRoute(const std::string &path,
           std::unique_ptr<RequestHandlerFactory> request_handler_factory) {
    auto emplace_res = routes.emplace(path, std::move(request_handler_factory));
    return emplace_res.second;
  }

  bool dropRoute(const std::string &path) { return routes.erase(path); }

  bool handleRequest(const Request &req, Response &res) {
    auto iter = routes.find(req.path);
    if (iter == routes.end()) {
      return false;
    }
    auto request_handler = iter->second->createRequestHandler();
    request_handler->handle(req, res);
    return true;
  }

private:
  using RoutingTable =
      std::map<std::string, std::unique_ptr<RequestHandlerFactory>>;

  RoutingTable routes;
};

int main() {
  RequestRouter router;
  router.addRoute("/unknown/page/",
                  std::make_unique<NotFoundRequestHandlerFactory>());
  router.addRoute("/make/coffee/",
                  std::make_unique<IAmATeaPotRequestHandlerFactory>());

  {
    Request req;
    req.path = "/unknown/page/";
    Response res;
    router.handleRequest(req, res);
    std::cout << "Response code: " << res.response_code << '\n';
  }

  {
    Request req;
    req.path = "/make/coffee/";
    Response res;
    router.handleRequest(req, res);
    std::cout << "Response code: " << res.response_code << '\n';
  }
}