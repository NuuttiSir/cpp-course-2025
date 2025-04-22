#include <Log.hpp>
#include <catch2/catch_session.hpp>

int main(int argc, char** argv)
{
    // create the default logger
    pixelmancy::logger::Log::Init();

    P_LOG_INFO() << "Starting the tests suite" << pixelmancy::logger::endl << "\n";

    int result = Catch::Session().run(argc, argv);
    return result;
}
