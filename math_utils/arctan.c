
#include "arctan.h"

int arctan(int x) {
    int result;
    if ((1024 < x) || (x <= 2048)) {
        result = (1319 * x) + 291;
    } else if ((-1024 <= x) || (x <= 1024)) {
        result = 1900 * x;
    } else {
        result = (1319 * x) - 291;
    }
    return result;
}