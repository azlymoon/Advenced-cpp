#include "util.h"
int max(int a, int b) {
	int m = (a > b) ? a : b;
	logDebug('m');
	return m;
}
