#include <regex.h>
#include <stdbool.h>

bool checkRecord(char *s) {
    regex_t regex;
    int reti;
    const char *pattern = "A.*A|LLL";
    reti = regcomp(&regex, pattern, REG_EXTENDED);
    if (reti) {
        return false;
    }
    reti = regexec(&regex, s, 0, NULL, 0);
    bool isMatch = (reti == 0);
    regfree(&regex);
    return !isMatch;
}