#ifndef FILEUTIL_HEADER
#define FILEUTIL_HEADER

#include "SongCollection.h"

using namespace std;

class FileUtil {
public:
    void loadFiles(SongCollection& songCollection);
    void saveFiles(SongCollection& songCollection);
};
#endif