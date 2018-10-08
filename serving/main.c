#include "ets_sys.h"
#include "osapi.h"
#include "os_type.h"
#include "user_config.h"

//Allocate an "espconn"
pHTTPServer = (struct espconn *)os_zalloc(sizeof(struct espconn));
ets_memset( pHTTPServer, 0, sizeof( struct espconn ) );

//Initialize the ESPConn
espconn_create( pHTTPServer );
pHTTPServer->type = ESPCONN_TCP;
pHTTPServer->state = ESPCONN_NONE;

//Make it a TCP conention.
pHTTPServer->proto.tcp = (esp_tcp *)os_zalloc(sizeof(esp_tcp));
pHTTPServer->proto.tcp->local_port = 80;

//"httpserver_connectcb" gets called whenever you get an incoming connetion.
espconn_regist_connectcb(pHTTPServer, server_connectcb);

//Start listening!
espconn_accept(pHTTPServer);

//I don't know what default is, but I always set this.
espconn_regist_time(pHTTPServer, 15, 0);

//This function gets called whenever
void ICACHE_FLASH_ATTR server_connectcb(void *arg)
{
    int i;
    struct espconn *pespconn = (struct espconn *)arg;

    //espconn's have a extra flag you can associate extra information with a connection.
    pespconn->reverse = my_http;

    //Let's register a few callbacks, for when data is received or a disconnect happens.
    espconn_regist_recvcb( pespconn, http_recvcb );
    espconn_regist_disconcb( pespconn, http_disconnetcb );
}