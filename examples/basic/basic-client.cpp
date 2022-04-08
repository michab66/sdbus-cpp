#include <iostream>
#include <sdbus-c++/sdbus-c++.h>
#include <string>
#include <unistd.h>
#include <vector>

#include "basic.h"

void onConcatenated(sdbus::Signal& signal)
{
    std::string concatenatedString;
    signal >> concatenatedString;

    std::cout << "Received signal with concatenated string " << concatenatedString << std::endl;
}

int main(int argc, char *argv[])
{
    // Create proxy object for the concatenator object on the server side. Since here
    // we are creating the proxy instance without passing connection to it, the proxy
    // will create its own connection automatically, and it will be system bus connection.
    const char* destinationName = BUS_NAME;
    const char* objectPath = OBJECT_PATH;
    auto concatenatorProxy = sdbus::createProxy(destinationName, objectPath);

    // Let's subscribe for the 'concatenated' signals
    const char* interfaceName = INTERFACE_NAME;
    concatenatorProxy->registerSignalHandler(interfaceName, "concatenated", &onConcatenated);
    concatenatorProxy->finishRegistration();

    std::vector<int> numbers = {1, 2, 3};
    std::string separator = ":";

    // Invoke concatenate on given interface of the object
    {
        auto method = concatenatorProxy->createMethodCall(interfaceName, "concatenate");
        method << numbers << separator;
        auto reply = concatenatorProxy->callMethod(method);
        std::string result;
        reply >> result;
        assert(result == "1:2:3");
        std::cout << "Concatenated result: " << result << std::endl;
    }

    // Invoke concatenate again, this time with no numbers and we shall get an error
    {
        auto method = concatenatorProxy->createMethodCall(interfaceName, "concatenate");
        method << std::vector<int>() << separator;
        try
        {
            auto reply = concatenatorProxy->callMethod(method);
            assert(false);
        }
        catch(const sdbus::Error& e)
        {
            std::cerr << "Expected error: " << e.getName() << " with message " << e.getMessage() << std::endl;
        }
    }

    // Give sufficient time to receive 'concatenated' signal from the first concatenate invocation
    sleep(1);

    return 0;
}
