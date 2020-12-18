#include <iostream>
#include <vector>
#include <fstream>
#include <sstream>

using std::cout;
using std::vector;
using std::endl;
using std::string;

using namespace std;

int get_neighbors(vector<vector<vector<string>>> cube, int w, int x, int y, int z){
    int neighbors = 0;
    for(int i = w - 1; i < w + 2; i++){
        for(int j = y - 1; j < y + 2; j++){
            for(int k = z - 1; k < z + 2; k++){
                for(int l = x - 1; l < x + 2; l++){
                    if(i < 0 || j < 0 || k < 0 || l < 0 || i > cube.size() - 1 || j > cube[i].size() - 1 || k > cube[i][j].size() - 1 || l > cube[i][j][k].size() - 1) //out of bounds checking
                        continue;
                    if(i == w && j == y && k == z && l == x) //don't count the cell itself
                        continue;
                    else if(cube[i][j][k][l] == '#'){
                        neighbors++;
                        if(neighbors >= 4)
                            return neighbors;
                    }
                }
            }
        }
    }
    return neighbors;
};

void iterate_cycle(vector<vector<vector<string>>> &cube){
    vector<vector<vector<string>>> blank = cube; //copy the cube and edit that copy while maintaining the state of the original

    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            for(int k = 0; k < cube[i][j].size(); k++){
                for(int l = 0; l < cube[i][j][k].size(); l++){
                    int neighbors = get_neighbors(cube,i,l,j,k);
                    if(cube[i][j][k][l] == '#'){ //cell is ON
                        if(neighbors < 2 || neighbors > 3){
                            blank[i][j][k][l] = '.';
                        }
                    }
                    else{                     //cell is OFF
                        if(neighbors == 3){
                            blank[i][j][k][l] = '#';
                        }
                    }
                }
            }
        }
    }
    cube = blank;    //replace cube with our iterated copy
};

void grow_box(vector<vector<vector<string>>> &cube){
    int newY = cube[0].size() + 2;
    int newZ = cube[0][0].size() + 2;
    string blank = ".";
    vector<string> newlayer;
    vector<vector<string>> newBox;

    for(int i = 1; i < newZ; i++) //Empty line
        blank.push_back('.');
    for(int i = 0; i < newZ; i++) //Empty square
        newlayer.push_back(blank);
    for(int i = 0; i < newY; i++){ //Empty cube
        newBox.push_back(newlayer);
    }
    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            for(int k = 0; k < cube[i][j].size(); k++){
                cube[i][j][k].push_back('.');
                cube[i][j][k].insert(0,".");
            }
            cube[i][j].insert(cube[i][j].begin(),blank);
            cube[i][j].push_back(blank);
        }
        cube[i].insert(cube[i].begin(),newlayer);
        cube[i].push_back(newlayer);
    }
    cube.insert(cube.begin(),newBox);
    cube.push_back(newBox);

}

int count_active_cubes(vector<vector<vector<string>>> cube){
    int num = 0;

    for(int i = 0; i < cube.size(); i++){
        for(int j = 0; j < cube[i].size(); j++){
            for(int k = 0; k < cube[i][j].size(); k++){
                for(int l = 0; l < cube[i][j][k].size(); l++){
                    if(cube[i][j][k][l] == '#')
                        num++;
                }
            }
        }
    }
    return num;
}

int main()
{
    std::ifstream file;
    string buffer;
    vector<string> layer;
    vector<vector<string>> box;
    vector<vector<vector<string>>> conway;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        layer.push_back(buffer);
    }
    box.push_back(layer);
    conway.push_back(box);

    //first layer assembled, time to simulate
    //this isn't a cube! it's more of a box, the sides will not necessarily be the same length.
    //Reminder of coordinate system:
    /*
        Conway[w][y][z][x]:
        W just holds the other Y boxes I guess
        Y travels down the box (into/out of screen). Array 0 refers to the middle layer of the box.
        Z refers to which string in vector (ie up/down verticality). Array 0 refers to top edge of layer
        X traverses individual strings (left to right horizontal). Array 0 refers to the leftmost character of string.

        Life rules:
        ACTIVE: 2-3 neighbors, no change. If 1 or 4+, OFF
        INACTIVE: 1-2 or 4+, no change. 3 neighbors, transition to ON.

        iteration flow:
        read box state -> grow box size -> iterate box contents
    */


    grow_box(conway);
    cout << "starting active cubes: " << count_active_cubes(conway) << endl;
    for(int i = 0; i < 6; i++){
        iterate_cycle(conway);
        grow_box(conway);

        cout << "active cubes in cycle " << i + 1 << ": " << count_active_cubes(conway) << endl;
    }
    return 0;
}
