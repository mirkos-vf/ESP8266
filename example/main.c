#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "user_config.h"


void sdk_init_done_cb(void) { 
	/* your application code */
}

/*
	entry point to a program
*/
void ICACHE_FLASH_ATTR
user_init() {
	system_init_done_cb(sdk_init_done_cb);
}