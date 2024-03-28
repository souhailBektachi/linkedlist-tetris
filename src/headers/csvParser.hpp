#pragma once
#include <iostream>
#include <stdlib.h>
#include <string.h>
#include "csts.hpp"
void parseCsv(const char *pathname, int mapkeys[]);
FILE *checkFile(const char *pathname);