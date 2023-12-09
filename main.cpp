#include <vector>
#include "my_optimization.h"

int main() {

    std::vector<std::vector<Path>> path;
    std::vector<Point> points;
    std::vector<Point> op_path_line;
    std::vector<Point> op_path_angle;
    init_json(path);    
    my_function(path, points);                          // ?????
    optimize_line_again(points,op_path_line);           // ???line?? (??)
    optimize_again(op_path_line,op_path_angle);         // ???????????
    return 0;
}

