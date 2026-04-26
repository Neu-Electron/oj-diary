typedef struct {
    int* parent;
    int* rank;
} DSU;

DSU* dsu_create(int n) {
    DSU* dsu = (DSU*)malloc(sizeof(DSU));
    dsu->parent = (int*)malloc(n * sizeof(int));
    dsu->rank = (int*)malloc(n * sizeof(int));
    for (int i = 0; i < n; i++) {
        dsu->parent[i] = i;
        dsu->rank[i] = 0;
    }
    return dsu;
}

int dsu_find(DSU* dsu, int x) {
    if (dsu->parent[x] != x) {
        dsu->parent[x] = dsu_find(dsu, dsu->parent[x]);
    }
    return dsu->parent[x];
}

int dsu_unite(DSU* dsu, int a, int b) {
    int ra = dsu_find(dsu, a);
    int rb = dsu_find(dsu, b);
    if (ra == rb)
        return 0;

    if (dsu->rank[ra] < dsu->rank[rb]) {
        dsu->parent[ra] = rb;
    } else if (dsu->rank[ra] > dsu->rank[rb]) {
        dsu->parent[rb] = ra;
    } else {
        dsu->parent[rb] = ra;
        dsu->rank[ra]++;
    }
    return 1;
}

void dsu_free(DSU* dsu) {
    free(dsu->parent);
    free(dsu->rank);
    free(dsu);
}

int isFeasible(int n, int** edges, int edgesSize, int k, int X) {
    DSU* dsu = dsu_create(n);

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int s = edges[i][2];
        int must = edges[i][3];

        if (must == 1) {
            if (s < X) {
                dsu_free(dsu);
                return 0;
            }
            dsu_unite(dsu, u, v);
        }
    }

    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int s = edges[i][2];
        int must = edges[i][3];

        if (must == 0 && s >= X) {
            dsu_unite(dsu, u, v);
        }
    }

    int used = 0;
    for (int i = 0; i < edgesSize; i++) {
        int u = edges[i][0];
        int v = edges[i][1];
        int s = edges[i][2];
        int must = edges[i][3];

        if (must == 0 && s < X && 2 * s >= X) {
            if (dsu_unite(dsu, u, v)) {
                used++;
            }
        }
    }

    int root = dsu_find(dsu, 0);
    int connected = 1;
    for (int i = 1; i < n; i++) {
        if (dsu_find(dsu, i) != root) {
            connected = 0;
            break;
        }
    }

    dsu_free(dsu);

    return connected && used <= k;
}

int maxStability(int n, int** edges, int edgesSize, int* edgesColSize, int k) {

    DSU* dsu = dsu_create(n);

    int minMustStrength = INT_MAX;
    for (int i = 0; i < edgesSize; i++) {
        if (edges[i][3] == 1) {
            int u = edges[i][0];
            int v = edges[i][1];
            int s = edges[i][2];

            if (!dsu_unite(dsu, u, v)) {
                dsu_free(dsu);
                return -1;
            }
            if (s < minMustStrength) {
                minMustStrength = s;
            }
        }
    }
    dsu_free(dsu);

    int low = 1;
    int high = 200000;
    int ans = -1;

    while (low <= high) {
        int mid = low + (high - low) / 2;

        if (isFeasible(n, edges, edgesSize, k, mid)) {
            ans = mid;
            low = mid + 1;
        } else {
            high = mid - 1;
        }
    }

    return ans;
}