#include <fstream>
#include <iostream>
#include <map>
#include <set>
#include <sstream>
#include <string>
#include <iomanip>

using namespace std;

struct songInfo{
    string albumName;
    int trackNumber;
    string songName;
    string songTime; // mm:ss
    string totalSongs; // for the artist

    bool operator<(const songInfo& other) const {
        return trackNumber < other.trackNumber;
    }
};

// convert song time to seconds
int convertToSeconds(const string& songTime){
    int minutes = 0;
    int seconds = 0;
    char colon;

    stringstream ss(songTime);
    ss >> minutes >> colon >> seconds; 

    return minutes * 60 + seconds; 
}

// total album time
string totalArtistTime(const map<string, set<songInfo>>& lib_info) {

    int totalSeconds = 0;

    for (const auto& artist : lib_info) {
        for (const auto& song : artist.second) {
            totalSeconds += convertToSeconds(song.songTime);
        }
    }

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    stringstream time; 
    time << minutes << ':' << setw(2) << setfill('0') << seconds;

    return time.str();
}

string totalAlbumTime(const set<songInfo>& songs) {
    int totalSeconds = 0;

    for (const auto& song : songs) {
        totalSeconds += convertToSeconds(song.songTime);
    }

    int minutes = totalSeconds / 60;
    int seconds = totalSeconds % 60;

    stringstream time; 
    time << minutes << ':' << setw(2) << setfill('0') << seconds;

    return time.str();
}

// remove underscores from strings
void removeUnderscores(string& str){
    for (char& c : str){
        if (c == '_'){
            c = ' ';
        }
    }
}

int main(int argc, char *argv[]){
    string inputFile;
    inputFile = argv[1];
    ifstream file(inputFile);

    string tempLine, artistName, genre;
    // map<string, set<songInfo > > lib_info;
    map<string, map<string, set<songInfo > > > lib_info;

    while(getline(file, tempLine)){

        songInfo tempSong;
        stringstream ss(tempLine);
        ss >> tempSong.songName;
        ss >> tempSong.songTime;
        ss >> artistName; //key
        ss >> tempSong.albumName;
        ss >> genre; //don't need
        ss >> tempSong.trackNumber;

        removeUnderscores(tempSong.songName);
        removeUnderscores(artistName);
        removeUnderscores(tempSong.albumName);

        // lib_info[artistName].insert(tempSong);
        lib_info[artistName][tempSong.albumName].insert(tempSong);

        // cout << tempSong.songName << " " << tempSong.albumName << " " << artistName << " " << tempSong.albumName  << " " << tempSong.trackNumber << " " << tempSong.songTime << endl;

    }

    for (auto it = lib_info.begin(); it != lib_info.end(); ++it) {
        string artist = it->first;
        const map<string, set<songInfo>>& albums = it->second; //create a temp map where albums=key and songs in the album are a set (for cases when an aritist has more than one album)
        int totalArtistSongs = 0;

        for (auto album : albums) {
            totalArtistSongs += album.second.size();
        }
        cout << artist << ": " << totalArtistSongs << ", " << totalArtistTime(albums) << endl;

    for (auto albumIt = albums.begin(); albumIt != albums.end(); ++albumIt) {
            const string& albumName = albumIt->first;
            const set<songInfo>& songs = albumIt->second;


            cout << "        " << albumName << ": " << songs.size() << ", " << totalAlbumTime(songs) << endl;

            for (auto song : songs) {
                cout << "                " << song.trackNumber << ". " << song.songName << ": " << song.songTime << endl;
            }
    }
    // for (const auto& artistPair : lib_info) { 
    //     string artist = artistPair.first;
    //     const auto& albums = artistPair.second;

    //     cout << artist << ": " << totalTime(tempSong.albumName) << endl;

    //     for (const auto& albumPair : albums) {
    //         string albumName = albumPair.first;
    //         const auto& songs = albumPair.second;

    //         cout << "  " << albumName << ": " << songs.size() << " Total time: "
    //              << totalTime(songs) << " seconds" << endl;

    //         for (const auto& song : songs) {
    //             cout << "    " << song.trackNumber << ". " << song.songName << ": "
    //                  << song.songTime << endl;
    //         }
    //     }

    // worked orginally for printing out songs but only for one album per artist


    // for (auto artistPair : lib_info) { //iterate through lib_info map by pairs
    //     string artist = artistPair.first; //key of iterator
    //     const set<songInfo> songs = artistPair.second; //access the set of stongs stored as the value

    //     //print artist name, number of songs, and total album time
    //     cout << artist << ": " << songs.size() << "Total time: "
    //          << totalTime(songs) << endl;

    //     string albumName = songs.begin()->albumName; //assuming no artist will have more than one album

    //     //creates a new map that sorts songs by album name under the same artist
    //     //dont know if necessary
    //     map<string, set <songInfo > > albumMap;
    //     for (const auto& song : songs) {
    //        albumMap[song.albumName].insert(song);
    //    }

    //     //print album name, number of songs, and total album time
    //     cout << "  " << albumName << ": " << songs.size() << "Total time: "
    //         << totalTime(songs) << "" << endl; 

        //another for loop, print every song in the set with its track number and time
        // for (auto song : songs) {
        //         cout << "    " << song.trackNumber << ". " << song.songName << ": "
        //              << song.songTime << endl;
        //     }
    }
    return 0;
}


// if statement in main for if artist has more than one key 
// or change total time function to loop through albums and add all song times



