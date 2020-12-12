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
    int heading = 0;    //East -> 0
    int rel_x = 0;
    int rel_y = 0;

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
        buffer.erase(0,1);
        mag = stoi(buffer);
        direction = commands[i][0];

        switch(direction){
            case 'N': rel_y += mag; break;

            case 'S': rel_y -= mag; break;
            case 'E': rel_x += mag; break;
            case 'W': rel_x -= mag; break;
            case 'L':
                heading += mag;
                if(heading >= 360)
                    heading -= 360;
                break;
            case 'R':
                heading -= mag;
                if(heading < 0)
                    heading += 360;
                break;
            default:
                if(heading == 0)
                    rel_x += mag;
                else if(heading == 90)
                    rel_y += mag;
                else if(heading == 180)
                    rel_x -= mag;
                else    //heading == 270
                    rel_y -= mag;
                break;
        }
    }

    cout << abs(rel_x) + abs(rel_y) << endl;
    return 0;
}
