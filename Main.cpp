

// Include mongoose
#include "mongoose.h"
#include <string>
#include <iostream>

// Struct contains settings for how to server http with mong.
static struct mg_serve_http_opts s_http_server_opts;

// Event handler
static void ev_handler(struct mg_connection *nc, int ev, void *p)
{
	// If event is a http request
	if (ev == MG_EV_HTTP_REQUEST)
	{
		// Server static html files
		mg_serve_http(nc, (struct http_message *) p, s_http_server_opts);
	}
}

int initServer(int port)
{
	// Mong event manager
	struct mg_mgr mgr;
	// Mongoose connection
	struct mg_connection *nc;

	//Convert port to char
	std::string portToChar = std::to_string(port);
	static char const *sPort = portToChar.c_str();

	// Init mongoose
	mg_mgr_init(&mgr, NULL);
	std::cout << "Starting web server on port " << sPort << std::endl;

	nc = mg_bind(&mgr, sPort, ev_handler);

	// if connection fails
	if (nc == NULL)
	{

	}

	// Set up HTTP server options
	mg_set_protocol_http_websocket(nc);

	s_http_server_opts.document_root = ".";

	s_http_server_opts.enable_directory_listing = "yes";

	for (;;)
	{
		mg_mgr_poll(&mgr, 1000);
	}

	// free memory
	mg_mgr_free(&mgr);

	return 0;
}

int main(void)
{
	int port;
	std::cout << "Select server port" << std::endl;

	std::cin >> port;

	// faled case
	if (std::cin.fail())
	{
		port = 1000;
	}

	initServer(port);
}