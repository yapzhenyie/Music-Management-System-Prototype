#ifndef FILEUTIL_CPP
#define FILEUTIL_CPP

#include <iostream>
#include <fstream>
#include <string>
#include "FileUtil.h"

using namespace std;

void FileUtil::loadFiles(SongCollection& songCollection) {
    {
        string title, singer, duration, empty;
        ifstream readFile;
        readFile.open("Songs.txt");
        if (readFile.is_open()) {
            while (readFile.good()) {
                getline(readFile, title);
                if (title == "") {
                    break;
                }
                getline(readFile, singer);
                getline(readFile, duration);
                getline(readFile, empty);
                songCollection.addSong(new Song(title, singer, stoi(duration)));
            }
            readFile.close();
        } else {
            cout << "Unable to open Songs.txt file." << endl;
        }
    }
    {
        string playlistName, songTitle;
        ifstream readFile;
        readFile.open("Playlists.txt");
        if (readFile.is_open()) {
            while (readFile.good()) {
                getline(readFile, playlistName);
                if (playlistName == "") {
                    break;
                }
                songCollection.addPlaylist(new Playlist(playlistName));
                Playlist* playlist = songCollection.getPlaylist(playlistName);
                while (readFile.good()) {
                    getline(readFile, songTitle);
                    if (songTitle == "") {
                        break;
                    }
                    Song* songToAdd = songCollection.getSong(songTitle);
                    if (songToAdd != NULL) {
                        playlist->addSong(songToAdd);
                    } else {
                        cout << "Fail to add song " << songTitle << " to playlist: " << playlistName << "." << endl;
                    }
                }
            }
            readFile.close();
        } else {
            cout << "Unable to open Playlists.txt file." << endl;
        }
    }
}

void FileUtil::saveFiles(SongCollection& songCollection) {
    {
        ofstream myfile("Songs.txt");
        if (myfile.is_open()) {
            NodeType<Song>* current = songCollection.getSongs()->getHead();
            while (current != NULL) {
                myfile << current->data->getTitle() << endl;
                myfile << current->data->getSinger() << endl;
                myfile << current->data->getDuration() << endl;
                myfile << "" << endl;
                current = current->node;
            }

            myfile.close();
        } else {
            cout << "Unable to open Songs.txt file." << endl;
        }
    }

    {
        ofstream myfile("Playlists.txt");
        if (myfile.is_open()) {
            NodeType<Playlist>* current = songCollection.getPlaylists()->getHead();
            while (current != NULL) {
                myfile << current->data->getName() << endl;
                NodeType<Song>* songs = current->data->getSongs()->getHead();
                while (songs != NULL) {
                    myfile << songs->data->getTitle() << endl;
                    songs = songs->node;
                }
                myfile << "" << endl;
                current = current->node;
            }

            myfile.close();
        } else {
            cout << "Unable to open Playlists.txt file." << endl;
        }
    }
}
#endif