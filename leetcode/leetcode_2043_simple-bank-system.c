typedef struct {
    long long* balance;
    int accountCount;
} Bank;

Bank* bankCreate(long long* balance, int balanceSize) {
    Bank* obj = (Bank*)malloc(sizeof(Bank));
    obj->accountCount = balanceSize;
    obj->balance = (long long*)malloc(sizeof(long long) * balanceSize);

    for (int i = 0; i < balanceSize; i++) {
        obj->balance[i] = balance[i];
    }
    return obj;
}

bool bankTransfer(Bank* obj, int account1, int account2, long long money) {

    if (account1 < 1 || account1 > obj->accountCount || account2 < 1 ||
        account2 > obj->accountCount) {
        return false;
    }

    if (obj->balance[account1 - 1] < money) {
        return false;
    }

    obj->balance[account1 - 1] -= money;
    obj->balance[account2 - 1] += money;
    return true;
}

bool bankDeposit(Bank* obj, int account, long long money) {

    if (account < 1 || account > obj->accountCount) {
        return false;
    }

    obj->balance[account - 1] += money;
    return true;
}

bool bankWithdraw(Bank* obj, int account, long long money) {

    if (account < 1 || account > obj->accountCount) {
        return false;
    }

    if (obj->balance[account - 1] < money) {
        return false;
    }

    obj->balance[account - 1] -= money;
    return true;
}

void bankFree(Bank* obj) {
    if (obj != NULL) {
        free(obj->balance);
        free(obj);
    }
}