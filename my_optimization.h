#ifndef MY_OPTIMIZATION_H
#define MY_OPTIMIZATION_H
#include <iostream>

// #include <vector>
// #include <json/reader.h>
// #include <nlohmann/json.hpp>
// #include <iomanip>
// #include <fstream>
// #include <json/value.h>
// #include <nlohmann/json.hpp>


using namespace std;
// namespace optimization{
struct Path{
    double x;
    double y;
};


struct Point {
    double x;
    double y;
    Point(double x1,double y1): x(x1),y(y1){};
    Point() : x(0),y(0) {};
};

void print_fun(vector<Point> &path);

void optimize_line_again(std::vector<Point> &points, std::vector<Point> &op_path);

void optimize_again(std::vector<Point> &points, std::vector<Point> &op_path);

void init_json(std::vector<std::vector<Path>> &paths);

void my_function(std::vector<std::vector<Path>> &paths, std::vector<Point> &points);

// }
#endif 