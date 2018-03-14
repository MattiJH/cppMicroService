//
//  Created by Ivan Mejia on 12/24/16.
//
// MIT License
//
// Copyright (c) 2016 ivmeroLabs.
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:

// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.

// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//

// main.cpp : Defines the entry point for the console application.
//

#include "stdafx.h"
#include <Windows.h>
#include "usr_interrupt_handler.hpp"
//#include "runtime_utils.hpp" not supported on windows
#include "microsvc_controller.hpp"
#include <clocale>

using namespace web;
using namespace cfx;

int main(int argc, const char * argv[]) {
	std::setlocale(LC_ALL, "");
	InterruptHandler::hookSIGINT();

	MicroserviceController server;
	server.setEndpoint(U("http://host_auto_ip4:6502/api"));

	try {
		// wait for server initialization...
		server.accept().wait();
		std::wcout << U("DIY server now listening for requests at: ") << server.endpoint() << std::endl;

		cfx::InterruptHandler::waitForUserInterrupt();

		server.shutdown().wait();
		Sleep(2000);
	}
	catch (std::exception & e) {
		std::cerr << "something wrong happened! :(" << std::endl;
		std::cerr << e.what() << std::endl;
	}

	catch (...) {
		//RuntimeUtils::printStackTrace();
		// TODO: use boost strack trace helper here
		std::cerr << "should print stack trace here..." << std::endl;
	}

	return 0;
}
