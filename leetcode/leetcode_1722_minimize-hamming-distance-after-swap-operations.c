#define MAX_N 100005
#define MAX_VAL 100005

int minimumHammingDistance(int* source, int sourceSize, int* target,
                           int targetSize, int** allowedSwaps,
                           int allowedSwapsSize, int* allowedSwapsColSize) {
    int n = sourceSize;

    int parent[MAX_N], rank_[MAX_N];
    for (int i = 0; i < n; i++) {
        parent[i] = i;
        rank_[i] = 0;
    }

    for (int i = 0; i < allowedSwapsSize; i++) {
        int a = allowedSwaps[i][0], b = allowedSwaps[i][1];

        int ra = a, rb = b;
        while (parent[ra] != ra)
            ra = parent[ra];
        while (parent[rb] != rb)
            rb = parent[rb];

        while (parent[a] != a) {
            int next = parent[a];
            parent[a] = ra;
            a = next;
        }
        while (parent[b] != b) {
            int next = parent[b];
            parent[b] = rb;
            b = next;
        }

        if (ra != rb) {
            if (rank_[ra] < rank_[rb]) {
                parent[ra] = rb;
            } else if (rank_[ra] > rank_[rb]) {
                parent[rb] = ra;
            } else {
                parent[rb] = ra;
                rank_[ra]++;
            }
        }
    }

    for (int i = 0; i < n; i++) {
        int root = i;
        while (parent[root] != root)
            root = parent[root];
        int r = root;
        int x = i;
        while (parent[x] != x) {
            int next = parent[x];
            parent[x] = r;
            x = next;
        }
    }

    typedef struct Node {
        int idx;
        struct Node* next;
    } Node;

    Node* heads[MAX_N] = {NULL};
    Node* tails[MAX_N] = {NULL};

    for (int i = 0; i < n; i++) {
        int root = parent[i];
        Node* node = (Node*)malloc(sizeof(Node));
        node->idx = i;
        node->next = NULL;

        if (heads[root] == NULL) {
            heads[root] = tails[root] = node;
        } else {
            tails[root]->next = node;
            tails[root] = node;
        }
    }

    int freq[MAX_VAL] = {0};
    int match = 0;

    for (int i = 0; i < n; i++) {
        if (heads[i] == NULL)
            continue;

        for (Node* p = heads[i]; p; p = p->next) {
            freq[source[p->idx]]++;
        }

        for (Node* p = heads[i]; p; p = p->next) {
            if (freq[target[p->idx]] > 0) {
                freq[target[p->idx]]--;
                match++;
            }
        }

        for (Node* p = heads[i]; p; p = p->next) {
            freq[source[p->idx]] = 0;
        }

        Node* p = heads[i];
        while (p) {
            Node* next = p->next;
            free(p);
            p = next;
        }
    }

    return n - match;
}