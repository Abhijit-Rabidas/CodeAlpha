#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
namespace fs = std::filesystem;

// Function to clear the terminal
void clearScreen() {
#ifdef _WIN32
    system("cls");  // Windows
#else
    system("clear");  // Linux/Unix/Mac
#endif
}

// Function to list both directories and files in the given path
void listContents(const string& path) {
    cout << "Contents of " << path << ":\n";
    
    // List directories
    cout << "\nDirectories:\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_directory()) {
            cout << "[DIR] " << entry.path().filename().string() << endl;
        }
    }
    
    // List files
    cout << "\nFiles:\n";
    for (const auto& entry : fs::directory_iterator(path)) {
        if (entry.is_regular_file()) {
            cout << "[FILE] " << entry.path().filename().string() << endl;
        }
    }
}

void createDirectory(const string& path) {
    if (fs::create_directories(path)) {
        cout << "Directory created successfully: " << path << endl;
    } else {
        cout << "Failed to create directory or it already exists: " << path << endl;
    }
}

void createFile(const string& filePath) {
    ofstream outFile(filePath);
    if (outFile) {
        cout << "File created successfully: " << filePath << endl;
    } else {
        cout << "Failed to create file: " << filePath << endl;
    }
}

void readFile(const string& filePath) {
    ifstream inFile(filePath);
    if (inFile) {
        string line;
        cout << "Reading file: " << filePath << "\n";
        while (getline(inFile, line)) {
            cout << line << endl;
        }
    } else {
        cout << "Failed to open file: " << filePath << endl;
    }
}

void writeFile(const string& filePath, const string& content) {
    ofstream outFile(filePath, ios::app); // Open in append mode
    if (outFile) {
        outFile << content << endl;
        cout << "Content written to file: " << filePath << endl;
    } else {
        cout << "Failed to open file: " << filePath << endl;
    }
}

void copyFile(const string& currentDir, const string& source, const string& destination) {
    string fullSourcePath, fullDestinationPath;
    
    // If the source path is relative, prepend currentDir
    if (!fs::path(source).is_absolute()) {
        fullSourcePath = currentDir + "/" + source;
    } else {
        fullSourcePath = source;
    }
    
    // If the destination path is relative, prepend currentDir
    if (!fs::path(destination).is_absolute()) {
        fullDestinationPath = currentDir + "/" + destination;
    } else {
        fullDestinationPath = destination;
    }

    try {
        fs::copy(fullSourcePath, fullDestinationPath, fs::copy_options::overwrite_existing);
        cout << "File copied successfully from " << fullSourcePath << " to " << fullDestinationPath << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Error copying file: " << e.what() << endl;
    }
}


void moveFile(const string& currentDir, const string& source, const string& destination) {
    string fullSourcePath, fullDestinationPath;
    
    // If the source path is relative, prepend currentDir
    if (!fs::path(source).is_absolute()) {
        fullSourcePath = currentDir + "/" + source;
    } else {
        fullSourcePath = source;
    }
    
    // If the destination path is relative, prepend currentDir
    if (!fs::path(destination).is_absolute()) {
        fullDestinationPath = currentDir + "/" + destination;
    } else {
        fullDestinationPath = destination;
    }

    try {
        fs::rename(fullSourcePath, fullDestinationPath);
        cout << "File moved successfully from " << fullSourcePath << " to " << fullDestinationPath << endl;
    } catch (fs::filesystem_error& e) {
        cout << "Error moving file: " << e.what() << endl;
    }
}

void changeDirectory(string& currentDir, const string& newDir) {
    string potentialPath = currentDir + "/" + newDir;
    if (fs::exists(potentialPath) && fs::is_directory(potentialPath)) {
        currentDir = potentialPath;
        cout << "Changed directory to: " << currentDir << endl;
    } else {
        cout << "Directory does not exist: " << potentialPath << endl;
    }
}

void goUpDirectory(string& currentDir) {
    fs::path p(currentDir);
    if (p.has_parent_path()) {
        currentDir = p.parent_path().string();
        cout << "Moved up to directory: " << currentDir << endl;
    } else {
        cout << "Already at the root directory." << endl;
    }
}

int main() {
    int choice;
    string filePath, content, source, destination, newDirName, targetDir;
    string currentDir = fs::current_path().string(); // Start at the current directory

    while (true) {
        clearScreen();  // Clear the terminal on each loop iteration

        cout << "\nCurrent Directory: " << currentDir << "\n";
        cout << "\nMenu:\n";
        cout << "1. List directories and files\n";
        cout << "2. Create a new directory\n";
        cout << "3. Create a file\n";
        cout << "4. Read a file\n";
        cout << "5. Write to a file\n";
        cout << "6. Copy a file\n";
        cout << "7. Move a file\n";
        cout << "8. Change directory\n";
        cout << "9. Go up one directory\n";
        cout << "10. Exit\n";
        cout << "Enter your choice: ";
        cin >> choice;

        switch (choice) {
            case 1:
                listContents(currentDir);
                break;
            case 2:
                cout << "Enter the name of the new directory: ";
                cin >> newDirName;
                createDirectory(currentDir + "/" + newDirName);
                break;
            case 3:
                cout << "Enter the name of the file to create: ";
                cin >> filePath;
                createFile(currentDir + "/" + filePath);
                break;
            case 4:
                cout << "Enter the name of the file to read: ";
                cin >> filePath;
                readFile(currentDir + "/" + filePath);
                break;
            case 5:
                cout << "Enter the name of the file to write to: ";
                cin >> filePath;
                cin.ignore(); // Ignore newline character after file path input
                cout << "Enter the content to write: ";
                getline(cin, content);
                writeFile(currentDir + "/" + filePath, content);
                break;
            case 6:
                cout << "Enter the source file path (relative or full path): ";
                cin >> source;
                cout << "Enter the destination path (relative or full path): ";
                cin >> destination;
                copyFile(currentDir, source, destination);  // Pass currentDir
                break;
            case 7:
                cout << "Enter the source file path (relative or full path): ";
                cin >> source;
                cout << "Enter the destination path (relative or full path): ";
                cin >> destination;
                moveFile(currentDir, source, destination);  // Pass currentDir
                break;
            case 8:
                cout << "Enter the directory name to navigate into: ";
                cin >> targetDir;
                changeDirectory(currentDir, targetDir);
                break;
            case 9:
                goUpDirectory(currentDir);
                break;
            case 10:
                cout << "Exiting the program." << endl;
                return 0;
            default:
                cout << "Invalid choice. Please try again." << endl;
        }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get();  // Wait for user to press Enter
    }

    return 0;
}

