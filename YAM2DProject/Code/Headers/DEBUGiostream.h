#pragma once

#include <string>

void msgstream(std::string msg, bool endline = true);
void msgstream(std::string msg, std::string msg2, bool endline = true);
void msgstream(float value, bool endline = true);
void msgstream(float value, float value2, bool endline = true);

void newline();
