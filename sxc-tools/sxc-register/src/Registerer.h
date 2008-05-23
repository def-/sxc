#include <gloox/client.h>
#include <gloox/connectionlistener.h>
#include <gloox/registration.h>
#include <gloox/logsink.h>
#include <gloox/loghandler.h>

class Registerer
    : public gloox::RegistrationHandler, gloox::ConnectionListener
{
    public:
        void start(gloox::JID jid);
        virtual void onConnect();
        virtual void onDisconnect(gloox::ConnectionError e);
        virtual void handleRegistrationFields(
            const gloox::JID &from,
            int fields,
            std::string instructions);
        virtual void handleRegistrationResult(
            const gloox::JID &from,
            gloox::RegistrationResult result);
        void print(std::string text);

        Registerer() {}
        virtual ~Registerer() {}
        virtual bool onTLSConnect(const gloox::CertInfo& info) {}
        virtual void handleAlreadyRegistered(const gloox::JID &from) {}
        virtual void handleDataForm(
            const gloox::JID &from,
            const gloox::DataForm &form) {}
        virtual void handleOOB(
            const gloox::JID &from,
            const gloox::OOB &oob) {}

    private:
        static std::string prefix;
        static std::string registrationPrefix;
        static std::string connectionPrefix;
        gloox::JID *jid;
        gloox::Registration *registration;
        gloox::Client *client;
};
