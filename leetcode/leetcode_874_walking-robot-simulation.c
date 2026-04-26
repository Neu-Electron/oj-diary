typedef struct {
    long long key;
    UT_hash_handle hh;
} ObsMap;

int robotSim(int* commands, int commandsSize, int** obstacles, int obstaclesSize, int* obstaclesColSize) {
    int dx[4] = {0, 1, 0, -1};
    int dy[4] = {1, 0, -1, 0};
    
    int dir = 0, x = 0, y = 0, maxDist = 0;
    const int OFFSET = 30000;
    
    ObsMap *obsMap = NULL, *entry, *tmp;
    for (int i = 0; i < obstaclesSize; i++) {
        entry = (ObsMap*)malloc(sizeof(ObsMap));
        entry->key = ((long long)(obstacles[i][0] + OFFSET) << 16) 
                   | (obstacles[i][1] + OFFSET);
        HASH_ADD_KEYPTR(hh, obsMap, &entry->key, sizeof(long long), entry);
    }
    
    for (int i = 0; i < commandsSize; i++) {
        if (commands[i] == -2) {
            dir = (dir + 3) % 4;
        } else if (commands[i] == -1) {
            dir = (dir + 1) % 4; 
        } else {
            for (int s = 0; s < commands[i]; s++) {
                int nx = x + dx[dir];
                int ny = y + dy[dir];
                long long key = ((long long)(nx + OFFSET) << 16) | (ny + OFFSET);
                
                HASH_FIND(hh, obsMap, &key, sizeof(long long), entry);
                if (entry) break;
                
                x = nx;
                y = ny;
                int dist = x * x + y * y;
                if (dist > maxDist) maxDist = dist;
            }
        }
    }
    
    HASH_ITER(hh, obsMap, entry, tmp) {
        HASH_DEL(obsMap, entry);
        free(entry);
    }
    
    return maxDist;
}