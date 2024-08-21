#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>

using namespace std;

struct songInfo{
    string albumName;
    int trackNumber;
    string songName;
    int songTime; //in seconds
};

int main(int argc, char *argv[]){
    string inputFile;
    inputFile = argv[1];
    ifstream file(inputFile);

    string tempLine, artistName, genre;
    map <string, set<songInfo>> lib_info;

    while(getline(file, tempLine)){
        //replace underscores with space
        for(int i = 0; i < tempLine.size(); i++){
            if(tempLine[i] == '_'){
                tempLine[i] = ' ';
            }
        }

        songInfo tempSong;
        stringstream ss(tempLine);
        ss >> tempSong.songName;
        ss >> tempSong.albumName;
        ss >> artistName; //key
        ss >> tempSong.albumName;
        ss >> genre; //don't need
        ss >> tempSong.trackNumber;

        lib_info[artistName].insert(tempSong);

    }

    for( size_t i = 0; i < lib_info.size(); i++){
        cout << lib
    }

}

//1st ArtistName: numofSongs, totalalbumnTime
//2nd AlbumnName: TotalSongs, totalalbumnTime

//For each albumn
//tracknum. songname: songtime

//want the artists printed in alphabetical order
//want the songs printed in track order
//how to order track number
//total song time
//convert song time to seconds

