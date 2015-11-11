#ifndef SERVICE_HPP_INCLUDED__
#define SERVICE_HPP_INCLUDED__

#ifdef BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST
    #include <boost/make_shared.hpp>
    #include <boost/bind.hpp>
    namespace elib = boost;
#else
    #include <system_error>
    namespace elib = std;
#endif

#include <boost/application.hpp>
//#include <zmq.hpp>

class service
{
public:
    explicit service(boost::application::context& c)
        : ctx_(c)
    {
    }

    ~service()
    {
    }

    int worker()
    {
        while (ctx_.find<boost::application::status>()->state() != boost::application::status::stopped)
        {
            // sleep one second...
            elib::this_thread::sleep_for(elib::chrono::seconds(1));
        }
        return 0;
    }

    int operator()()
    {
        return worker();
    }

    bool stop()
    {
        std::cerr << "Stop requested..." << std::endl;
        return true;
    }

private:
    boost::application::context& ctx_;

    service& operator=(const service&) = delete;
    service(const service&)            = delete;
    service()                          = delete;
};


#endif
