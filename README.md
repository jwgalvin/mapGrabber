# 🖘️ MapGrabber

A modern C++ project using **Domain-Driven Design (DDD)** principles to structure and eventually interact with mapping APIs (e.g. OpenStreetMap, Mapbox). This serves as a sandbox for experimenting with C++, architectural patterns, and real-world data integrations.

---

## 📆 Features

- Domain-driven architecture
- Modular codebase with `domain`, `application`, `infrastructure`, and `ui` layers
- Git + CMake ready
- "Hello World" CLI example using a simulated `Location` service

---

## 🚀 Getting Started

### 1. 📅 Clone the repo

```bash
git clone https://github.com/jwgalvin/mapGrabber.git
cd mapGrabber
```

### 2. 🔐 (Optional) Configure Git Identity

If you haven't set up Git locally:

```bash
git config user.name "Your Name"
git config user.email "youremail@gmail.com"
```

---

## 🐧 WSL Setup Guide (Optional for Windows Users)

Enable **WSL (Windows Subsystem for Linux)** to get a full Ubuntu-based dev environment inside Windows.

### ✅ Step 1: Install WSL

1. Open **PowerShell as Administrator**
2. Run:

   ```powershell
   wsl --install
   ```

3. Restart when prompted

---

### ✅ Step 2: Configure Ubuntu

After reboot, Ubuntu will launch and prompt you to:

- Create a UNIX-style username (e.g., `jwgalvin`)
- Enter and confirm a new password

---

### ✅ Step 3: Install Developer Tools

In the Ubuntu terminal, run:

```bash
sudo apt update
sudo apt install build-essential cmake curl git -y
```

---

### ✅ Step 4: Access Your Project from WSL

```bash
cd /mnt/c/Users/<your-username>/mapGrabber/YourProject
```

Or open the folder in File Explorer:

```bash
explorer.exe .
```

> ⚠️ **If you get a Git error about "dubious ownership" in WSL**, run this:

```bash
git config --global --add safe.directory /mnt/c/Users/<your-username>/mapGrabber
```

---

### ✅ Step 5: Use WSL in VSCode

1. Install the [Remote - WSL extension](https://marketplace.visualstudio.com/items?itemName=ms-vscode-remote.remote-wsl)
2. Open VSCode
3. Press `Ctrl+Shift+P` → `WSL: Open Folder`
4. Navigate to `/mnt/c/...` and open your project

---

### ✅ Step 6: Optional Quality-of-Life Tips

**Run Bash commands from PowerShell:**

```powershell
wsl ls -la
wsl g++ --version
```

**Set WSL as your default terminal in VSCode:**

```json
"terminal.integrated.defaultProfile.windows": "WSL"
```

**Launch Ubuntu from Start Menu or pin it to your taskbar** for quick access.

---

install this 'sudo apt install libcurl4-openssl-dev'


You're now ready to develop C++ with Bash, Linux tools, and full Windows interoperability 🚀


rm -rf build
cmake -S . -B build
cmake --build build
./build/main