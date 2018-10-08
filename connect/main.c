#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "user_config.h"

const char ssid[32] = "my_home_ssid";
const char password[32] = "my_home_password";

struct station_config stationConf;

wifi_set_opmode( STATION_MODE );
os_memcpy(&stationConf.ssid, ssid, 32);
os_memcpy(&stationConf.password, password, 32);
wifi_station_set_config(&stationConf);
wifi_station_connect();