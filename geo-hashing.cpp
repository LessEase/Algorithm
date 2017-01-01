/*************************************************************************
	> File Name: geo-hashing.cpp
	> Author: chenshaoyi
	> Mail: chshaoyi7@gmail.com
	> Created Time: 一 12/26 10:06:20 2016
 ************************************************************************/

#include<iostream>
#include<map>
#include<string>
using namespace std;

struct Position{
    double latitude;
    double longitude;
};

class GeoHasher{
    private:
        map<int, char> binary2char_dict_;
        map<char, int> char2binary_dict_;
    public:
        GeoHasher();
        //precision is the length of hashed string
        string   Encode(Position& pos, int precision);
        Position Decode(string& hashstr);
};

GeoHasher::GeoHasher(){
    for(int i=0; i<10; i++){
        binary2char_dict_[i] = '0' + i;
        char2binary_dict_['0'+i] = i;
    }
    
    char c;
    int cnt=10;
    for(int i=0; i<26; i++){
       c = 'a' + i; 
       if('a'==c||'i'==c||'l'==c||'o'==c)
            continue;

       binary2char_dict_[cnt] = c; 
       char2binary_dict_[c] = cnt;
       cnt ++;
    }
}


string GeoHasher::Encode(Position& pos, int precision){
    int length = precision * 5;
    string hashstr="";
    double latitude_range[2]  ={-90.0, 90.0};
    double longitude_range[2] ={-180.0, 180.0};
    double mid;
    int bits=0;
    for(int i=0; i<length; i++){
        if(i%2==1){ // latitude
           mid = (latitude_range[0] + latitude_range[1])/2; 
            if(pos.latitude<mid){
                bits <<= 1;
                latitude_range[1] = mid;
            }else{
                bits <<= 1;
                bits |= 1;
                latitude_range[0] = mid;
            }
        }else{// longitude
           mid = (longitude_range[0] + longitude_range[1])/2;
              if(pos.longitude<mid){
                  bits <<= 1;
                  longitude_range[1] = mid;
              }else{
                  bits <<= 1;
                  bits |= 1;
                  longitude_range[0] = mid;
              }
        }
        
        if((i+1)%5==0){
            hashstr += binary2char_dict_[bits];
            bits = 0;
        }
    }

    return hashstr;
}

Position GeoHasher::Decode(string& hashstr){
    Position pos; 
    double latitude_range[2]  ={-90.0, 90.0};
    double longitude_range[2] ={-180.0, 180.0};
    double mid;
    int bits=0;
    int bit;
    int islatitude=false;
    for(int i=0; i<hashstr.size(); i++){
        bits = char2binary_dict_[hashstr[i]];
        for(int j=4; j>=0; j--){
           bit = (bits>>j)&1; 
            if(islatitude){
                mid = (latitude_range[0] + latitude_range[1])/2;  
                if(bit) latitude_range[0] = mid;
                else latitude_range[1] = mid;
            }else{
                mid = (longitude_range[0] + longitude_range[1])/2;
                if(bit) longitude_range[0] = mid;
                else    longitude_range[1] = mid;
            }
            islatitude = !islatitude;
        }
    } 

    pos.latitude = (latitude_range[0]+latitude_range[1])/2;
    pos.longitude = (longitude_range[0]+longitude_range[1])/2;

    return pos;
}


int main(){
    
    GeoHasher hasher;
    Position pos;
    string hashstr;
    int m, n;
    cin >> m >> n;
    while(m--){
        cin >> pos.latitude >> pos.longitude;
        cout << hasher.Encode(pos, 10) << endl;
    }

    cout.setf(ios::fixed);
    cout.precision(6);
    while(n--){
        cin >> hashstr;
        pos = hasher.Decode(hashstr);
        cout << pos.latitude << " " << pos.longitude << endl;
    }
    return 0;
}
