#include <iostream>

#include <boost/application.hpp>

#include "service.hpp"

namespace app = boost::application;

#ifdef BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST
    #include <boost/make_shared.hpp>
    #include <boost/bind.hpp>
    namespace elib = boost;
#else
    #include <system_error>
    namespace elib = std;
#endif


int main( int argc, char * argv[] )
{
    app::context ctx;
    service s( ctx );

    ctx.insert< app::path >( elib::make_shared< app::path >() );
    ctx.insert< app::args >( elib::make_shared< app::args >(argc, argv) );
    ctx.insert< app::termination_handler >(
                elib::make_shared< app::termination_handler_default_behaviour >(
                    elib::bind( &service::stop, &s )
                    ) );

    return app::launch< app::common >( s, ctx );
}

