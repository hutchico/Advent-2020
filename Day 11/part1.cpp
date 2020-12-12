#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define DECAY_CONST 4

int change_room(vector<string> &room, vector<vector<char>> &changes){
    int total = 0;
    int adjacent = 0;
    for(int i = 0; i < room.size(); i++){
        for(int j = 0; j < room[0].size(); j++){
            if(room[i][j] == 'L'){  //Seat is empty
                //Start by catching edge cases
                if(i == room.size() - 1 && j == room[0].size() - 1){   //Bottom right corner case
                    if(room[i-1][j] == '#' || room[i][j-1] == '#' || room[i-1][j-1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == room.size() - 1 && j == 0){   //Bottom left corner case
                    if(room[i-1][j] == '#' || room[i][j+1] == '#' || room[i-1][j+1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == 0 && j == room.size() - 1){   //top right corner case
                    if(room[i+1][j] == '#' || room[i][j-1] == '#' || room[i+1][j-1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == 0 && j == 0){   //top left corner case
                    if(room[i+1][j] == '#' || room[i][j+1] == '#'|| room[i+1][j+1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }

                //Corner cases covered so now we hit the rest of the edges
                else if(i == 0){    //Top edge
                    if(room[i+1][j] == '#' || room[i][j+1] == '#' || room[i][j-1] == '#' || room[i+1][j-1] == '#' || room[i+1][j+1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(j == 0){    //Left edge
                    if(room[i-1][j] == '#' || room[i][j+1] == '#' || room[i+1][j] == '#' || room[i-1][j+1] == '#' || room[i+1][j+1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(j == room[0].size() - 1){   //Right edge
                    if(room[i-1][j] == '#' || room[i+1][j] == '#' || room[i][j-1] == '#' || room[i-1][j-1] == '#' || room[i+1][j-1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == room.size() - 1){   //Bottom edge
                    if(room[i-1][j] == '#' || room[i][j+1] == '#' || room[i][j-1] == '#' || room[i-1][j+1] == '#' || room[i-1][j-1] == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }

                //Now general case for anything not on the edge
                else if(room[i-1][j] == '#' || room[i][j+1] == '#' || room[i][j-1] == '#' || room[i+1][j] == '#' || room[i-1][j-1] == '#' || room[i+1][j+1] == '#' || room[i+1][j-1] == '#' || room[i-1][j+1] == '#')
                    continue;
                else{
                        changes[i][j] = '1';
                        total++;
                    }
            }
            else if(room[i][j] == '#'){ //seat is occupied
                //located on a corner means this seat will never flip back
                if(i == 0 && j == 0)
                    continue;
                else if(i == room.size() - 1 && j == room[0].size() - 1)
                    continue;
                else if(i == 0 && j == room[0].size() - 1)
                    continue;
                else if(i == room.size() - 1  && j == 0)
                    continue;
                else{
                    if(i != 0 && j != 0 && room[i-1][j-1] == '#')
                        adjacent++;
                    if(i != 0 && room[i-1][j] == '#')
                        adjacent++;
                    if(i != 0 && j != room[0].size() - 1 && room[i-1][j+1] == '#')
                        adjacent++;
                    if(j != 0 && room[i][j-1] == '#')
                        adjacent++;
                    if(j != room[0].size() - 1 && room[i][j+1] == '#')
                        adjacent++;
                    if(i != room.size() - 1 && j != 0 && room[i+1][j-1] == '#')
                        adjacent++;
                    if(i != room.size() - 1 && room[i+1][j] == '#')
                        adjacent++;
                    if(i != room.size() - 1 && j != room[0].size() - 1 && room[i+1][j+1] == '#')
                        adjacent++;

                    if(adjacent >= DECAY_CONST){
                        changes[i][j] = '0';
                        total++;
                    }
                    adjacent = 0;
                }
            }
        }
    }

    for(int i = 0; i < changes.size(); i++){
        for(int j = 0; j < changes[0].size(); j++){
            if(changes[i][j] == '1')
                room[i][j] = '#';
            else if(changes[i][j] == '0')
                room[i][j] = 'L';
        }
    }
    return total;
}

int count_seats(vector<string> room){
    int total = 0;
    for(int i = 0; i < room.size(); i++){
        for(int j = 0; j < room[0].size(); j++){
            if(room[i][j] == '#')
                total++;
        }
    }
    return total;
}

void print_room(vector<string> room){
    for(int i = 0; i < room.size(); i++){
        cout << room[i] << endl;
    }
}

int main()
{
    std::ifstream file;
    vector<string> room;
    vector<vector<char>> changes;
    vector<vector<char>> templ;
    vector<char> stage1;
    string user;
    string buffer;
    int changed = 0;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(buffer == "")
            break;
        room.push_back(buffer);
    }
    file.close();
    for(int i = 0; i < room[0].size(); i++){
        stage1.push_back('2');
    }
    for(int i = 0; i < room.size(); i++){
        changes.push_back(stage1);
    }
    templ = changes; //Store this so we can reset the change array between rounds
    while(true){
        changed = change_room(room,changes);
        cout << endl << "Changed tiles: " << changed << endl;

        //print_room(room);
        changes = templ;
        if(changed == 0)
            break;
    }

    cout << count_seats(room) << endl;
    return 0;
}
