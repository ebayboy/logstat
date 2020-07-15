#!/bin/bash


#build hiredis
function build_hiredis()
{
	ls src/libs/*.tar.bz2 | xargs -i tar xf {} -C src/libs/
	make -C src/libs/hiredis
	cp src/libs/hiredis/libhiredis.a src/libs/
}


function build_libevent()
{
	BUILD_DIR=/tmp/libevent_build
	cd src/libs/libevent 
	mkdir -p $BUILD_DIR
	./configure --prefix=$BUILD_DIR && make -j4 && make install || exit 1
	cd - 
	cp $BUILD_DIR/lib/libevent.a src/libs
	cp $BUILD_DIR/include/* src/include/
}


build_hiredis

build_libevent

make -j4

