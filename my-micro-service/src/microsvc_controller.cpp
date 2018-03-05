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

void MicroserviceController::initRestOpHandlers() 
{
	_listener.support(methods::GET, std::bind(&MicroserviceController::handleGet, this, std::placeholders::_1));
	_listener.support(methods::PUT, std::bind(&MicroserviceController::handlePut, this, std::placeholders::_1));
	_listener.support(methods::POST, std::bind(&MicroserviceController::handlePost, this, std::placeholders::_1));
	_listener.support(methods::DEL, std::bind(&MicroserviceController::handleDelete, this, std::placeholders::_1));
	_listener.support(methods::PATCH, std::bind(&MicroserviceController::handlePatch, this, std::placeholders::_1));
	_listener.support(methods::OPTIONS, std::bind(&MicroserviceController::handleOptions, this, std::placeholders::_1));
	_listener.support(methods::CONNECT, std::bind(&MicroserviceController::handleConnect, this, std::placeholders::_1));
	_listener.support(methods::HEAD, std::bind(&MicroserviceController::handleHead, this, std::placeholders::_1));
	_listener.support(methods::TRCE, std::bind(&MicroserviceController::handleTrace, this, std::placeholders::_1));
}

void MicroserviceController::handleGet(http_request message) 
{
	auto path = requestPath(message);
	if (!path.empty()) 
	{
		if (path[0] == U("service") && path[1] == U("test")) 
		{
			auto responseBody = json::value::object();
			responseBody[U("version")] = json::value::string(U("0.1.1"));
			responseBody[U("status")] = json::value::string(U("ready!"));
			responseBody[U("response")] = json::value::string(U("Hello World!"));

			http_response response(status_codes::OK);
			addHeaders(response);
			response.set_body(responseBody);

			message.reply(response);

		}
		else if (path[0] == U("locations") && path[1] == U("all")) 
		{
			std::vector<Location> responseVec = dao.getAllFromDB();
			json::value responseBody;
			
			int i = 0;
			
			for (Location& l : responseVec) 
			{
				auto responseBodyPart = json::value::object();
				responseBodyPart[U("Location_id")] = json::value::number(l.id);
				responseBodyPart[U("Location_name")] = json::value::string(utility::conversions::to_string_t(l.name));
				responseBodyPart[U("Location_address")] = json::value::string(utility::conversions::to_string_t(l.address));
				responseBodyPart[U("Location_city")] = json::value::string(utility::conversions::to_string_t(l.city));
				responseBodyPart[U("Location_zip")] = json::value::number(l.zip);
				responseBodyPart[U("Location_country")] = json::value::string(utility::conversions::to_string_t(l.country));

				responseBody[i] = responseBodyPart;
				i++;
			}

			http_response response(status_codes::OK);
			addHeaders(response);
			response.set_body(responseBody);

			message.reply(response);



		}
		
		else 
		{
			http_response response(status_codes::NotFound);
			addHeaders(response);

			message.reply(response);
		}
	}
	else 
	{
		http_response response(status_codes::NotFound);
		addHeaders(response);
	
		message.reply(response);
	
	}
}
void MicroserviceController::handlePatch(http_request message) 
{
	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::PATCH));
	message.reply(response);
}

void MicroserviceController::handlePut(http_request message) 
{

	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::PUT));
	message.reply(response);
}

