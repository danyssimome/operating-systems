#ifndef CHANNELS_CONSTANTS_H
#define CHANNELS_CONSTANTS_H

char const PATHNAME[] = "./server.cpp";
const int PROJ_ID = 65;

//структура сообщения
struct msgBuffer {
    long type;
    char text[512];
};

const long REQUEST_TYPE = 1;
const long RESPONSE_TYPE = 2;

char const STR_ALLOW[] = "Существуют права на запись";
char const STR_DENY[] = "Права установлены";
char const STR_NOTFOUND[] = "Папка не найдена";
const char OFF[] = "off";

#endif
