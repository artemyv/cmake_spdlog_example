#include <spdlog/sinks/stdout_color_sinks.h> // or "../stdout_sinks.h" if no colors needed
#include <spdlog/spdlog.h>
#include "logger.h"
#include <iostream>

#define WIN32_LEAN_AND_MEAN
#include <windows.h> // Defines macros used by TraceLoggingProvider.h
#include <TraceLoggingProvider.h>  // The native TraceLogging API
#include <winmeta.h> // for WINEVENT_LEVEL_* definitions

// Forward-declare the g_hMyComponentProvider variable that you will use for tracing in this component
TRACELOGGING_DECLARE_PROVIDER(g_hMyComponentProvider);

// Define the GUID to use in TraceLoggingProviderRegister 
// {3970F9cf-2c0c-4f11-b1cc-e3a1e9958833}
TRACELOGGING_DEFINE_PROVIDER(
    g_hMyComponentProvider,
    "SimpleTraceLoggingProvider",
    (0x3970f9cf, 0x2c0c, 0x4f11, 0xb1, 0xcc, 0xe3, 0xa1, 0xe9, 0x95, 0x88, 0x33));


class TraceLoggingSample
{
public:
    void BasicDataTypes();
    void NamingData();
    void LevelsAndKeywords();
};

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

    
    TraceLoggingSample sample;

    sample.BasicDataTypes();
    sample.NamingData();
    sample.LevelsAndKeywords();

    fmt::print("Please stop the trace and click enter\n");

    std::cin.get();

    TraceLoggingUnregister(g_hMyComponentProvider);


    return 0;
}

void TraceLoggingSample::BasicDataTypes()
{
    UINT8 u8 = 200;
    INT32 i32 = -2000000000;
    UINT32 u32 = 4000000000;
    INT64 i64 = 9000000000000000000;
    float f32 = 3.14f;
    BOOL b = TRUE;
    bool bcpp = true;

    /*
    The following four "NumericValues" events are equivalent (except where noted) ...
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "NumericValues",
        TraceLoggingUInt8(u8, "UINT8"),
        TraceLoggingInt32(i32, "INT32"),
        TraceLoggingUInt32(u32, "UINT32"),
        TraceLoggingHexUInt32(u32, "UINT32"),
        TraceLoggingInt64(i64, "INT64"),
        TraceLoggingFloat32(f32, "float"),
        TraceLoggingBool(b, "BOOL"),
        TraceLoggingBoolean(bcpp, "bool (C++)")
    );

    /*
    same as ...
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "NumericValues",
        TraceLoggingUInt8(200, "UINT8"),
        TraceLoggingInt32(-2000000000, "INT32"),
        TraceLoggingUInt32(4000000000, "UINT32"),
        TraceLoggingHexUInt32(4000000000, "UINT32"),
        TraceLoggingInt64(9000000000000000000, "INT64"),
        TraceLoggingFloat32(3.14f, "float"),
        TraceLoggingBool(TRUE, "BOOL"),
        TraceLoggingBoolean(true, "bool (C++)")
    );

    /*
    same as ...
    */

#ifdef __cplusplus

    /*
    TraceLoggingValue() automatically determines the value type (C++ only)
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "NumericValues",
        TraceLoggingValue(u8, "UINT8"),
        TraceLoggingValue(i32, "INT32"),
        TraceLoggingValue(u32, "UINT32"),
        TraceLoggingValue(u32, "UINT32"),
        TraceLoggingValue(i64, "INT64"),
        TraceLoggingValue(f32, "float"),
        TraceLoggingValue(b, "BOOL"),         // This will be evaluated as INT32, not as BOOL
        TraceLoggingValue(bcpp, "bool (C++)")
    );

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "NumericValues",
        TraceLoggingValue((BYTE)200, "UINT8"),
        TraceLoggingValue(-2000000000, "INT32"),
        TraceLoggingValue(4000000000, "UINT32"),
        TraceLoggingValue(4000000000, "UINT32"),    // This one won't show up as hex. TraceLoggingValue will use default out types
        TraceLoggingValue(9000000000000000000, "INT64"),
        TraceLoggingValue(3.14f, "float"),
        TraceLoggingValue((BOOL)TRUE, "BOOL"),      // This will be evaluated as INT32, not as BOOL
        TraceLoggingValue((bool)true, "bool (C++)")
    );

#endif


    /*
    Strings and chars
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Strings and Chars",
        TraceLoggingString("String1", "String (char)"),
        TraceLoggingWideString(L"LString2", "String (wide char)"),
        TraceLoggingChar('A', "Single char")
    );


    /*
    Other types
    */

    /*
    NOTE: In C, a GUID, FILETIME, or SYSTEMTIME value parameter must be an l-value.
    */

 /*   INT_PTR iptr = 1234;
    UINT_PTR uptr = 4321;
    FILETIME ft;
    SYSTEMTIME st;
    SID const sid1 = { SID_REVISION, 1, 5, { 6 } };
    static const GUID s_TestGuid = { 0x3970f9cf, 0x2c0c, 0x4f11, { 0xb1, 0xcc, 0xe3, 0xa1, 0xe9, 0x95, 0x88, 0x33 } };

    GetSystemTime(&st);
    GetSystemTimeAsFileTime(&ft);*/

    //TraceLoggingWrite(
    //    g_hMyComponentProvider,
    //    "Other Types",
    //    TraceLoggingGuid(s_TestGuid, "GUID"),
    //    TraceLoggingSystemTime(st, "Current Time (FILETIME)"),
    //    TraceLoggingPointer((LPCVOID)&iptr, "void*"),
    //    TraceLoggingSid(&sid1, "SID")
    //    TraceLoggingIntPtr(iptr, "INT_PTR"),
    //    TraceLoggingUIntPtr(uptr, "UINT_PTR")
    //);
}

