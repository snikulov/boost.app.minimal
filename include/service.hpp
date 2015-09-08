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
//        ctx_.find<boost::application::wait_for_termination_request>()->wait();
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