void MicroserviceController::handlePost(http_request message) 
{
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::POST));
	auto path = requestPath(message);
	if (!path.empty())
	{
		if (path[0] == U("locations") && path[1] == U("add"))
		{
			
				message.extract_json().then([=](json::value request)
				{
					try
					{
						Location newLocation;

						if (request.has_field(U("Location_name")))
							newLocation.name = toString(request[U("Location_name")].as_string().c_str());

						if (request.has_field(U("Location_address")))
							newLocation.address = toString(request[U("Location_address")].as_string().c_str());

						if (request.has_field(U("Location_city")))
							newLocation.city = toString(request[U("Location_city")].as_string().c_str());

						if (request.has_field(U("Location_zip")))
							newLocation.zip = request[U("Location_zip")].as_integer();

						if (request.has_field(U("Location_country")))
							newLocation.country = toString(request[U("Location_country")].as_string().c_str());

						if (dao.insertIntoDB(newLocation)) {

							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Adding item successful"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						
						}
						else
						{
							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Addint item failed, please check your parameters"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						}
					}
					catch (const json::json_exception & e)
					{
						std::cout << "exception: " << e.what() << std::endl;

						auto responseBody = json::value::object();
						responseBody[U("error")] = json::value::string(U("Invalid JSON"));

						http_response response(status_codes::BadRequest);
						addHeaders(response);
						response.set_body(responseBody);

						message.reply(response);
					}
					catch (const std::exception ex)
					{
						http_response response(status_codes::BadRequest);
						addHeaders(response);
						message.reply(response);
					}
					catch (...)
					{
						http_response response(status_codes::BadRequest);
						addHeaders(response);
						message.reply(response);
					}

				});
			
		
		}
		else if (path[0] == U("locations") && path[1] == U("update"))
		{
			message.extract_json().then([=](json::value requestBody) {
				try
				{
					Location updateLocation;
					if (requestBody.has_field(U("Location_id"))) {
						updateLocation.id = requestBody[U("Location_id")].as_integer();


						if (requestBody.has_field(U("Location_name")))
							updateLocation.name = toString(requestBody[U("Location_name")].as_string().c_str());

						if (requestBody.has_field(U("Location_address")))
							updateLocation.address = toString(requestBody[U("Location_address")].as_string().c_str());

						if (requestBody.has_field(U("Location_city")))
							updateLocation.city = toString(requestBody[U("Location_city")].as_string().c_str());

						if (requestBody.has_field(U("Location_zip")))
							updateLocation.zip = requestBody[U("Location_zip")].as_integer();

						if (requestBody.has_field(U("Location_country")))
							updateLocation.country = toString(requestBody[U("Location_country")].as_string().c_str());

						if (dao.updateDB(updateLocation)) {
							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Update successful"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						}
						else
						{
							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Update failed"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						}
					}
					else
					{

						auto responseBody = json::value::object();
						responseBody[U("Results")] = json::value::string(U("Update failed, please check your parameters"));

						http_response response(status_codes::OK);
						addHeaders(response);
						response.set_body(responseBody);

						message.reply(response);
					}
				}
				catch (const json::json_exception & e)
				{
					std::cout << "exception: " << e.what() << std::endl;
					auto responseBody = json::value::object();
					responseBody[U("error")] = json::value::string(U("Invalid JSON"));

					http_response response(status_codes::BadRequest);
					addHeaders(response);
					response.set_body(responseBody);

					message.reply(response);
				}
				catch (const std::exception ex)
				{

					http_response response(status_codes::BadRequest);
					addHeaders(response);
			
					message.reply(response);
				}
				catch (...)
				{
					http_response response(status_codes::BadRequest);
					addHeaders(response);

					message.reply(response);
				}

			});

		}
		else if (path[0] == U("locations") && path[1] == U("search")) {

			
			
			auto searchDB = message.extract_json().then([=](json::value requestBody)
			{
				try
				{
					Location searchLocation;
					if (requestBody.has_field(U("Location_id")))
						searchLocation.id = requestBody[U("Location_id")].as_integer();

					if (requestBody.has_field(U("Location_name")))
						searchLocation.name = toString(requestBody[U("Location_name")].as_string().c_str());

					if (requestBody.has_field(U("Location_address")))
						searchLocation.address = toString(requestBody[U("Location_address")].as_string().c_str());

					if (requestBody.has_field(U("Location_city")))
						searchLocation.city = toString(requestBody[U("Location_city")].as_string().c_str());

					if (requestBody.has_field(U("Location_zip")))
						searchLocation.zip = requestBody[U("Location_zip")].as_integer();

					if (requestBody.has_field(U("Location_country")))
						searchLocation.country = toString(requestBody[U("Location_country")].as_string().c_str());

					std::vector<Location> responseVec = dao.getByValue(searchLocation);
					json::value responseBody;
					int i = 0;

					for (Location& l : responseVec)
					{
						auto responseBodyPart = json::value::object();
						responseBodyPart[U("Location_id")] = json::value::number(l.id);
						responseBodyPart[U("Location_name")] = json::value::string(utility::conversions::to_string_t(l.name));
						responseBodyPart[U("Location_address")] = json::value::string(utility::conversions::to_string_t(l.address));
						responseBodyPart[U("Location_city")] = json::value::string(utility::conversions::to_string_t(l.city));
						responseBodyPart[U("Location_zip")] = json::value::number(l.zip);
						responseBodyPart[U("Location_country")] = json::value::string(utility::conversions::to_string_t(l.country));

						responseBody[i] = responseBodyPart;
						i++;
					}

					http_response response(status_codes::OK);
					addHeaders(response);
					response.set_body(responseBody);

					message.reply(response);

				}
				catch (const json::json_exception & e)
				{
					std::cout << "exception: " << e.what() << std::endl;

					auto responseBody = json::value::object();
					responseBody[U("error")] = json::value::string(U("Invalid JSON"));

					http_response response(status_codes::BadRequest);
					addHeaders(response);
					response.set_body(responseBody);

					message.reply(response);
				}
				catch (const std::exception ex)
				{

					http_response response(status_codes::BadRequest);
					addHeaders(response);
				
					message.reply(response);
				}
				catch (...)
				{

					http_response response(status_codes::BadRequest);
					addHeaders(response);
					
					message.reply(response);
				}

			});
			try 
			{
				searchDB.get();
			}
			catch (std::exception & e)
			{
				std::cout << e.what() << std::endl;
			}
		
		}
	}
	else
	{

		http_response response(status_codes::NotFound);
		addHeaders(response);

		message.reply(response);
	}

}

void MicroserviceController::handleDelete(http_request message) {
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::DEL));
	auto path = requestPath(message);
	if (!path.empty())
	{
		if (path[0] == U("locations") && path[1] == U("delete")) 
		{
			auto deleteRow =  message.extract_json().then([=](json::value requestBody) {
				try
				{
				
					Location deleteLocation;

					if (requestBody.has_field(U("Location_id"))) {
						deleteLocation.id = requestBody[U("Location_id")].as_integer();


						if (requestBody.has_field(U("Location_name")))
							deleteLocation.name = toString(requestBody[U("Location_name")].as_string().c_str());


						if (requestBody.has_field(U("Location_address")))
							deleteLocation.address = toString(requestBody[U("Location_address")].as_string().c_str());

						if (requestBody.has_field(U("Location_city")))
							deleteLocation.city = toString(requestBody[U("Location_city")].as_string().c_str());

						if (requestBody.has_field(U("Location_zip")))
							deleteLocation.zip = requestBody[U("Location_zip")].as_integer();

						if (requestBody.has_field(U("Location_country")))
							deleteLocation.country = toString(requestBody[U("Location_country")].as_string().c_str());

						if (dao.deleteRow(deleteLocation))
						{
							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Deletion successful"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						}
						else
						{
							auto responseBody = json::value::object();
							responseBody[U("Results")] = json::value::string(U("Deletion failed, please check your parameters"));

							http_response response(status_codes::OK);
							addHeaders(response);
							response.set_body(responseBody);

							message.reply(response);
						}
					}
					else
					{
						auto responseBody = json::value::object();
						responseBody[U("Results")] = json::value::string(U("Invalid JSON"));

						http_response response(status_codes::OK);
						addHeaders(response);
						response.set_body(responseBody);

						message.reply(response);

					}
				}
				catch (const json::json_exception & e)
				{
					std::cout << "exception: " << e.what() << std::endl;
					auto responseBody = json::value::object();
					responseBody[U("error")] = json::value::string(U("Invalid JSON"));

					http_response response(status_codes::BadRequest);
					addHeaders(response);
					response.set_body(responseBody);

					message.reply(response);
				}
				catch (const std::exception ex)
				{

					http_response response(status_codes::BadRequest);
					addHeaders(response);

					message.reply(response);
				}
				catch (...)
				{

					http_response response(status_codes::BadRequest);
					addHeaders(response);

					message.reply(response);
				}

			});
			try
			{
				deleteRow.get();
			}
			catch (std::exception & e)
			{
				std::cout << "exception: " << e.what() << std::endl;

			}
		}
		else
		{

			http_response response(status_codes::NotFound);
			addHeaders(response);

			message.reply(response);
		}
	}
	else
	{

		http_response response(status_codes::NotFound);
		addHeaders(response);

		message.reply(response);
	}

}

void MicroserviceController::handleHead(http_request message) {
	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::HEAD));
	message.reply(response);
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::HEAD));
}

void MicroserviceController::handleOptions(http_request message) {
	http_response response(status_codes::OK);
	addHeaders(response);

	message.reply(response);
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::OPTIONS));
}

void MicroserviceController::handleTrace(http_request message) {
	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::TRCE));
	message.reply(response);
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::TRCE));
}

void MicroserviceController::handleConnect(http_request message) {
	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::CONNECT));
	message.reply(response);
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::CONNECT));
}

void MicroserviceController::handleMerge(http_request message) {
	http_response response(status_codes::NotImplemented);
	addHeaders(response);
	response.set_body(responseNotImpl(methods::MERGE));
	message.reply(response);
	//message.reply(status_codes::NotImplemented, responseNotImpl(methods::MERGE));
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
void MicroserviceController::addHeaders(http_response& response) {
	response.headers().add(U("Access-Control-Allow-Origin"), U("*"));
	response.headers().add(U("Access-Control-Allow-Headers"), U("Content-Type"));
	response.headers().add(U("Access-Control-Allow-Methods"), U("GET,POST,DELETE,OPTIONS"));
}