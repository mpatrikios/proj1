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
    string songTime; //in seconds
};

// total album time
string total_time(set<songInfo> songs){}

// convert song time to seconds
void convertToSeconds(string songTime){}

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

    for (auto artistPair : lib_info) { //iterate through lib_info map by pairs
        string artist = artistPair.first; //key of iterator
        const set<songInfo> songs = artistPair.second; //access the set of stongs stored as the value

        //print artist name, number of songs, and total album time
        cout << artist << ": " << songs.size() << "Total time: "
             << totalTime(songs) << endl;

        string albumName = songs.begin()->albumName; //assuming no artist will have more than one album

        //creates a new map that sorts songs by album name under the same artist
        //dont know if necessary
        // map<string, set<songInfo>> albumMap;
        // for (const auto& song : songs) {
        //     albumMap[song.albumName].insert(song);
        // }

        //print album name, number of songs, and total album time
        cout << "  " << albumName << ": " << songs.size() << "Total time: "
            << totalTime(songs) << "" << endl; 

        //another for loop, print every song in the set with its track number and time
        for (auto song : songs) {
                cout << "    " << song.trackNumber << ". " << song.songName << ": "
                     << song.songTime << endl;
            }
        }

    return 0;
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

