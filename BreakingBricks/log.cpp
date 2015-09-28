/*
file: log.cpp
*/

#include "log.h"

const char* htmlHead =
"<!-- (c) Chr. Jaeger 2011 -->\n"
"<html>\n"
"   <head>\n"
"      <title>Logfile</title>\n"
"   </head>\n"
"   <body>\n"
"      <div align=\"center\">\n"
"         <h1>Logfile</h1>\n"
"         <table border=\"1\">\n"
"         <tr><td>Type</td><td>Message";

const char* htmlTail =
"</td></tr>\n"
"         </table>\n"
"      </div>\n"
"   </body>\n"
"</html>\n";

const char* Log::endl = "<br />";

Log::Log(void) : _file("logfile.html") {
	_file << htmlHead;
}

Log::~Log(void) {
	_file << htmlTail;
	_file.close();
}

std::ofstream& Log::MessageType(const std::string& label,
								const std::string& htmlColor) {
	_file << "</td></tr>\n"
		<< "         "
		<< "<tr><td><font color=\"" 
		<< htmlColor 
		<< "\"><b>"
		<< label 
		<< "</b></font></td><td>";
	return _file;
}

std::ofstream& Log::Info(void) {
	return MessageType("Info", "green");
}

std::ofstream& Log::Warning(void) {
	return MessageType("Warning", "orange");
}

std::ofstream& Log::Error(void) {
	return MessageType("Error", "red");
}