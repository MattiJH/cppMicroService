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
#include "stdafx.h"
#include "microsvc_controller.hpp"
#include <string>
#include <vector>

using namespace web;
using namespace http;

void MicroserviceController::initRestOpHandlers() {
	_listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
	_listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
	_listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
	_listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
	_listener.support(methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
}

void MicroserviceController::handleGet(http_request message) 
{
	auto path = requestPath(message);
	if (!path.empty()) {
		if (path[0] == U("service") && path[1] == U("test")) 
		{
			auto response = json::value::object();
			response[U("version")] = json::value::string(U("0.1.1"));
			response[U("status")] = json::value::string(U("ready!"));
			response[U("response")] = json::value::string(U("Hello World!"));
			message.reply(status_codes::OK, response);

		}
		else if (path[0] == U("locations") && path[1] == U("all")) 
		{
			std::vector<Location> responseVec = dao.getAllFromDB();
			json::value response;
			int i = 0;
			
			for (Location& l : responseVec) {
				
				auto responsePart = json::value::object();
				responsePart[U("Location_id")] = json::value::number(l.id);
				responsePart[U("Location_name")] = json::value::string(utility::conversions::to_string_t(l.name));
				responsePart[U("Location_address")] = json::value::string(utility::conversions::to_string_t(l.address));
				responsePart[U("Location_city")] = json::value::string(utility::conversions::to_string_t(l.city));
				responsePart[U("Location_zip")] = json::value::number(l.zip);
				responsePart[U("Location_country")] = json::value::string(utility::conversions::to_string_t(l.country));

				response[i] = responsePart;
				i++;
			}
			message.reply(status_codes::OK, response);



		}
		else {
			message.reply(status_codes::NotFound);
		}
	}
	else 
	{
		message.reply(status_codes::NotFound);
	}
}
void MicroserviceController::handlePatch(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::PATCH));
}

void MicroserviceController::handlePut(http_request message) {

	message.reply(status_codes::NotImplemented, responseNotImpl(methods::PUT));
}

void MicroserviceController::handlePost(http_request message) {
	auto path = requestPath(message);
	if (!path.empty())
	{
		if (path[0] == U("locations") && path[1] == U("add"))
		{
			message.extract_json().then([=](json::value request) {
				try
				{
					Location newLocation;

					newLocation.name = toString(request[U("Location_name")].as_string().c_str());
					newLocation.address = toString(request[U("Location_address")].as_string().c_str());
					newLocation.city = toString(request[U("Location_city")].as_string().c_str());
					newLocation.zip = request[U("Location_zip")].as_integer();
					newLocation.country = toString(request[U("Location_country")].as_string().c_str());

					if (dao.insertIntoDB(newLocation)) {
						message.reply(status_codes::OK);
					}
					else
					{
						message.reply(status_codes::InternalError);
					}
				}
				catch (const json::json_exception & e)
				{
					std::cout << "exception: " << e.what() << std::endl;
					auto response = json::value::object();
					response[U("error")] = json::value::string(U("Invalid JSON"));
					message.reply(status_codes::BadRequest, response);
				}
				catch (const std::exception ex)
				{
					message.reply(status_codes::BadRequest);
				}
				catch (...)
				{
					message.reply(status_codes::BadRequest);
				}

			});

		}
	}
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
}

void MicroserviceController::handleDelete(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
}

void MicroserviceController::handleHead(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void MicroserviceController::handleOptions(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void MicroserviceController::handleTrace(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void MicroserviceController::handleConnect(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void MicroserviceController::handleMerge(http_request message) {
	message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
}

json::value MicroserviceController::responseNotImpl(const http::method &method) {

	using namespace json;

	auto response = value::object();
	response[U("serviceName")] = value::string(U("Mircoservice Sample"));
	response[U("http_method")] = value::string(method);

	auto subResponse = value::object();
	subResponse[U("field1")] = value::string(U("some string"));
	subResponse[U("field2")] = value::number(123123);
	
	response[U("sub")] = subResponse;

	return response;
}
std::string MicroserviceController::toString(const wchar_t* wc) {
	std::wstring ws(wc);
	std::string s(ws.begin(), ws.end());
	return s;
}