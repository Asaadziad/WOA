#ifndef PARSER_H
#define PARSER_H


typedef struct json_obj* JSONObject;

/*
 * will parse a given Json file
 * @return: an array of Json objects
 * */
JSONObject* parse(const char* file_path);


#endif
