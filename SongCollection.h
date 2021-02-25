#ifndef SONGCOLLECTION_HEADER
#define SONGCOLLECTION_HEADER

#include <iostream>

#include "Playlist.cpp"

using namespace std;

class SongCollection {
private:
	LinkedList<Song> songs;
	LinkedList<Playlist> playlists;
public:
	void addSong(Song* song);
	void deleteSong(Song* song);
	void listSongs();
	Song* getSong(string title);
	LinkedList<Song>* getSongs();

	void addPlaylist(Playlist* playlist);
	void deletePlaylist(Playlist* playlist);
	void listPlaylists();
	void listPlaylistsContainSong(Song* song);
	Playlist* getPlaylist(string playlist);
	LinkedList<Playlist>* getPlaylists();
};
#endif