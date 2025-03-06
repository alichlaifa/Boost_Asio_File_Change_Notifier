#include "watcher.h"
#include <sys/types.h>
#include <dirent.h>
#include <cstring>

Watcher::Watcher(const std::string& path, std::function<void(const std::string&, const std::string&)> callback)
    : m_path(path), m_callback(callback), keep_running(true) {
    m_fd = inotify_init();
    if (m_fd < 0) {
        perror("inotify_init");
        return;
    }
    watchExistingDirectories(m_path);
}

Watcher::~Watcher() {
    for (const auto& [wd, path] : m_watches) {
        inotify_rm_watch(m_fd, wd);
    }
    close(m_fd);
}

void Watcher::watchExistingDirectories(const std::string& path) {
    addWatch(path);

    DIR* dir = opendir(path.c_str());
    if (dir) {
        struct dirent* entry;
        while ((entry = readdir(dir)) != nullptr) {
            if (entry->d_type == DT_DIR) {
                std::string name = entry->d_name;
                if (name != "." && name != "..") {
                    std::string subPath = path + "/" + name;
                    watchExistingDirectories(subPath);
                }
            }
        }
        closedir(dir);
    }
}

void Watcher::addWatch(const std::string& path) {
    int wd = inotify_add_watch(m_fd, path.c_str(), IN_CREATE | IN_DELETE | IN_MODIFY | IN_CLOSE_WRITE);
    if (wd < 0) {
        perror("inotify_add_watch");
    } else {
        m_watches[wd] = path;
        if (path != m_path) { 
            std::cout << "Now watching: " << path << std::endl;
        }
    }
}

void Watcher::startWatching() {
    char buffer[BUFFER_LEN];

    while (keep_running) {
        int length = read(m_fd, buffer, BUFFER_LEN);
        if (length < 0) {
            if (keep_running) perror("read");
            break;
        }

        int i = 0;
        while (i < length) {
            struct inotify_event* event = (struct inotify_event*)&buffer[i];

            if (event->len > 0 && event->name[0] != '.') {
                std::string eventPath = m_watches[event->wd] + "/" + event->name;
                std::string eventType;

                if (event->mask & IN_CREATE) {
                    eventType = "CREATE";
                    if (event->mask & IN_ISDIR) {
                        watchExistingDirectories(eventPath);
                    }
                } else if (event->mask & IN_DELETE) {
                    eventType = "DELETE";
                } else if (event->mask & IN_MODIFY || event->mask & IN_CLOSE_WRITE) {
                    eventType = "MODIFY";
                }

                if (!eventType.empty()) {
                    std::cout << "Detected: " << eventType << " → " << eventPath << std::endl;
                    m_callback(eventType, eventPath);
                }
            }
            i += EVENT_SIZE + event->len;
        }
    }
}

void Watcher::stopWatching() {
    keep_running = false;
}
