// DataDog Agent
#include <opentracing/dynamic_load.h>
#include <iostream>
#include <string>

auto& CreateTracer()
{
    std::string error_message;
  	auto handle_maybe = opentracing::DynamicallyLoadTracingLibrary(
	      "/usr/local/lib/libdd_opentracing_plugin.so", error_message);
	  /*if (!handle_maybe) {
	    std::cerr << "Failed to load tracer library " << error_message << "\n";
	    return 1;
	  }*/

	std::string tracer_config = R"({
	      "service": "ragnacompose-mysql-client",
	      "agent_host": "datadog",
	      "agent_port": 8126
	    })"; 

	auto& tracer_factory = handle_maybe->tracer_factory();
	auto tracer_maybe = tracer_factory.MakeTracer(tracer_config.c_str(), error_message);
	/*if (!tracer_maybe) {
	  std::cerr << "Failed to create tracer " << error_message << "\n";
	  return 1;
	}*/

    auto tracer = *tracer_maybe;

    return tracer;
}