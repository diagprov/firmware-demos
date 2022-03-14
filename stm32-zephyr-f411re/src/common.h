
#ifndef COMMON_H
#define COMMON_H


#define DISPLAY_DEV_NAME DT_LABEL(DT_INST(0, ilitek_ili9340))

#ifdef CONFIG_ARCH_POSIX
#include "posix_board_if.h"
#endif

#ifdef CONFIG_ARCH_POSIX
#define RETURN_FROM_MAIN(exit_code) posix_exit_main(exit_code)
#else
#define RETURN_FROM_MAIN(exit_code) return
#endif


#endif
