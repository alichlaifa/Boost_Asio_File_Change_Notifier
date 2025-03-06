#ifndef CONFIG_H
#define CONFIG_H

#include <string>

namespace Config {
    const std::string server_ip = "YOUR_SERVER_IP";  // Change IP before running
    const short server_port = 12345;                // Default port
    const std::string watched_folder = "Watched_folder";  // Change folder to watch
}

#endif // CONFIG_H

