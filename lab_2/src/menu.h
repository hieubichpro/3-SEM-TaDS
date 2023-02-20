#ifndef MENU_H

#define MENU_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "file_work.h"
#include "print_info.h"
#include "sorts.h"
#include "struct.h"

#define OK 0
#define ERR_OPTION_TYPE -1
#define ERR_OPTION_VALUE -2
#define ERR_OPEN_FILE -3
#define ERR_NO_SUCH_FILE -42

#define MAX_FLATS 1000

int option_menu(void);

#endif
