/**
 * Definition for singly-linked list.
 * struct ListNode {
 *     int val;
 *     struct ListNode *next;
 * };
 */

struct hashTable {
    int key;
    UT_hash_handle hh;
};

struct ListNode* modifiedList(int* nums, int numsSize, struct ListNode* head) {

    if (head == NULL) {
        return NULL;
    }

    struct hashTable* hash = NULL;
    struct hashTable* tmp = NULL;

    for (int i = 0; i < numsSize; i++) {
        HASH_FIND_INT(hash, &nums[i], tmp);
        if (tmp == NULL) {
            tmp = (struct hashTable*)malloc(sizeof(struct hashTable));
            tmp->key = nums[i];
            HASH_ADD_INT(hash, key, tmp);
        }
    }

    while (head != NULL) {
        HASH_FIND_INT(hash, &head->val, tmp);
        if (tmp != NULL) {
            struct ListNode* toDelete = head;
            head = head->next;
            free(toDelete);
        } else {
            break;
        }
    }

    if (head == NULL) {
        HASH_CLEAR(hh, hash);
        return NULL;
    }

    struct ListNode* prev = head;
    struct ListNode* curr = head->next;

    while (curr != NULL) {
        HASH_FIND_INT(hash, &curr->val, tmp);
        if (tmp != NULL) {
            prev->next = curr->next;
            free(curr);
            curr = prev->next;
        } else {
            prev = curr;
            curr = curr->next;
        }
    }

    HASH_CLEAR(hh, hash);

    return head;
}