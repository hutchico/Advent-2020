#include <iostream>
#include <fstream>
#include <vector>
#include <math.h>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int main()
{
    std::ifstream file;
    string buffer;
    vector<string> commands;
    char direction;
    int mag = 0;
    int num_rotations = 0;    //East -> 0
    int rel_x = 0;
    int rel_y = 0;
    int middle = 0;
    int wayp_x = 10;
    int wayp_y = 1;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        commands.push_back(buffer);
    }
    file.close();

    for(int i = 0; i < commands.size(); i++){
        buffer = commands[i];
        cout << buffer << ": ";
        buffer.erase(0,1);
        mag = stoi(buffer);
        direction = commands[i][0];

        switch(direction){
            case 'N': wayp_y += mag; break;
            case 'S': wayp_y -= mag; break;
            case 'E': wayp_x += mag; break;
            case 'W': wayp_x -= mag; break;
            case 'L':
                num_rotations = mag / 90;
                for(int j = 0; j < num_rotations; j++){
                    middle = wayp_y;
                    wayp_y = wayp_x;
                    wayp_x = -1 * middle;
                }
                break;
            case 'R':
                num_rotations = mag / 90;
                for(int j = 0; j < num_rotations; j++){
                    middle = wayp_x;
                    wayp_x = wayp_y;
                    wayp_y = -1 * middle;
                }
                break;
            default:
                rel_x += mag * wayp_x;
                rel_y += mag * wayp_y;
                break;
        }
        cout << rel_x << " " << rel_y << " " << wayp_x << " " << wayp_y;
        cout << endl;
    }

    cout << abs(rel_x) + abs(rel_y) << endl;
    return 0;
}
