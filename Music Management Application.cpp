#include <iostream>
#include <fstream>
#include <string>

#include "SongCollection.h"
#include "FileUtil.h"

using namespace std;

void musicManagementMessages();
void songsCollectionMessages();
void playlistMessages();
void editPlaylistMessages();
void playlistNavigationMessages();

int option = 0;
SongCollection songCollection{};
Playlist* selectedPlaylist;

int songPlay = 0;
bool playingSong = false;

int main() {
    FileUtil().loadFiles(songCollection);
    musicManagementMessages();
    FileUtil().saveFiles(songCollection);
    return 0;
}

void musicManagementMessages() {
    cout << "Welcome to the Music Management Application." << endl;
    cout << "Please select an option from the list by typing the number." << endl;
    cout << "1 - Manage Songs Collection" << endl;
    cout << "2 - Manage Playlist" << endl;
    cout << "3 - Quit Application" << endl;
    cout << "Your option: ";
    cin >> option;

    //check the input is match with the variable data type.
    while (cin.fail() || option < 1 || option > 3) {
        cin.clear(); // clear the error flag status of cin.fail().
        cin.ignore(); // ignore the previous input.
        cout << "Invalid input. Please try again." << endl;
        cout << "Your option: ";
        cin >> option;
    }
    switch (option) {
    case 1:
        cout << endl;
        option = 0;
        songsCollectionMessages();
        break;
    case 2:
        cout << endl;
        option = 0;
        playlistMessages();
        break;
    case 3:
        cout << "Thank you for using Music Management Application." << endl;
        break;
    }
}

void songsCollectionMessages() {
    cout << "------------------[Songs Collection]------------------" << endl;
    cout << "Please select an option from the list by typing the number." << endl;
    cout << "1 - Display Songs" << endl;
    cout << "2 - Add Songs" << endl;
    cout << "3 - Delete Songs" << endl;
    cout << "4 - Playlist Search" << endl;
    cout << "5 - Back To Main" << endl;
    cout << "Your option: ";
    cin >> option;

    while (cin.fail() || option < 1 || option > 5) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again." << endl;
        cout << "Your option: ";
        cin >> option;
    }
    switch (option) {
    case 1:
    {
        cout << endl;
        option = 0;
        songCollection.listSongs();
        cout << endl;
        songsCollectionMessages();
        break;
    }
    case 2:
    {
        cout << endl;
        option = 0;
        string title = "";
        string singer = "";
        int duration = 0;
        cout << "Add new song to the collection." << endl;
        cout << "\tTitle: ";
        cin.clear();
        cin.ignore();
        getline(cin, title);

        if (songCollection.getSong(title) != NULL) {
            cout << "The song \"" << title << "\" is already exists in the collection." << endl;
        } else {
            cout << "\tSinger: ";
            getline(cin, singer);
            cout << "\tDuration(seconds): ";
            cin >> duration;
            while (cin.fail()) {
                cout << "\tDuration(seconds): ";
                cin.clear();
                cin.ignore();
                cin >> duration;
            }
            songCollection.addSong(new Song(title, singer, duration));
            cout << "New Song: " << title << " (" << singer << ") - " << duration << "s" << endl;
            cout << "Successfully added the song \"" << title << "\" into the collection." << endl;
        }
        cout << endl;
        songsCollectionMessages();
        break;
    }
    case 3:
    {
        cout << endl;
        option = 0;
        string title = "";
        cout << "Please enter the title of the song to be deleted." << endl;
        cout << "Title: ";
        cin.clear();
        cin.ignore();
        getline(cin, title);

        Song* songDelete = songCollection.getSong(title);
        if (songDelete == NULL) {
            cout << "The song \"" << title << "\" does not found in the collection." << endl;
        } else {
            songCollection.deleteSong(songDelete);
            cout << "Successfully deleted the song \"" << title << "\" from the collection." << endl;
        }
        cout << endl;
        songsCollectionMessages();
        break;
    }
    case 4:
    {
        cout << endl;
        option = 0;
        string title = "";
        cout << "Please enter the title of the song to list out the playlists that contain the song." << endl;
        cout << "Title: ";
        cin.clear();
        cin.ignore();
        getline(cin, title);

        Song* songSelected = songCollection.getSong(title);
        if (songSelected == NULL) {
            cout << "The song \"" << title << "\" does not found in the collection." << endl;
        } else {
            songCollection.listPlaylistsContainSong(songSelected);
        }
        cout << endl;
        songsCollectionMessages();
        break;
    }
    case 5:
    {
        cout << endl;
        option = 0;
        musicManagementMessages();
        break;
    }
    }
}

