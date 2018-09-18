#include "phpx.h"

#include <iostream>
#include <regex>
#include <sys/time.h>

using namespace php;
using namespace std;


PHPX_FUNCTION(my_hql_info)
{
    struct timeval tv;
    gettimeofday(&tv,NULL);
    int start = 1435017600;

    Array arr;
    arr.set("HowLong", tv.tv_sec - start);
    arr.set("WHO", "HeQuanLi");
    arr.set("WHEN WE START", "2015-6-23");
    retval = arr;
}

// auto add \n on the end of line
PHPX_FUNCTION(my_hql_echox)
{
    echo("%s\n", args[0].toCString());
}

PHPX_FUNCTION(my_hql_is_email)
{
    Variant a = false;
    regex pattern("([0-9A-Za-z\\-_\\.]+)@([0-9a-z]+\\.[a-z]{2,3}(\\.[a-z]{2})?)");
    if (regex_match(args[0].toCString(), pattern)) {
        a = true;
    }
    retval = a;
}

PHPX_FUNCTION(my_hql_is_phone)
{
    Variant a = false;
    regex e("^1(3\\d|47|5([0-3]|[5-9])|8(0|2|[5-9]))\\d{8}$");

    if (regex_match(args[0].toCString(), e)) {
        a = true;
    }
    retval = a;

}


PHPX_EXTENSION()
{
    Extension *extension = new Extension("my_hql", "0.0.2");

    extension->onStart = [extension]() noexcept
    {
        extension->registerConstant("my_hql_VERSION", 1001);
        extension->registerConstant("WHEN_WE_START", 1435017600);
    };

//    extension->onShutdown = [extension]() noexcept
//    {
//        cout << extension->name << "shutdown" << endl;
//    };
//
//    extension->onBeforeRequest = [extension]() noexcept
//    {
//        cout << extension->name << "beforeRequest" << endl;
//    };
//
//    extension->onAfterRequest = [extension]() noexcept
//    {
//        cout << extension->name << "afterRequest" << endl;
//    };

    extension->registerFunction(PHPX_FN(my_hql_info));
    extension->registerFunction(PHPX_FN(my_hql_echox));
    extension->registerFunction(PHPX_FN(my_hql_is_email));
    extension->registerFunction(PHPX_FN(my_hql_is_phone));

    extension->info(
    {
        "my_hql support", "enabled"
    },
    {
        { "author", "GuoQingZhe" },
        { "for", "HeQuanLi"},
        { "we_start_at", "2015-06-23"},
        { "love_hql", "forever"},
        { "version", extension->version },
        { "date", "2018-09-06" },
    });

    return extension;
}
