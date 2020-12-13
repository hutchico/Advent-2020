#include <iostream>
#include <fstream>
#include <vector>
#include <sstream>
#include <numeric>
#include <execution>
#include <algorithm>

using namespace std;

uint64_t mulInv(uint64_t a, uint64_t b) {
	uint64_t b0 = b, t, q;
	uint64_t x0 = 0, x1 = 1;
	if (b == 1) return 1;
	while (a > 1) {
		q = a / b;
		t = b, b = a % b, a = t;
		t = x0, x0 = x1 - q * x0, x1 = t;
	}
	if (x1 < 0) x1 += b0;
	return x1;
}

uint64_t chineseRemainder(vector<int> n, vector<int> a) {
    //TODO: Figure out why this is producing integer over/underflow
    uint64_t prod = 1;
    int64_t p;
    int64_t sum = 0;
    uint64_t i;


	for (i = 0; i < n.size(); i++) prod *= n[i];
    cout << prod << endl;
	for (i = 0; i < n.size(); i++) {
		p = prod / n[i];
		sum += a[i] * mulInv(p, n[i]) * p;
		cout << sum << endl;
	}

	return sum % prod;
}



int main()
{
    std::ifstream file;
    string buffer;
    int offs = 0;
    vector<int> bus;
    vector<int> offsets;
    std::stringstream ss;

    file.open("modinput.txt");
    getline(file,buffer); //Discard first line since it has no effect on pt2
    getline(file,buffer);
    buffer.append(",");
    ss.str(buffer);
    while(true){
        getline(ss,buffer,',');
        if(buffer == "x"){
            offs++;
            continue;
        }
        if(ss.eof())
            break;
        else{
            cout << stoi(buffer) << " " << offs << endl;
            bus.push_back(stoi(buffer));
            offsets.push_back(offs * -1);
        }
        offs++;
    }
    file.close();

    cout << chineseRemainder(bus,offsets) << endl;
    /*
    while(true){
        depTime += bus[0];
        cout << depTime << endl;
        for(int i = 0; i < bus.size(); i++){

            cout << bus[i] << " "<< depTime % bus[i] << endl;


            if((depTime + offsets[i]) % bus[i] == 0)
                continue;
            else{
                complete = false;
                break;
            }
        }
        if(complete)
            break;
        else{
            complete = true;
        }
    }

    for(int i = 0; i < bus.size(); i++){
        cout << bus[i] << " ";
    }
    cout << endl;
    */

    return 0;
}
