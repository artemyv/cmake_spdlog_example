#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>
#include "logger.h"

#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Defines macros used by TraceLoggingProvider.h
#include <TraceLoggingProvider.h>  // The native TraceLogging API

// Forward-declare the g_hMyComponentProvider variable that you will use for tracing in this component
TRACELOGGING_DECLARE_PROVIDER(g_hMyComponentProvider);

// Define the GUID to use in TraceLoggingProviderRegister 
// {3970F9cf-2c0c-4f11-b1cc-e3a1e9958833}
TRACELOGGING_DEFINE_PROVIDER(
    g_hMyComponentProvider,
    "SimpleTraceLoggingProvider",
    (0x3970f9cf, 0x2c0c, 0x4f11, 0xb1, 0xcc, 0xe3, 0xa1, 0xe9, 0x95, 0x88, 0x33));


int main() {

    // Register the provider
    TraceLoggingRegister(g_hMyComponentProvider);

    spdlog::set_pattern("%5P:%-6t  [%8!n:%-5!l] %Y-%m-%d %H:%M:%S.%e %^#%$ %v [%!]");
    auto console = spdlog::stdout_color_mt("console");
    spdlog::set_default_logger(console);

    LOG_ERROR("do as printf,%s", "format");
    LOG_INFO("do as printf,%d", 125);

    SPDLOG_ERROR("do as fmt,{}", "format");
    SPDLOG_INFO("do as fmt,{}", 125);

    char sampleValue[] = "Sample value";

    // Log an event
    TraceLoggingWrite(g_hMyComponentProvider, // handle to my provider
        "HelloWorldTestEvent",              // Event Name that should uniquely identify your event.
        TraceLoggingValue(sampleValue, "TestMessage")); // Field for your event in the form of (value, field name).
    // Stop TraceLogging and unregister the provider

    TraceLoggingWrite(g_hMyComponentProvider, // handle to my provider
        "spdlog",              // Event Name that should uniquely identify your event.
        TraceLoggingValue("console", "logger"),
        TraceLoggingValue("some log string", "message")); // Field for your event in the form of (value, field name).

    
    TraceLoggingUnregister(g_hMyComponentProvider);


    return 0;
}
