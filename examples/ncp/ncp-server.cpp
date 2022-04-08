/**
 * Example of a D-Bus server which implements org.freedesktop.DBus.ObjectManager
 *
 * The example uses the generated stub API layer to register an object manager under "org.sdbuscpp.examplemanager"
 * and add objects underneath which implement "org.sdbuscpp.ExampleManager.Planet1".
 */

#include "ncp-server-glue.h"
#include <sdbus-c++/sdbus-c++.h>
#include <iostream>
#include <memory>
#include <thread>
#include <chrono>

static std::unique_ptr<sdbus::IConnection> g_connection;

class ManagerAdaptor : public sdbus::AdaptorInterfaces< sdbus::ObjectManager_adaptor >
{
public:
    ManagerAdaptor(sdbus::IConnection& connection, std::string path)
    : AdaptorInterfaces(connection, std::move(path))
    {
        registerAdaptor();
    }

    ~ManagerAdaptor()
    {
        unregisterAdaptor();
    }
};

class NcpAdaptor final : public sdbus::AdaptorInterfaces< consent::dbus::api::ConsentManager_adaptor,
                                                sdbus::ManagedObject_adaptor,
                                                sdbus::Properties_adaptor >
{
public:
    NcpAdaptor(sdbus::IConnection& connection, std::string path)
    : AdaptorInterfaces(connection, std::move(path))
    {
        registerAdaptor();
        emitInterfacesAddedSignal({consent::dbus::api::ConsentManager_adaptor::INTERFACE_NAME});
    }

    ~NcpAdaptor()
    {
        emitInterfacesRemovedSignal({consent::dbus::api::ConsentManager_adaptor::INTERFACE_NAME});
        unregisterAdaptor();
    }

    std::string queryConsent(const std::string& userId, const std::string& applicationId, const std::string& applicationDisplayName, 
    const std::string& context, const std::string& piiScopeName) override
    {
        return std::string("false");
    }

    std::string concatenate(const std::string& first, const std::string& second) override
    {
        return first + second;
    }

   bool quit()
   {
       g_connection->leaveEventLoop();
       return true;
   }
};

int main()
{
    std::cerr << __DATE__ << " : " << __TIME__ << std::endl;

    g_connection = sdbus::createSessionBusConnection();
    g_connection->requestName("mbux.service");

    auto manager = std::make_unique<ManagerAdaptor>(*g_connection, "/consent/dbus/api/ConsentManager");
    auto ncpServer = std::make_unique<NcpAdaptor>(*g_connection, "/consent/dbus/api/ConsentManager");
    g_connection->enterEventLoop();

    g_connection->releaseName("mbux.service");
    
    return 0;
}
