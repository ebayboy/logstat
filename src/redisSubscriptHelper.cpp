
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <string>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"


using namespace std;

void authCallback(redisAsyncContext *c, void *r, void *priv) {
    redisReply *reply = (redisReply*)r;

    cout << "auth reply->type:" << reply->type << "reply->str:" << reply->str << endl;

    if (reply == NULL) {
        return;
    }

    if (reply->type == REDIS_REPLY_STATUS) {
        if (strcasecmp(reply->str, "OK") == 0) {
            cout << (char *)priv << " : " << reply->str << endl; 
        }
    } else {
        //REDIS_REPLY_ERROR
        cerr << "Auth failed!" << reply->str << endl;
    }
}

void subCallback(redisAsyncContext *c, void *r, void *priv) {
    redisReply *reply = (redisReply*)r;
    if (reply == NULL) {
        return;
    }

    if ( reply->type == REDIS_REPLY_ARRAY && reply->elements == 3 ) {
        if ( strcmp( reply->element[0]->str, "subscribe" ) != 0 ) {
            printf( "Received[%s] channel %s: %s\n",
                    (char*)priv,
                    reply->element[1]->str,
                    reply->element[2]->str );
        }
    }
}

void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}

int reidsSubInit() 
{
    struct event_base *base = event_base_new();
    redisAsyncContext *c = redisAsyncConnect("127.0.0.1", 6379);
    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisLibeventAttach(c,base);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);

    //AUTH
    redisAsyncCommand(c, authCallback, (char*) "auth", "AUTH 123456");

    //SUB
    redisAsyncCommand(c, subCallback, (char*) "sub", "SUBSCRIBE channel01");

    event_base_dispatch(base);

    return 0;
}
