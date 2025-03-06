# **Boost Asio File Change Notifier**  

A **C++ project** using **Boost.Asio** and **inotify** to monitor file changes in a specified directory and send notifications to a remote server. This client-server system allows tracking **file creations, modifications, and deletions** in real-time.

---

## 🚀 Features
### **Client Side**
- Monitors a folder (and its subdirectories) for file changes.
- Uses **inotify** to detect **created, modified, and deleted** files.
- Sends change notifications to the server over **Boost.Asio TCP**.
- Simple command to **exit** the client safely.

### **Server Side**
- Listens for file change notifications from the client.
- Logs received file events to the console.
- Graceful handling of **client disconnects**.

  ## ⚙️ Setup & Installation

### **1️⃣ Prerequisites**
Make sure you have the following installed:
- **C++17 or later**
- **Boost.Asio library**
- **CMake**
- **Linux (for inotify support on the client side)**

### **2️⃣ Clone the Repository**
```bash
git clone https://github.com/yourusername/Boost_Asio_File_Change_Notifier.git
cd Boost_Asio_File_Change_Notifier
```

### **2️⃣ Configure config.h Files**
Edit the config.h files in both the Client and Server directories to set your server IP, server port, and watched folder.

## 🏗 Building the Project

### 1️⃣ Build the Server

To build the server, follow these steps:

```bash
cd Server
mkdir build && cd build
cmake ..
make
```
Run the server:

```bash
./server
```
### 2️⃣ Build the Client

To build the client, follow these steps:

```bash
cd Server
mkdir build && cd build
cmake ..
make
```
Run the client:

```bash
./client
```
## 🎯 Usage

### 1️⃣ Modify, Create, or Delete Files in the Watched Folder
The client will automatically detect changes in the watched folder and notify the server.

- The server will print received events to the console.
- File creation, modification, and deletion will be tracked.

### 2️⃣ To Stop the Client
To stop the client, type:

```bash
exit
```