void TraceLoggingSample::NamingData()
{
    UINT32 Cat = 0xCA7;

    /*
    Each of the following four events are equivalent:
    */

    /*
    TraceLogging uses the symbol to automatically name the field "Cat"
    and assign it the value contained in the variable Cat (0xCA7).
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Cat1",
        TraceLoggingUInt32(Cat)
    );

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Cat2",
        TraceLoggingValue(Cat)
    );


    /*
    Use a different symbol for the value of the event's "Cat" field.
    */

    UINT32 Tiger = Cat;

    /*
    Now we need to explicitly name the datum or we will have events with a
    different field name ("Tiger").
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Tiger",
        TraceLoggingUInt32(Tiger, "Cat")
    );

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Cat3",
        TraceLoggingValue(Tiger, "Cat")
    );
};

void TraceLoggingSample::LevelsAndKeywords()
{
    /*
    Verbosity levels and event keywords must be compile-time constants.

    TraceLoggingLevel accepts values 0-255
    TraceLoggingKeyword accepts values 0 to UINT64_MAX

    See winmeta.h for predefined verbosity levels and reserved keyword values.
    */

    PCWSTR MyName = L"Joe";
    INT16 MyRank = 99;
    ULONG MySerialNumber = 12345;

    /*
    The following is only logged when session verbosity level is
    WINEVENT_LEVEL_VERBOSE (5) or higher ...
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Levels",
        TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
        TraceLoggingWideString(MyName, "Name"),
        TraceLoggingInt16(MyRank, "Rank"),
        TraceLoggingUInt32(MySerialNumber, "Serial Number")
    );

    /*
    TraceLoggingWrite will not complain if TraceLoggingLevel is invoked more than once.
    However, only the last level will be used.
    The following event is only logged at WINEVENT_LEVEL_VERBOSE or higher...
    */

    TraceLoggingWrite(
        g_hMyComponentProvider,
        "Levels",
        TraceLoggingLevel(WINEVENT_LEVEL_CRITICAL),
        TraceLoggingLevel(WINEVENT_LEVEL_VERBOSE),
        TraceLoggingWideString(MyName, "Name"),
        TraceLoggingInt16(MyRank, "Rank"),
        TraceLoggingUInt32(MySerialNumber, "Serial Number")
    );
}
