#include <cmath>
#include <iostream>
#include <fstream>
#include <sstream>

#include "lib/httplib.h"
#include "lib/ini.h"
#include "lib/json.hpp"

//TODO: Вынести в ini файл

std::string readFileIntoString(const std::string& path) {
    std::ifstream input_file(path);
    if (!input_file.is_open()) {
        std::cerr << "Could not open the file - '"
                  << path << "'" << std::endl;
        exit(EXIT_FAILURE);
    }
    return std::string((std::istreambuf_iterator<char>(input_file)), std::istreambuf_iterator<char>());
}

void startPage(const httplib::Request& req, httplib::Response& res) {
    std::string index = readFileIntoString("html/index-min.html");
    res.set_content(index, "text/html");
}

void loadJs(const httplib::Request& req, httplib::Response& res) {
    std::string javascript = readFileIntoString("html/index-min.js");
    res.set_content(javascript, "application/javascript");
}

nlohmann::json loadJson(std::string city) {
    httplib::Client cli("api.openweathermap.org");
    auto json = cli.Get("/data/2.5/weather?q=" + city + "&appid=" + "your-apikey");
    return nlohmann::json::parse(json->body);
}

void getJsonData(const httplib::Request& req, httplib::Response& res) {

    nlohmann::json data = loadJson(req.get_param_value("city"));
    std::string imgdata = data["weather"][0]["icon"];
    std::string descriptiondata = data["weather"][0]["description"];
    double tempdata = data["main"]["temp"];
    tempdata -= 273.15;
    std::string citydata = data["name"];
    nlohmann::json answer = {
        {"imgdata", imgdata},
        {"descriptiondata", descriptiondata},
        {"tempdata", int(tempdata)},
        {"citydata", citydata}
    };
    res.set_content(answer.dump(), "application/json");
}

int main(){
    httplib::Server svr;
    // Обработка главной страницы
    svr.Get("/", startPage);
    svr.Get("/index.html", [](const httplib::Request &, httplib::Response &res) {
        res.set_redirect("/");
    });
    svr.Get("/index.js", loadJs);
    svr.Get("/getjsondata", getJsonData);
    std::cout << "Start server... OK\n";
    svr.listen("localhost", 3000);
}