void playlistMessages() {
    cout << "------------------[Playlist]------------------" << endl;
    cout << "Please select an option from the list by typing the number." << endl;
    cout << "1 - View Playlists" << endl;
    cout << "2 - Create Playlist" << endl;
    cout << "3 - Delete Playlist" << endl;
    cout << "4 - Edit Playlist" << endl;
    cout << "5 - Playlist Navigation" << endl;
    cout << "6 - Back To Main" << endl;
    cout << "Your option: ";
    cin >> option;

    while (cin.fail() || option < 1 || option > 6) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again." << endl;
        cout << "Your option: ";
        cin >> option;
    }
    switch (option) {
    case 1:
    {
        cout << endl;
        option = 0;
        songCollection.listPlaylists();
        cout << endl;
        playlistMessages();
        break;
    }
    case 2:
    {
        cout << endl;
        option = 0;
        string playlistName = "";
        cout << "Please enter the name of the playlist to be created." << endl;
        cout << "Playlist Name: ";
        cin.clear();
        cin.ignore();
        getline(cin, playlistName);

        if (songCollection.getPlaylist(playlistName) != NULL) {
            cout << "The playlist named \"" << playlistName << "\" is already exists." << endl;
        } else {
            songCollection.addPlaylist(new Playlist(playlistName));
            cout << "Successfully created the playlist named \"" << playlistName << "\"." << endl;
        }
        cout << endl;
        playlistMessages();
        break;
    }
    case 3:
    {
        cout << endl;
        option = 0;
        string playlistName = "";
        cout << "Please enter the name of the playlist to be deleted." << endl;
        cout << "Playlist Name: ";
        cin.clear();
        cin.ignore();
        getline(cin, playlistName);

        Playlist* playlistDelete = songCollection.getPlaylist(playlistName);
        if (playlistDelete == NULL) {
            cout << "The playlist \"" << playlistName << "\" does not found." << endl;
        } else {
            songCollection.deletePlaylist(playlistDelete);
            cout << "Successfully deleted the playlist \"" << playlistName << "\"." << endl;
        }
        cout << endl;
        playlistMessages();
        break;
    }
    case 4:
    {
        cout << endl;
        option = 0;
        string playlistName = "";
        cout << "Please enter the name of the playlist to be edited." << endl;
        cout << "Playlist Name: ";
        cin.clear();
        cin.ignore();
        getline(cin, playlistName);

        Playlist* playlist = songCollection.getPlaylist(playlistName);
        if (playlist == NULL) {
            cout << "Playlist \"" << playlistName << "\" could not be found." << endl;
            cout << endl;
            playlistMessages();
        } else {
            selectedPlaylist = playlist;
            editPlaylistMessages();
        }
        break;
    }
    case 5:
    {
        cout << endl;
        option = 0;
        string playlistName = "";
        cout << "Please enter the name of the playlist for song navigation." << endl;
        cout << "Playlist Name: ";
        cin.clear();
        cin.ignore();
        getline(cin, playlistName);

        Playlist* playlist = songCollection.getPlaylist(playlistName);
        if (playlist == NULL) {
            cout << "Playlist \"" << playlistName << "\" could not be found." << endl;
            cout << endl;
            playlistMessages();
        } else {
            if (playlist->getSongs()->getSize() == 0) {
                cout << "Playlist \"" << playlistName << "\" does not contains any song." << endl;
                cout << endl;
                playlistMessages();
            } else {
                selectedPlaylist = playlist;
                songPlay = 0;
                playingSong = false;
                playlistNavigationMessages();
            }
        }
        break;
    }
    case 6:
        cout << endl;
        option = 0;
        musicManagementMessages();
        break;
    }
}

