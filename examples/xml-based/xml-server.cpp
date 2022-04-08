/**
 * Example of a D-Bus server which implements org.freedesktop.DBus.ObjectManager
 */

#include "planet-server-glue.h"
#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

static std::unique_ptr<sdbus::IConnection> g_connection;

class ServerAdaptor final : public sdbus::AdaptorInterfaces<
    consent::dbus::api::ConsentManager_adaptor,
    sdbus::ObjectManager_adaptor,
    sdbus::ManagedObject_adaptor,
    sdbus::Properties_adaptor >
{
public:
    ServerAdaptor(sdbus::IConnection& connection, std::string path)
    : AdaptorInterfaces(connection, std::move(path))
    {
        registerAdaptor();
        emitInterfacesAddedSignal({consent::dbus::api::ConsentManager_adaptor::INTERFACE_NAME});
    }

    ~ServerAdaptor()
    {
        emitInterfacesRemovedSignal({consent::dbus::api::ConsentManager_adaptor::INTERFACE_NAME});
        unregisterAdaptor();
    }

    std::string concatenate(const std::string& first, const std::string& second) override
    {
        return first + second;
    }

    std::string concatenateWords(const std::vector<std::string>& words) override
    {
        std::string result;

        for ( const auto& c : words )
            result += c;

        return result;
    }

    bool quit()
    {        
        g_connection->leaveEventLoop();
        return true;
    }
};

int main( int argc, char**argv )
{
    // Represents the 'dbus-send --dest=...' name.
    auto constexpr busName = "sdbus.example.api";
    // Represents the 'dbus-send <destination object path>'.
    auto constexpr objPath = "/org/sdbus/examples";

    std::cerr <<
        "Server (" <<
        __DATE__ << " : " << __TIME__ << 
        ") starting ..." << std::endl;

    g_connection = sdbus::createSessionBusConnection( busName );

    auto earth = std::make_unique<ServerAdaptor>(*g_connection, objPath);

    g_connection->enterEventLoop();

    g_connection->releaseName(busName);

    return 0;
}
