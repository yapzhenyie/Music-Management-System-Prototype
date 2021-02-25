#ifndef SONGCOLLECTION_CPP
#define SONGCOLLECTION_CPP

#include "SongCollection.h"

using namespace std;

void SongCollection::addSong(Song* song) {
	if (songs.contains(song)) {
		return;
	}
	songs.add(song);
}

void SongCollection::deleteSong(Song* song) {
	songs.remove(song);

	// Update playlists song
	NodeType<Playlist>* current = playlists.getHead();
	while (current != NULL) {
		NodeType<Song>* songs = current->data->getSongs()->getHead();
		if (current->data->hasSong(song)) {
			current->data->removeSong(song);
		}
		current = current->node;
	}
}

void SongCollection::listSongs() {
	if (songs.getSize() == 0) {
		cout << "No song is available in the collection." << endl;
		return;
	}
	NodeType<Song>* current = songs.getHead();
	int i = 1;
	cout << "Listing " << songs.getSize() << " songs" << endl;
	while (current != NULL) {
		cout << i++ << ". " << current->data->getTitle() << " (" << current->data->getSinger() << ") - " << current->data->getDuration() << "s" << endl;
		current = current->node;
	}
}

Song* SongCollection::getSong(string title) {
	return songs.get("song:" + title);
}


LinkedList<Song>* SongCollection::getSongs() {
	return &this->songs;
}

void SongCollection::addPlaylist(Playlist* playlist) {
	if (playlists.contains(playlist)) {
		return;
	}
	playlists.add(playlist);
}

void SongCollection::deletePlaylist(Playlist* playlist) {
	playlists.remove(playlist);
}

void SongCollection::listPlaylists() {
	if (playlists.getSize() == 0) {
		cout << "No playlist found." << endl;
		return;
	}
	NodeType<Playlist>* current = playlists.getHead();
	int i = 1;
	cout << "Listing " << playlists.getSize() << " playlists" << endl;
	while (current != NULL) {
		cout << i++ << ". " << current->data->getName() << " - ";
		NodeType<Song>* songs = current->data->getSongs()->getHead();
		if (songs != NULL) {
			while (songs != NULL) {
				cout << songs->data->getTitle();
				songs = songs->node;
				if (songs != NULL) {
					cout << ", ";
				}
			}
		} else {
			cout << "(Empty)";
		}
		cout << endl;
		current = current->node;
	}
}

void SongCollection::listPlaylistsContainSong(Song* song) {
	if (playlists.getSize() == 0) {
		cout << "No playlist found. Create a playlist before for playlists contain song." << endl;
		return;
	}
	NodeType<Playlist>* current = playlists.getHead();
	int i = 1;
	bool found = false;
	cout << "Playlists contain song: " << song->getTitle() << endl;
	while (current != NULL) {
		NodeType<Song>* songs = current->data->getSongs()->getHead();
		while (songs != NULL) {
			if (songs->data == song) {
				cout << i++ << ". " << current->data->getName() << endl;
				found = true;
			}
			songs = songs->node;
		}
		current = current->node;
	}
	if (!found) {
		cout << "This song does not exist in any playlist." << endl;
	}
}

Playlist* SongCollection::getPlaylist(string playlist) {
	return playlists.get("playlist:" + playlist);
}

LinkedList<Playlist>* SongCollection::getPlaylists() {
	return &this->playlists;
}
#endif