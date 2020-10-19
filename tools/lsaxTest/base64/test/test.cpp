/****************************************************************************
@file:test-util.cpp 
@author:ebayboy@163.com 
@date:2020-08-20 16:22 
@version: 1.0  
@description: cpp file 
@Copyright (c)  all right reserved 
**************************************************************************/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>

#include <gtest/gtest.h>

#include "base64.h"

TEST(testCase, test0)
{
	unsigned char *encode = (unsigned char *)"foobar";
	unsigned int encodelen = strlen((char *)encode);
    char *decode = (char *)"Zm9vYmFy";
	unsigned int decodelen = strlen(decode);

	char *encode_out = NULL;
	unsigned char *decode_out = NULL;

	encode_out = (char *)malloc(BASE64_ENCODE_OUT_SIZE(encodelen));
	decode_out = (unsigned char *)malloc(BASE64_DECODE_OUT_SIZE(decodelen));

	ASSERT_TRUE(encode_out);
	ASSERT_TRUE(decode_out);

	ASSERT_EQ(base64_encode(encode, encodelen, encode_out), decodelen);
	ASSERT_EQ(memcmp(encode_out, decode, decodelen), 0);

	ASSERT_EQ(base64_decode(decode, decodelen, decode_out), encodelen);
	ASSERT_EQ(memcmp(decode_out, encode, encodelen),0);

	free(encode_out);
	free(decode_out);
}


