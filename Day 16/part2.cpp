#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <utility>
#include <string>
#include <map>

using std::vector;
using std::string;
using std::cout;
using std::pair;
using std::endl;
using std::string;
using std::map;


struct ruleset{
    vector<string> names;
    vector<vector<pair<int,int>>> ranges;
};

int main()
{
    std::ifstream file;
    std::stringstream ss;
    string readBuffer;  //these names seem meaningful but are functionally temp1, temp2, and temp3
    string parseBuffer;
    string field;

    ruleset rules;
    vector<pair<int,int>> line;
    vector<int> my;
    vector<int> ticket_input;
    vector<int> invalid_values;
    vector<int> fieldVals;
    vector<vector<int>> valid_tickets;
    map<string,int> ticket; //Map the name of a field to its position on the ticket
    map<string,int> fieldTests; //Record how many columns are valid options for a given field name
    map<string,vector<int>> possibleFields;
    map<int,string> validity; //Inverse of fieldTests

    long long invalid_sum = 0;

    file.open("input.txt");
    while(true){                    //process rules
        getline(file,readBuffer);
        if(readBuffer == ""){
            break;
        }
        ss.str(readBuffer);
        getline(ss,readBuffer,':'); //"class": or "departure time":
        field = readBuffer;
        rules.names.push_back(field);
        fieldTests[field] = 0;
        possibleFields[field] = fieldVals; //should be an empty vector at this point
        ss.ignore(1); //drop the space
        getline(ss,readBuffer,'-');
        getline(ss,parseBuffer,' ');
        line.push_back(std::make_pair(stoi(readBuffer),stoi(parseBuffer)));
        ss.ignore(3);
        getline(ss,readBuffer,'-');
        getline(ss,parseBuffer);
        line.push_back(std::make_pair(stoi(readBuffer),stoi(parseBuffer)));
        rules.ranges.push_back(line);
        line.clear();
        std::stringstream().swap(ss);
    }

    getline(file,readBuffer); //your ticket:
    getline(file,readBuffer);
    readBuffer.append(",");
    ss.str(readBuffer);
    for(int i = 0; i < rules.names.size(); i++){
        getline(ss,readBuffer,',');
        my.push_back(stoi(readBuffer));
    }

    getline(file,readBuffer);
    getline(file,readBuffer); //nearby tickets:
    while(true){
        getline(file,readBuffer);
        if(readBuffer == "")
            break;
        readBuffer.append(",");
        std::stringstream().swap(ss);
        ss.str(readBuffer);
        for(int i = 0; i < rules.names.size(); i++){
            getline(ss,readBuffer,',');
            ticket_input.push_back(stoi(readBuffer));
        }


        int cut = 0;
        int overcut = 0;
        for(int i = 0; i < ticket_input.size(); i++){
            cut = 0;
            for(int j = 0; j < rules.names.size(); j++){
                int minLow = rules.ranges[j][0].first;
                int maxLow = rules.ranges[j][0].second;
                int minHgh = rules.ranges[j][1].first;
                int maxHgh = rules.ranges[j][1].second;
                if((ticket_input[i] >= minLow && ticket_input[i] <= maxLow) || (ticket_input[i] >= minHgh && ticket_input[i] <= maxHgh)){
                    cut++;
                }
            }
            if(cut == 0){
                invalid_values.push_back(ticket_input[i]);
                overcut++;
            }
        }

        if(overcut == 0){
            valid_tickets.push_back(ticket_input);
        }
        ticket_input.clear();
    }

    for(int i = 0; i < invalid_values.size(); i++)
        invalid_sum += invalid_values[i];

    cout << invalid_sum << endl;

    for(int i = 0; i < valid_tickets[0].size(); i++){
        for(int j = 0; j < rules.names.size(); j++){
            int cut = 0;
            int minLow = rules.ranges[j][0].first;
            int maxLow = rules.ranges[j][0].second;
            int minHgh = rules.ranges[j][1].first;
            int maxHgh = rules.ranges[j][1].second;
            for(int k = 0; k < valid_tickets.size(); k++){
                if((valid_tickets[k][i] >= minLow && valid_tickets[k][i] <= maxLow) || (valid_tickets[k][i] >= minHgh && valid_tickets[k][i] <= maxHgh)){
                    cut++;
                }
            }
            if(cut == valid_tickets.size()){
                fieldTests[rules.names[j]] = fieldTests[rules.names[j]] + 1;
                possibleFields[rules.names[j]].push_back(i);
            }
        }
    }



    for (const auto& x : fieldTests) {
        validity[x.second] = x.first;
    }

    for(int i = 1; i < 21; i++){
        int correctField;
        field = validity[i];    //get name of field with lowest validity rate
        correctField = possibleFields[field][0]; //Get position this field corresponds to since there should only be one
        ticket[field] = correctField; //map field name to its corresponding CORRECT position
        for (const auto& x : possibleFields) {  //Erase the position in question from all other field possibilities.
            vector<int> values = x.second;
            for(int j = 0; j < x.second.size(); j++){
                if(x.second[j] == correctField){
                    values.erase(values.begin()+j);
                    break;
                }
            }
            possibleFields[x.first] = values;
        }
        //Postcondition should be the next lowest field value has exactly one possible field now
        //repeat for all 20 field positions even though we're only after six of them
    }

    for (const auto& x : ticket) {
        cout << x.first << ": " << x.second + 1<< "\n";
    }
    /*
    cout << my[ticket["departure location"]] << endl;
    cout << my[ticket["departure station"]] << endl;
    cout << my[ticket["departure platform"]] << endl;
    cout << my[ticket["departure track"]] << endl;
    cout << my[ticket["departure date"]] << endl;
    cout << my[ticket["departure time"]] << endl;
    */
    invalid_sum = my[ticket["departure location"]]; //Reuse this variable
    invalid_sum *= my[ticket["departure station"]];
    invalid_sum *= my[ticket["departure platform"]];
    invalid_sum *= my[ticket["departure track"]];
    invalid_sum *= my[ticket["departure date"]];
    invalid_sum *= my[ticket["departure time"]];

    cout << invalid_sum << endl;

    return 0;
}
