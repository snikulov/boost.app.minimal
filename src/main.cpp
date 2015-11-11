#include <iostream>

#include <boost/application.hpp>
#include <boost/program_options.hpp>

#include "service.hpp"

namespace app = boost::application;
namespace po = boost::program_options;

#ifdef BOOST_APPLICATION_FEATURE_NS_SELECT_BOOST
    #include <boost/make_shared.hpp>
    #include <boost/bind.hpp>
    namespace elib = boost;
#else
    namespace elib = std;
#endif

// provide setup example for windows service
#if defined(BOOST_WINDOWS_API)
#   include "setup/windows/setup/service_setup.hpp"
#endif


int main(int argc, char * argv[])
{
    app::context ctx;
    service s(ctx);

    elib::shared_ptr<app::path> mypath = elib::make_shared< app::path >();
    ctx.insert< app::path >(mypath);
    ctx.insert< app::args >(elib::make_shared< app::args >(argc, argv));
    ctx.insert< app::termination_handler >(
        elib::make_shared< app::termination_handler_default_behaviour >(
        [&s](){ return s.stop(); }
//            elib::bind(&service::stop, &s)
            ));
    // define our simple installation schema options
    po::options_description opts("service options");

    // provide setup for windows service
    opts.add_options()
        ("help", "produce a help message")
        ("console", "run on console")
        ("daemon", "run as a service")
#if defined(BOOST_WINDOWS_API) && !defined(__MINGW32__)
        ("install", "install service")
        ("uninstall", "unistall service")
        ("name", po::value<std::string>()->default_value(mypath->executable_name().stem().string()), "service name")
        ("display", po::value<std::string>()->default_value(""), "service display name (optional, installation only)")
        ("description", po::value<std::string>()->default_value(""), "service description (optional, installation only)")
#endif
        ;
    po::variables_map vm;
    po::store(po::parse_command_line(argc, argv, opts), vm);

    if (vm.count("help"))
    {
        std::cout << opts << std::endl;
        return 0;
    }
    else if (vm.count("console"))
    {
        return app::launch< app::common >(s, ctx);
    }
#if defined(BOOST_WINDOWS_API) && !defined(__MINGW32__)
    else if (vm.count("install"))
    {
        boost::system::error_code ec;
        app::example::install_windows_service(
            app::setup_arg(vm["name"].as<std::string>()),
            app::setup_arg(vm["display"].as<std::string>()),
            app::setup_arg(vm["description"].as<std::string>()),
            app::setup_arg(mypath->executable_path_name()),
            app::setup_arg(""),
            app::setup_arg(""),
            app::setup_arg("auto"),
            app::setup_arg(""),
            app::setup_arg("--daemon")
        ).install(ec);

        std::cout << ec.message() << std::endl;

        return ec.value();
    }
    else if (vm.count("uninstall"))
    {
        boost::system::error_code ec;
        app::example::uninstall_windows_service(
            app::setup_arg(vm["name"].as<std::string>()),
            app::setup_arg(mypath->executable_path_name())).uninstall(ec);

        std::cout << ec.message() << std::endl;

        return ec.value();
    }
#endif
    else if (vm.count("daemon"))
    {
        return app::launch< app::server >(s, ctx);
    }

    std::cout << opts << std::endl;
    return 0;
}

