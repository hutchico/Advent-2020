#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::vector;
using std::endl;
using std::string;

using namespace std;

int get_neighbors(vector<vector<string>> cube, int x, int y, int z){
    int neighbors = 0;
    //cout << y << z << x << endl;
    for(int i = y - 1; i < y + 2; i++){
        for(int j = z - 1; j < z + 2; j++){
            for(int k = x - 1; k < x + 2; k++){
                //cout << i << j << k << endl;
                if(i < 0 || j < 0 || k < 0 || i > cube.size() - 1 || j > cube[i].size() - 1 || z > cube[i][j].size() - 1) //out of bounds checking
                    continue;
                if(i == y && j == z && k == x) //don't count the cell itself
                    continue;
                else if(cube[i][j][k] == '#')
                    neighbors++;
            }
        }
    }
    //cout << neighbors << endl;
    return neighbors;
};

void iterate_cycle(vector<vector<string>> &cube){
    vector<vector<string>> blank = cube; //copy the cube and edit that copy while maintaining the state of the original
    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            for(int k = 0; k < cube[i][j].size(); k++){
                int neighbors = get_neighbors(cube,k,i,j);
                if(cube[i][j][k] == '#'){ //cell is ON
                    if(neighbors < 2 || neighbors > 3){
                        blank[i][j][k] = '.';
                    }
                }
                else{                     //cell is OFF
                    if(neighbors == 3){
                        blank[i][j][k] = '#';
                    }
                }
            }
        }
    }
    cube = blank;    //replace cube with our iterated copy
};

void print_box(vector<vector<string>> cube){   //DEBUG: Verify cube state
    for(int y = 0; y < cube.size(); y++){       //Ignoring X here because strings are a unified object
        for(int z = 0; z < cube[0].size(); z++){
            cout << cube[y][z] << endl;
        }
        cout << endl;
    }
}

void grow_box(vector<vector<string>> &cube){
    int newX = cube[0].size() + 2; //The central layer is a square and we're just adding a blank layer on top/bottom
    string blank = ".";
    vector<string> newlayer;
    for(int i = 1; i < newX; i++)
        blank.push_back('.');

    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            cube[i][j].push_back('.');
            cube[i][j].insert(0,".");
        }
        cube[i].insert(cube[i].begin(),blank);
        cube[i].push_back(blank);
    }
    for(int i = 0; i < newX; i++)
        newlayer.push_back(blank);

    cube.insert(cube.begin(),newlayer);
    cube.push_back(newlayer);
}

int count_active_cubes(vector<vector<string>> cube){
    int num = 0;
    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            for(int k = 0; k < cube[i][j].size(); k++){
                if(cube[i][j][k] == '#')
                    num++;
            }
        }
    }
    return num;
}

int main()
{
    std::ifstream file;
    string buffer;
    vector<vector<string>> conway; //
    vector<string> cubeLayer;


    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        cubeLayer.push_back(buffer);
    }
    conway.push_back(cubeLayer);


    //first layer assembled, time to simulate
    //this isn't a cube! it's more of a box, the sides will not necessarily be the same length.
    //Reminder of coordinate system:
    /*
        Conway[y][z][x]:
        Y travels down the box (into/out of screen). Array 0 refers to the middle layer of the box.
        Z refers to which string in vector (ie up/down verticality). Array 0 refers to top edge of layer
        X traverses individual strings (left to right horizontal). Array 0 refers to the leftmost character of string.

        Life rules:
        ACTIVE: 2-3 neighbors, no change. If 1 or 4+, OFF
        INACTIVE: 1-2 or 4+, no change. 3 neighbors, transition to ON.

        iteration flow:
        read box state -> grow box size -> iterate box contents
    */

    print_box(conway);
    grow_box(conway);
    cout << "active cubes: " << count_active_cubes(conway) << endl;
    for(int i = 0; i < 6; i++){
        iterate_cycle(conway);
        grow_box(conway);
        //print_box(conway);
        cout << "active cubes in cycle " << i + 1 << ": " << count_active_cubes(conway) << endl;
    }
    return 0;
}
