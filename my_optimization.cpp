#include <iostream>
#include <json/value.h>
#include <vector>
#include <json/reader.h>
#include <nlohmann/json.hpp>
#include <iomanip>
#include <fstream>
#include <nlohmann/json.hpp>
#include "my_optimization.h"


using namespace std;

void print_fun(std::vector<Point> &path){
    cout<<"print- path.size() = "<< path.size()<<endl;
    for(int i = 0; i < path.size(); i++){
        cout<<"path["<< i <<"] = [" <<path[i].x<< ","<< path[i].y<<"]"<<endl;
    }
    cout<<"end..."<<endl;
}


void optimize_line_again(std::vector<Point> &points, std::vector<Point> &op_path){

    double line_err_min = 0.3;                  // 直线允许误差
    double line_err_max = 2 - line_err_min;     // 直线允许误差
    op_path.push_back(points[0]);               // 添加起点
    
    for (int i = 1; i < points.size() - 1; i++) {       
        if(points[i].x - points[i-1].x <= line_err_min && points[i].y - points[i-1].y >= line_err_max){
            continue;
        }
        
        if(points[i].y - points[i-1].y <= line_err_min && points[i].x - points[i-1].x >= line_err_max){
            continue;
        }
        op_path.push_back(points[i]);
    }
    op_path.push_back(points.back());           // 添加终点
    cout << "再优化line数据后: "<< op_path.size() << "组 "<<endl;
}

void optimize_again(std::vector<Point> &points, std::vector<Point> &op_path){

    double slope_err = 0.0005;           // 斜率误差
    op_path.push_back(points[0]);        // 添加起点
    
    for (int i = 1; i < points.size() - 1; i++) {
        double slope1 = (points[i].y - points[i-1].y) / (points[i].x - points[i-1].x);
        double slope2 = (points[i+1].y - points[i].y) / (points[i+1].x - points[i].x);
        
        if(points[i].x - points[i-1].x == 0 || points[i].y - points[i-1].y == 0){
            continue;
        }

        // 如果斜率在误差允许的范围外，将当前点添加到简化路径中
        if (abs(slope1 - slope2) >= slope_err) {
            op_path.push_back(points[i]);
        }
    }
    op_path.push_back(points.back());   // 添加终点
    cout << "再优化斜率数据后: "<< op_path.size() << "组 "<<endl;
}



void init_json(std::vector<std::vector<Path>> &paths){
    // 解析JSON
    try {
        // JSON字符串
        std::string filePath = "/home/zsy/code/path_optimization/task_path_xie.json";  // JSON文件路径
        // 打开JSON文件
        std::ifstream file(filePath);
        if (file.is_open()) {
            // 读取文件内容到 JSON 对象
            std::string jsonDataString((std::istreambuf_iterator<char>(file)), std::istreambuf_iterator<char>());


            auto json_obj = nlohmann::json::parse(jsonDataString);
            auto plan_path = json_obj["PathListVector"][0]["planPath"];

        // 遍历planPath数组, 存放解析后的数据
        for (const auto& planPath : plan_path) {
            std::vector<Path> vec_path;
            // 遍历每个路径点
            for (const auto& point : planPath) {
                Path p;
                p.x = point["x"];
                p.y = point["y"];
                vec_path.push_back(p);
            }
            paths.push_back(vec_path);
        }

        // 打印结果
        // for (const auto& path : paths) {
        //     for (const auto& point : path) {
        //         std::cout << "x: " << point.x << ", y: " << point.y << std::endl;
        //     }
        // }

            file.close();
        } else {
            std::cout << "无法打开文件" << std::endl;
        }
    } catch (const std::exception& e) {
        std::cerr << "Failed to parse JSON: " << e.what() << std::endl;
    }
}


void my_function(std::vector<std::vector<Path>> &paths, std::vector<Point> &points){

    for(auto path : paths){

        double temp_x = -1.00;
        double temp_y = -1.00;
        size_t path_length = path.size();
        points.reserve(path_length);    
        temp_x = path.at(0).x;
        temp_y = path.at(0).y;

        Point point{};
        point.x = temp_x;
        point.y = temp_y; 
        points.push_back(point);    // 保存第一组数据, 作为哨兵
        size_t i = 1;
        for(i = 1 ;i < path_length - 1; i++){
            while(i < path_length && path[i].x == temp_x){    
            // 如果下一帧的x与上一帧的x相同，则x不变，刷新y
            if(path[i].x == path[i + 1].x){
                 i++;
                continue;
            }else if(path[i].x != path[i + 1].x){
                temp_y = path[i].y;
                point.x = temp_x;
                point.y = temp_y; 
                points.push_back(point);    // 保存x相同，y不同的最后一组数据
                i++;
            }
        }

        while(i < path_length  &&  path[i].y == temp_y){    
            // 如果下一帧的y与上一帧的y相同，则y不变，刷新x
            if(path[i].y == path[i + 1].y){
                 i++;
                continue;
            }else if(path[i].y != path[i + 1].y){
                temp_x = path[i].x;
                point.x = temp_x;
                point.y = temp_y; 
                points.push_back(point);    // 保存x相同，y不同的最后一组数据
                i++;
            }
        }
        

        while(i < path_length  && path[i].x != temp_x && path[i].y != temp_y){    
            temp_x = path[i].x;
            temp_y = path[i].y;
            point.x = temp_x;
            point.y = temp_y; 
            points.push_back(point);        // 保存x，y不同的每一组数据
            i++;
        }
        }
        cout << "初始数据: "<< path.size() << "组 "<<endl;
        cout << "优化后 : "<< points.size() << "组 "<<endl;
       
    }   
}

int main() {

    std::vector<std::vector<Path>> path;
    std::vector<Point> points;
    std::vector<Point> op_path_line;
    std::vector<Point> op_path_angle;
    init_json(path);    
    my_function(path, points);                          // 优化路径点
    optimize_line_again(points,op_path_line);           // 再优化line数据 (去噪)
    optimize_again(op_path_line,op_path_angle);         // 处理斜线，只保留起始点
    return 0;
}

