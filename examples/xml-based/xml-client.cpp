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

#include <planet-client-glue.h>

class PlanetProxy final : public sdbus::ProxyInterfaces< consent::dbus::api::ConsentManager_proxy >
{
public:
    PlanetProxy(sdbus::IConnection& connection, std::string destination, std::string path)
    : ProxyInterfaces(connection, std::move(destination), std::move(path))
    {
        registerProxy();
    }

    ~PlanetProxy()
    {
        unregisterProxy();
    }
};

int main( int argc, char**argv )
{
    auto connection = sdbus::createSessionBusConnection();

    // Represents the 'dbus-send --dest=...' name.
    auto constexpr busName = "sdbus.example.api";
    // Represents the 'dbus-send <destination object path>'.
    auto constexpr objPath = "/org/sdbus/examples";

    PlanetProxy planet(
        *connection,
        busName,
        objPath );

    if ( argc == 2 && std::string(argv[1]) == "quit" )
    {
        std::cout << planet.quit() << std::endl;
    }
    else if ( argc == 4 && std::string(argv[1]) == "concat" )
    {
        std::cout << planet.concatenate( std::string(argv[2]), std::string(argv[3]) ) << std::endl;   
    }
    else if ( argc > 4 && std::string(argv[1]) == "concat" )
    {
        std::vector<std::string> strings;

        for ( int i = 2 ; i < argc ; i++ )
            strings.push_back( argv[i] );

        std::cout << planet.concatenateWords( strings ) << std::endl;   
    }
    else
    {
        std::cerr << "concat x y | quit" << std::endl;
        return 0;
    }

    return 0;
}
