/**
 * Example of a D-Bus client which implements org.freedesktop.DBus.ObjectManager
 *
 * The example uses the generated stub API layer to listen to interfaces added to new objects under
 * "org.sdbuscpp.examplemanager". If added, we access "org.sdbuscpp.ExampleManager.Planet1" to print
 * info like this:
 * /org/sdbuscpp/examplemanager/Planet1/Earth added:	org.sdbuscpp.ExampleManager.Planet1
 * Earth has a population of 7874965825.
 *
 */

#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <thread>

#include <ncp-client-glue.h>

class NcpProxy final : public sdbus::ProxyInterfaces< consent::dbus::api::ConsentManager_proxy >
{
public:
    NcpProxy(sdbus::IConnection& connection, std::string destination, std::string path)
    : ProxyInterfaces(connection, std::move(destination), std::move(path))
    {
        registerProxy();
    }

    ~NcpProxy()
    {
        unregisterProxy();
    }
};

int main( int argc, char**argv )
{
    auto connection = sdbus::createSessionBusConnection();

    NcpProxy ncp(*connection, "mbux.service", "/consent/dbus/api/ConsentManager");

    if ( argc == 2 && std::string(argv[1]) == "quit" )
    {
        std::cout << ncp.quit() << std::endl;
    }
    else if ( argc == 4 && std::string(argv[1]) == "concatenate" )
    {
        std::cout << ncp.concatenate( std::string(argv[2]), std::string(argv[3]) ) << std::endl;   
    }
    else if ( argc == 4 && std::string(argv[1]) == "queryConsent" )
    {
        std::cout << ncp.queryConsent( std::string(argv[2]), std::string(argv[3]), std::string(argv[4]), 
                    std::string(argv[5]), std::string(argv[6]) ) << std::endl;   
    }
    else
    {
        std::cerr << "concatenate x y | queryConsent user appId appName context scopeName | quit" << std::endl;
        return 0;
    }

    return 0;
}
