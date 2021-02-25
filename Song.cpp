#ifndef SONG_CPP
#define SONG_CPP

#include <iostream>

using namespace std;

class Song {
private:
	string title;
	string singer;
	int duration; // in seconds
public:
	Song(string title, string singer, int duration) {
		this->title = title;
		this->singer = singer;
		this->duration = duration;
	}

	string getTitle() {
		return this->title;
	}

	string getSinger() {
		return this->singer;
	}

	int getDuration() {
		return this->duration;
	}

	string getIdentifier() {
		return "song:" + this->title;
	}
};
#endif