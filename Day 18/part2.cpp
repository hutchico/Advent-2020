#include <iostream>
#include <fstream>
#include <string>
#include <vector>
#include <sstream>
#include "part2.h"
#include "uint128_t.h"

using std::vector;
using std::cout;
using std::endl;
using std::string;
using std::to_string;

void resolve_parens(string &line, int pos, int &rear){
    long long ri = 0;
    long long li = 0;
    int close = 0;
    char input;
    string strput = "";
    int bk = pos;
    bool do_pass = true;
 //   cout << pos << " " << line[pos] << endl;
    while(true){
  //      cout << pos << " " << rear << " " << line.size() << endl;
        pos++;
        if(pos >= rear)
            break;
        input = line[pos];
        if(input == 'n')
            resolve_parens(line,pos,rear);
        if(input == 'd' && close == 0) //end bound for this run, ignore further instances of )
            close = pos;
    }
 //   cout << close << endl;
    pos = bk;
    //similar function to resolve_eq, do a pass resolving addition and then one for mult.
    //Precondition: The section of line defined by (pos,close) is of form x+*y+*z...n
    //Similarly: Expectation is any symbol of form x+y, x and y will both be single digits.
 //   cout << "pos: " << pos << endl;
 //   cout << "covering between " << line[pos] << " and " << line[close] << endl;
    while(true){
        if(pos >= close)
            break;
  //      cout << pos << " " << line[pos] << endl;
        if(line[pos] != '+'){
            pos++;
            continue;
        }
        pos--;
        while(line[pos] != '*' && line[pos] != '+' && line[pos] != 'n'){
            pos--;
        }
        strput = "";
  //      cout << "pos: " << pos << endl;
        while(true){
            if(close > pos && line[pos+1] != '+' && line[pos+1] != 'd' && line[pos+1] != 'n' && line[pos+1] != '*'){
                pos++;
  //              cout << "appendadd1: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
            }
            else{
                pos+=1;
                break;
            }
        }
        ri = convert(strput);
        string risize = to_string(ri);
        strput = "";
        while(true){
            if(close > pos && line[pos+1] != '+' && line[pos+1] != '*' && line[pos+1] != 'd' && line[pos+1] != 'n'){
                pos++;
 //               cout << "appendadd2: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
            }
            else{
                pos+=1;
                break;
            }
        }
        li = convert(strput);
        string lisize = to_string(li);
//        cout << "adding " << ri << " and " << li << endl;
        ri = ri + li;
        string riprod = to_string(ri);
 //       cout << pos << endl;
        pos = pos - (1 + lisize.size() + risize.size());
 //       cout << line << endl;
        line.erase(pos,1 + lisize.size() + risize.size());
 //       cout << line << endl;
        line.insert(pos,riprod);
 //       cout << line << endl;
        int adjust = 1 + lisize.size() + risize.size() - riprod.size();
        rear -= adjust;
        close -= adjust;
//        cout << close << " " << rear << " " << line.size() << endl;
        pos++;
        int tmp = bk;
        while(tmp <= close){
            do_pass = false;
            if(line[tmp] == '+'){
                do_pass = true;
                break;
            }
            tmp++;
        }
    }
    pos = bk;
    //Precondition for multiplicative pass:
    //      the string is of form (x) or (x*y*z)
    while(true){
        if(pos >= close)
            break;
        if(line[pos] == '*'){
            do_pass = true;
            break;
        }
        pos++;
    }

    while(do_pass){
        strput = "";
 //       cout << pos << " t " << close << endl;
        if(pos >= close)
            break;
        pos = bk;
        while(true){
            if(close > pos && line[pos+1] != '*' && line[pos+1] != 'd'){
                pos++;
  //              cout << "append1: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
            }
            else{
                if(close - pos >= 2)
                    pos+=1;
                break;
            }
        }
        ri = convert(strput);
        strput = "";
        while(true){
            if(close > pos && line[pos+1] != '*' && line[pos+1] != 'd'){
                pos++;
 //               cout << "append2: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
            }
            else{
                pos+=1;
                break;
            }
        }
        li = convert(strput);
//        cout << ri << " and " << li << endl;
        string risize = std::to_string(ri);
        string lisize = std::to_string(li);
        ri = ri * li;
//        cout << line << endl;
 //       cout << bk << endl;
        string ri_prod = std::to_string(ri);

        pos = pos - (1 + lisize.size() + risize.size());
//        cout << line << endl;
        line.erase(pos,1 + lisize.size() + risize.size());
 //       cout << line << endl;
        line.insert(pos,ri_prod);
 //       cout << line << endl;
        int adjust = lisize.size() + risize.size() + 1 - ri_prod.size(); //total change in array length
        rear -= adjust;
 //       cout << line.size() << " " << rear << " " << adjust << " " << close << endl;
        close -= adjust;
        int tmp = bk;
        while(tmp <= close){
            do_pass = false;
            if(line[tmp] == '*'){
                do_pass = true;
                break;
            }
            tmp++;
        }
    }
    pos = bk;
 //   cout << "line pre paren: " << line << endl;
 //   cout << pos << " " << close << endl;
    line.erase(pos,1);
    line.erase(close-1,1);
//    cout << "line after paren: " << line << endl;
    rear -= 2;
};

