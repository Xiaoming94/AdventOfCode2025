#define PROJECT_NAME "day3"

#include <aoclibs.h>

#include "solution.h"
int main()
{
  aoclibs::aocMain(&solution::findTotalMaxJoltage, &solution::findTotalMaxJoltageTwelveBats);
}
