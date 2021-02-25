#ifndef PLAYLIST_CPP
#define PLAYLIST_CPP

#include "Song.cpp"
#include "LinkedList.cpp"

using namespace std;

class Playlist {
private:
	string name;
	LinkedList<Song> songs;
public:
	Playlist(string name) {
		this->name = name;
	}
	string getName() {
		return this->name;
	}
	bool hasSong(Song* song) {
		if (songs.contains(song)) {
			return true;
		}
		return false;
	}
	Song* getSong(int index) {
		return songs.get(index);
	}
	void addSong(Song* song) {
		if (songs.contains(song)) {
			return;
		}
		songs.add(song);
	}
	void removeSong(Song* song) {
		songs.remove(song);
	}
	void listSongs() {
		if (songs.getSize() == 0) {
			cout << "No song is available in the playlist named \"" << this->name << "\"." << endl;
			return;
		}
		NodeType<Song>* current = songs.getHead();
		int i = 1;
		cout << "Listing " << songs.getSize() << " songs for playlist: " << this->name << endl;
		while (current != NULL) {
			cout << i++ << ". " << current->data->getTitle() << " (" << current->data->getSinger() << ") - " << current->data->getDuration() << "s" << endl;
			current = current->node;
		}
	}
	LinkedList<Song>* getSongs() {
		return &this->songs;
	}
	string getIdentifier() {
		return "playlist:" + this->name;
	}
};
#endif