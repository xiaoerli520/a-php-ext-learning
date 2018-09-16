#include "phpx.h"

#include <iostream>
#include <sys/time.h>

using namespace php;
using namespace std;


PHPX_FUNCTION(my_hql_echo)
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


PHPX_EXTENSION()
{
    Extension *extension = new Extension("my_hql", "0.0.1");

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

    extension->registerFunction(PHPX_FN(my_hql_echo));

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