uint64_t resolve_eq(string &line, int pos, int rear){
    uint64_t sum = 1;
    int close;
    int bk = pos;
    int ri;
    int li;
    bool do_pass = false;
    string strput = "";
    //Resolve all parentheses first
    while(line[pos] != 'n' && pos < rear) //find first instance of parens, go from there
        pos++;
    if(pos != rear) //implying there are parentheses to be dealt with
        resolve_parens(line, pos, rear);
    pos = bk;
  //  cout << endl << line << endl;
    //Pass resolving addition
    //Precondition for this segment: Line is of form x+*y+*z...n
    while(true){
        strput = "";
        close = rear;
        int oldpos;
//        cout << line << endl;
//        cout << pos << " " << rear << " " << line.size() << " " << line[pos] << endl;
        if(pos >= rear)
            break;
        if(line[pos] != '+'){
            pos++;
            continue;
        }
        pos--;
        while(pos > 0 && line[pos-1] != '*' && line[pos-1] != '+'){
            pos--;
        }
        oldpos = pos;
//        cout << pos << endl;
        while(true){
            if(close > pos && line[pos] != '*' && line[pos] != '+'){
  //              cout << "append2: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
                pos++;
            }
            else{
                pos+=1;
                break;
            }
        }
        ri = convert(strput);
        string rilen = to_string(ri);
        strput = "";
//        cout << pos << " " << close << endl;
        while(true){
            if(close > pos && line[pos] != '*' && line[pos] != '+'){
  //              cout << "append2: " << line[pos] << endl;
                strput.append(string(1,line[pos]));
                pos++;
            }
            else{
                pos+=1;
                break;
            }
        }
        li = convert(strput);
        string lilen = to_string(li);
 //       cout << "added " << ri << " and " << li << endl;
        ri = ri + li;
        string riprod = to_string(ri);
//        cout << "erasing " << 1+rilen.size()+lilen.size() << " at " << oldpos << endl;
        line.erase(oldpos,1+rilen.size()+lilen.size());
        line.insert(oldpos,riprod);
        rear = line.size();
        pos = 0;
 //       cout << line.size() << " " << rear << " " << adjust << " " << close << endl;
    }
    //Pass resolving multiplication
    //This should be easily tokened if it's not already resolved
 //   cout << line << endl;
    pos = 0;
    close = line.size();
    std::stringstream ss;
    while(pos <= close){    //check if there's math to do
        if(line[pos] == '*'){
            do_pass = true;
            break;
        }
        pos++;
    }
    if(do_pass){
        line.append("*");
        ss.str(line);
        string buffer;
        getline(ss,buffer,'*');
        sum = sum * stoll(buffer);
        while(!ss.eof()){
            getline(ss,buffer,'*');
            if(buffer == "")
                break;
            sum *= stoll(buffer);
        }
    }
    else
        sum = stoll(line);
    cout << sum << endl << endl;
    return sum;
}

int main()
{
    std::ifstream file;
    string buffer;
    vector<string> math;

    unsigned long long sum = 0;

    file.open("input.txt");
    while(true){
        string actual = "";
        getline(file,buffer);
        if(buffer == "")
            break;
        while(buffer.size() > 0){
            char input = buffer[0];
            buffer.erase(0,1);
            if(input == ' ')
                continue;
            else if(input == '(')
                actual.append("n");
            else if(input == ')')
                actual.append("d");
            else
                actual.append(string(1,input));
        }
        math.push_back(actual);
    }
    //cout << math[5] << endl;
    //cout << resolve_eq(math[5]) << endl;

    ///OOO flow: operations resolved left to right; when right operand is a parenthetical, the right operand is resolved first

    for(int i = 0; i < math.size(); i++){
 //       cout << math[i] << endl;
        uint64_t part = resolve_eq(math[i],0,math[i].size());
  //      cout << endl;
        sum += part;
    }
    cout << sum << endl;
    return 0;
}
