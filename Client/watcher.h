#ifndef WATCHER_H
#define WATCHER_H

#include <iostream>
#include <string>
#include <sys/inotify.h>
#include <unistd.h>
#include <functional>
#include <atomic>
#include <map>

#define EVENT_SIZE (sizeof(struct inotify_event))
#define BUFFER_LEN (1024 * (EVENT_SIZE + 16))

class Watcher {
public:
    Watcher(const std::string& path, std::function<void(const std::string&, const std::string&)> callback);
    ~Watcher();
    void startWatching();
    void stopWatching(); // <-- New function to stop the watcher

private:
    std::string m_path;
    int m_fd;
    std::map<int, std::string> m_watches;
    std::atomic<bool> keep_running;
    std::function<void(const std::string&, const std::string&)> m_callback;

    void watchExistingDirectories(const std::string& path);
    void addWatch(const std::string& path);
};

#endif
