#define TOTAL_MONEY(n) (((7 * ((n)/7) * (((n)/7) + 1)) / 2 + 21 * ((n)/7)) + \
                        (((n)%7) * (((n)/7) + 1) + (((n)%7) * (((n)%7) - 1)) / 2))
int totalMoney(int n) {
     return TOTAL_MONEY(n);
}