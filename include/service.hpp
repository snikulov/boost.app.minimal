#ifndef SERVICE_HPP_INCLUDED__
#define SERVICE_HPP_INCLUDED__

#include <boost/application.hpp>

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

    int operator()()
    {
        boost::shared_ptr<boost::application::status> st = ctx_.find<boost::application::status>();
        while (st->state() != boost::application::status::stopped)
        {
            // sleep one second...
            boost::this_thread::sleep(boost::posix_time::seconds(1));
        }
        return 0;
    }

    bool stop()
    {
        return true;
    }

private:
    boost::application::context& ctx_;

    service& operator=(const service&) = delete;
    service(const service&) = delete;
    service() = delete;
};


#endif
