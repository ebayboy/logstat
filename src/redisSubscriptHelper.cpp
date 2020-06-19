
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <signal.h>
#include <iostream>
#include <string>

#include "hiredis/hiredis.h"
#include "hiredis/async.h"
#include "hiredis/adapters/libevent.h"

#include "redisSubscriptHelper.h"

using namespace std;

static void authCallback(redisAsyncContext *c, void *r, void *priv) {
    redisReply *reply = (redisReply*)r;

    cout << "auth reply->type:" << reply->type << "reply->str:" << reply->str << endl;

    if (reply == NULL) {
        if (c->errstr) {
            printf("errstr: %s\n", c->errstr);
        }
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

static void subCallback(redisAsyncContext *c, void *r, void *priv) {
    redisReply *reply = (redisReply*)r;
    if (reply == NULL) {
        printf("Error: %s\n", c->errstr);
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

static void connectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Connected...\n");
}

static void disconnectCallback(const redisAsyncContext *c, int status) {
    if (status != REDIS_OK) {
        printf("Error: %s\n", c->errstr);
        return;
    }
    printf("Disconnected...\n");
}

int reidsSubInit(char *addr, int port, char *auth, char *sub) 
{
    struct event_base *base = event_base_new();
    redisAsyncContext *c = redisAsyncConnect(addr, port);
    char cmd[BUFSIZ] = {0};

    if (c->err) {
        /* Let *c leak for now... */
        printf("Error: %s\n", c->errstr);
        return 1;
    }

    redisLibeventAttach(c,base);
    redisAsyncSetConnectCallback(c,connectCallback);
    redisAsyncSetDisconnectCallback(c,disconnectCallback);

    //AUTH
    if (auth && strlen(auth) > 0) {
        snprintf(cmd, sizeof(cmd), "AUTH %s", auth);
        redisAsyncCommand(c, authCallback, (char*)"auth", cmd);
    }

    //SUB
    if (sub && strlen(sub) > 0) {
        snprintf(cmd, sizeof(cmd), "SUBSCRIBE %s", sub);
        redisAsyncCommand(c, subCallback, (char*)"sub", cmd);
    }

    event_base_dispatch(base);

    return 0;
}
