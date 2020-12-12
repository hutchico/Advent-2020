#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

#define DECAY_CONST 5

char find_seat(int x, int y, vector<string> room, int direction){
    //tried to use a switch case here but c++ apparently doesn't support nesting loop constructs
    //'direction' parameter specifies a numpad durection, where 1 is bottom left, 9 is top right.

    int ymax = room.size();
    int xmax = room[0].size();
    int xref = x;
    int yref = y;

    if(direction == 1){
        while(xref > -1 && yref < ymax){
            if(room[yref][xref] == '#')
                return '#';
            else if(room[yref][xref] == 'L')
                return 'L';
            xref--;
            yref++;
            }
    }
    else if(direction == 2){
            while(yref < ymax){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                yref++;
            }
        }
    else if(direction == 3){
        while(xref < xmax && yref < ymax){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                xref++;
                yref++;
            }
        }
    else if(direction == 4){
        while(xref > -1){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                xref--;
            }
        }
    else if(direction == 6){
        while(xref < xmax){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                xref++;
            }
        }
    else if(direction == 7){
        while(xref > -1 && yref > -1){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                xref--;
                yref--;
            }
        }
    else if(direction == 8){
        while(yref > -1){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                yref--;
            }
        }
    else if(direction == 9){
        while(xref < xmax && yref > -1){
                if(room[yref][xref] == '#')
                    return '#';
                else if(room[yref][xref] == 'L')
                    return 'L';
                xref++;
                yref--;
            }
        }

    return 'L'; //The point of this function is checking for occupied seats; if a seat isn't found, it's effectively empty.
}

int change_room(vector<string> &room, vector<vector<char>> &changes){
    int total = 0;
    int adjacent = 0;
    for(int i = 0; i < room.size(); i++){
        for(int j = 0; j < room[0].size(); j++){
            if(room[i][j] == 'L'){  //Seat is empty
                //Start by catching edge cases
                if(i == room.size() - 1 && j == room[0].size() - 1){   //Bottom right corner case
                    if(find_seat(j,i-1,room,8) == '#' || find_seat(j-1,i-1,room,7) == '#' || find_seat(j-1,i,room,4) == '#')
                        continue;
                    else{
                        changes[i][j] = '1'; //This seat will be flipped to on
                        total++;
                    }
                }
                else if(i == room.size() - 1 && j == 0){   //Bottom left corner case
                    if(find_seat(j,i-1,room,8) == '#' || find_seat(j+1,i-1,room,9) == '#' || find_seat(j+1,i,room,6) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == 0 && j == room.size() - 1){   //top right corner case
                    if(find_seat(j-1,i,room,4) == '#' || find_seat(j-1,i+1,room,1) == '#' || find_seat(j,i+1,room,2) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == 0 && j == 0){   //top left corner case
                    if(find_seat(j,i+1,room,2) == '#' || find_seat(j+1,i+1,room,3) == '#' || find_seat(j+1,i,room,6) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }

                //Corner cases covered so now we hit the rest of the edges
                else if(i == 0){    //Top edge
                    if(find_seat(j-1,i,room,4) == '#' || find_seat(j-1,i+1,room,1) == '#' || find_seat(j,i+1,room,2) == '#' || find_seat(j+1,i+1,room,3) == '#' || find_seat(j+1,i,room,6) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(j == 0){    //Left edge
                    if(find_seat(j,i+1,room,2) == '#' || find_seat(j+1,i+1,room,3) == '#' || find_seat(j+1,i,room,6) == '#' || find_seat(j+1,i-1,room,9) == '#' || find_seat(j,i-1,room,8) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(j == room[0].size() - 1){   //Right edge
                    if(find_seat(j,i-1,room,8) == '#' || find_seat(j-1,i-1,room,7) == '#' || find_seat(j-1,i,room,4) == '#' || find_seat(j-1,i+1,room,1) == '#' || find_seat(j,i+1,room,2) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }
                else if(i == room.size() - 1){   //Bottom edge
                    if(find_seat(j+1,i,room,6) == '#' || find_seat(j+1,i-1,room,9) == '#' || find_seat(j,i-1,room,8) == '#' || find_seat(j-1,i-1,room,7) == '#' || find_seat(j-1,i,room,4) == '#')
                        continue;
                    else{
                        changes[i][j] = '1';
                        total++;
                    }
                }

                //Now general case for anything not on an edge
                else if(find_seat(j-1,i+1,room,1) == '#' || find_seat(j,i+1,room,2) == '#' || find_seat(j+1,i+1,room,3) == '#' || find_seat(j-1,i,room,4) == '#' || find_seat(j+1,i,room,6) == '#' || find_seat(j-1,i-1,room,7) == '#' || find_seat(j,i-1,room,8) == '#' || find_seat(j+1,i-1,room,9) == '#')
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
                    if(find_seat(j-1,i-1,room,7) == '#')
                        adjacent++;
                    if(find_seat(j,i-1,room,8) == '#')
                        adjacent++;
                    if(find_seat(j+1,i-1,room,9) == '#')
                        adjacent++;
                    if(find_seat(j-1,i,room,4) == '#')
                        adjacent++;
                    if(find_seat(j+1,i,room,6) == '#')
                        adjacent++;
                    if(find_seat(j-1,i+1,room,1) == '#')
                        adjacent++;
                    if(find_seat(j,i+1,room,2) == '#')
                        adjacent++;
                    if(find_seat(j+1,i+1,room,3) == '#')
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
    //Update the room in accordance with which seats should have been changed
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

//DEBUG: visually verify room changes match expectations
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