void editPlaylistMessages() {
    if (selectedPlaylist == NULL) {
        cout << "An error occurred, please try again." << endl;
        cout << endl;
        option = 0;
        playlistMessages();
        return;
    }

    cout << "------------------[Edit Playlist: " << selectedPlaylist->getName() << "]------------------" << endl;
    cout << "Please select an option from the list by typing the number." << endl;
    cout << "1 - View Songs" << endl;
    cout << "2 - Add Song" << endl;
    cout << "3 - Remove Song" << endl;
    cout << "4 - Back To Playlist" << endl;
    cout << "Your option: ";
    cin >> option;

    while (cin.fail() || option < 1 || option > 4) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again." << endl;
        cout << "Your option: ";
        cin >> option;
    }
    switch (option) {
    case 1:
    {
        cout << endl;
        option = 0;
        selectedPlaylist->listSongs();
        cout << endl;
        editPlaylistMessages();
        break;
    }
    case 2:
    {
        cout << endl;
        option = 0;
        string title = "";
        cout << "Please enter the song title to be added into playlist \""<< selectedPlaylist->getName() << "\"." << endl;
        cout << "Title: ";
        cin.clear();
        cin.ignore();
        getline(cin, title);

        Song* songToAdd = songCollection.getSong(title);
        if (songToAdd == NULL) {
            cout << "The song \"" << title << "\" does not found in the collection. You can only add songs that is available in the collection." << endl;
        } else {
            if (!selectedPlaylist->hasSong(songToAdd)) {
                selectedPlaylist->addSong(songToAdd);
                cout << "Successfully added the song \"" << title << "\" into playlist \"" << selectedPlaylist->getName() << "\"." << endl;
            } else {
                cout << "The song \"" << title << "\" already exists in this playlist." << endl;
            }
        }
        cout << endl;
        editPlaylistMessages();
        break;
    }
    case 3:
    {
        cout << endl;
        option = 0;
        string title = "";
        cout << "Please enter the song title to be removed from playlist \"" << selectedPlaylist->getName() << "\"." << endl;
        cout << "Title: ";
        cin.clear();
        cin.ignore();
        getline(cin, title);

        Song* songToRemove = songCollection.getSong(title);
        if (songToRemove == NULL) {
            cout << "The song \"" << title << "\" does not found in the collection, it's an invalid song." << endl;
        } else {
            if (selectedPlaylist->hasSong(songToRemove)) {
                selectedPlaylist->removeSong(songToRemove);
                cout << "Successfully removed the song \"" << title << "\" from playlist \"" << selectedPlaylist->getName() << "\"." << endl;
            } else {
                cout << "The song \"" << title << "\" does not exists in this playlist." << endl;
            }
        }
        cout << endl;
        editPlaylistMessages();
        break;
    }
    case 4:
        cout << endl;
        option = 0;
        selectedPlaylist = NULL;
        playlistMessages();
        break;
    }
}

void playlistNavigationMessages() {
    if (selectedPlaylist == NULL || selectedPlaylist->getSongs()->getSize() == 0) {
        cout << "An error occurred, please try again." << endl;
        cout << endl;
        option = 0;
        playlistMessages();
        return;
    }

    cout << "------------------[Playlist Navigation: " << selectedPlaylist->getName() << "]------------------" << endl;
    cout << "Please select an option from the list by typing the number." << endl;
    cout << "1 - Previous Song" << endl;
    cout << "2 - Play/Pause" << endl;
    cout << "3 - Next Song" << endl;
    cout << "4 - Random Song" << endl;
    cout << "5 - Back To Playlist" << endl;
    cout << "Your option: ";
    cin >> option;

    while (cin.fail() || option < 1 || option > 5) {
        cin.clear();
        cin.ignore();
        cout << "Invalid input. Please try again." << endl;
        cout << "Your option: ";
        cin >> option;
    }
    switch (option) {
    case 1:
    {
        cout << endl;
        option = 0;
        songPlay--;
        if (songPlay <= 0) {
            songPlay = 0;
            Song* currentSong = selectedPlaylist->getSong(songPlay);
            playingSong = true;
            cout << "Song \"" << currentSong->getTitle() << "\" is already the first song in playlist \"" << selectedPlaylist->getName() << "\"." << endl;
        } else {
            Song* currentSong = selectedPlaylist->getSong(songPlay);
            playingSong = true;
            cout << "Previous song..." << endl;
            cout << "Now playing - " << currentSong->getTitle() << endl;
        }
        cout << endl;
        playlistNavigationMessages();
        break;
    }
    case 2:
    {
        cout << endl;
        option = 0;
        Song* currentSong = selectedPlaylist->getSong(songPlay);

        if (playingSong) {
            playingSong = false;
            cout << "Pause song - " << currentSong->getTitle() << endl;
        } else {
            playingSong = true;
            cout << "Now playing - " << currentSong->getTitle() << endl;
        }
        cout << endl;
        playlistNavigationMessages();
        break;
    }
    case 3:
    {
        cout << endl;
        option = 0;
        songPlay++;
        if (songPlay >= selectedPlaylist->getSongs()->getSize()) {
            songPlay = selectedPlaylist->getSongs()->getSize() - 1;
            Song* currentSong = selectedPlaylist->getSong(songPlay);
            playingSong = true;
            cout << "Song \"" << currentSong->getTitle() << "\" is already the last song in playlist \"" << selectedPlaylist->getName() << "\"." << endl;
        } else {
            Song* currentSong = selectedPlaylist->getSong(songPlay);
            playingSong = true;
            cout << "Next song..." << endl;
            cout << "Now playing - " << currentSong->getTitle() << endl;
        }
        cout << endl;
        playlistNavigationMessages();
        break;
    }
    case 4:
    {
        cout << endl;
        option = 0;
        songPlay = rand() % selectedPlaylist->getSongs()->getSize();
        Song* currentSong = selectedPlaylist->getSong(songPlay);
        playingSong = true;
        cout << "Play random song." << endl;
        cout << "Now playing - " << currentSong->getTitle() << endl;

        cout << endl;
        playlistNavigationMessages();
        break;
    }
    case 5:
        cout << endl;
        option = 0;
        selectedPlaylist = NULL;
        playlistMessages();
        break;
    }
}

