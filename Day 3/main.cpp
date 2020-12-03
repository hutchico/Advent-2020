#include <iostream>
#include <fstream>
#include <vector>

using std::vector;
using std::string;
using std::cout;
using std::endl;

int check_trees(vector<string> &data,int slopeX, int slopeY){
    int posX = 0;
    int posY = slopeY;
    int num_trees = 0;
    //Right X, Down Y
    //Use change in posY as an iterator
    for(; posY < data.size(); posY += slopeY){
        posX += slopeX;
        if(posX >= 31)
            posX -= 31;   //Wrap around rather than repeating the dataset itself
        if(data[posY][posX] == '#'){
            num_trees++;
        }
    }

    return num_trees;
}

int main()
{
    vector<string> input;
    string buffer;
    std::ifstream file;
    int tree_product = 0;

    file.open("input.txt");
    while(true){
        getline(file,buffer);
        if(file.eof() == true)
            break;
        input.push_back(buffer);
    }
    file.close();

    tree_product = check_trees(input,3,1);  //Use this as a holder at first, name becomes valid for part 2.
    cout << tree_product << endl;

    tree_product *= check_trees(input,1,1);
    tree_product *= check_trees(input,5,1);
    tree_product *= check_trees(input,7,1);
    tree_product *= check_trees(input,1,2);

    cout << tree_product << endl;

    return 0;
}
