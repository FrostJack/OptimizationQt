#pragma once
#include <string>
#include <exception>
class Exception : public std::exception {
	std::string msg;
public:
    Exception(const std::string& _msg) : msg(_msg) {}
	virtual const char* what() const noexcept override {
		return msg.c_str();
	}
};
