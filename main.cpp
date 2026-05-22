#include "App.h"
#include "AppExceptions.h"
#include <iostream>

int main()
{
    try {
        App app;
        app.run();
    }
    catch (const MapLoadException& e)        { std::cerr << "[Error] " << e.what() << "\n"; return 1; }
    catch (const UnknownMarkerTypeException& e) { std::cerr << "[Error] " << e.what() << "\n"; return 1; }
    catch (const std::exception& e)          { std::cerr << "[Error] " << e.what() << "\n"; return 1; }
    return 0;
}
