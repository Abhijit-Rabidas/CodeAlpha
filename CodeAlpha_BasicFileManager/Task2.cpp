#include <iostream>
#include <filesystem>
#include <fstream>
#include <vector>
#include <string>

using namespace std;
namespace fs = filesystem;

// Function to clear the terminal
void clearScreen()
{
#ifdef _WIN32
    system("cls"); // Windows
#else
    system("clear"); // Linux/Unix/Mac
#endif
}

// Function to list both directories and files in the given path
void listContents(const string &path)
{
    cout << "Contents of " << path << ": " << endl;

    // List directories
    cout << "\nDirectories:\n";
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_directory())
        {
            cout << "[DIR] " << entry.path().filename().string() << endl;
        }
    }

    // List files
    cout << "\nFiles:\n";
    for (const auto &entry : fs::directory_iterator(path))
    {
        if (entry.is_regular_file())
        {
            cout << "[FILE] " << entry.path().filename().string() << endl;
        }
    }
}

// Function to create a new directory
void createDirectory(const string &path)
{
    if (fs::create_directories(path))
    {
        cout << "Directory created successfully: " << path << endl;
    }
    else
    {
        cout << "Failed to create directory or it already exists: " << path << endl;
    }
}

// Function to create a new file
void createFile(const string &filePath)
{
    ofstream My_File(filePath);
    if (My_File)
    {
        cout << "File created successfully: " << filePath << endl;
    }
    else
    {
        cout << "Failed to create file: " << filePath << endl;
    }
}

// Function to read from a file
void readFile(const string &filePath)
{
    ifstream My_File(filePath);
    if (My_File)
    {
        string line;
        cout << "Reading file: " << filePath << "\n";
        while (getline(My_File, line))
        {
            cout << line << endl;
        }
    }
    else
    {
        cout << "Failed to open file: " << filePath << endl;
    }
}

// Function to write into a file 
void writeFile(const string &filePath, const string &content)
{
    ofstream My_File(filePath, ios::app); // Open in append mode
    if (My_File)
    {
        My_File << content << endl;
        cout << "Content written to file: " << filePath << endl;
    }
    else
    {
        cout << "Failed to open file: " << filePath << endl;
    }
}

// Function to copy a file to another location
void copyFile(const string &currentDir, const string &source, const string &destination)
{
    string fullSourcePath, fullDestinationPath;

    // If the source path is relative, prepend currentDir
    if (!fs::path(source).is_absolute())
    {
        fullSourcePath = currentDir + "/" + source;
    }
    else
    {
        fullSourcePath = source;
    }

    // If the destination path is relative, prepend currentDir
    if (!fs::path(destination).is_absolute())
    {
        fullDestinationPath = currentDir + "/" + destination;
    }
    else
    {
        fullDestinationPath = destination;
    }

    try
    {
        fs::copy(fullSourcePath, fullDestinationPath, fs::copy_options::overwrite_existing);
        cout << "File copied successfully from " << fullSourcePath << " to " << fullDestinationPath << endl;
    }
    catch (fs::filesystem_error &e)
    {
        cout << "Error copying file: " << e.what() << endl;
    }
}

// Function to move a file to another location
void moveFile(const string &currentDir, const string &source, const string &destination)
{
    string fullSourcePath, fullDestinationPath;

    // If the source path is relative, prepend currentDir
    if (!fs::path(source).is_absolute())
    {
        fullSourcePath = currentDir + "/" + source;
    }
    else
    {
        fullSourcePath = source;
    }

    // If the destination path is relative, prepend currentDir
    if (!fs::path(destination).is_absolute())
    {
        fullDestinationPath = currentDir + "/" + destination;
    }
    else
    {
        fullDestinationPath = destination;
    }

    try
    {
        fs::rename(fullSourcePath, fullDestinationPath);
        cout << "File moved successfully from " << fullSourcePath << " to " << fullDestinationPath << endl;
    }
    catch (fs::filesystem_error &e)
    {
        cout << "Error moving file: " << e.what() << endl;
    }
}

// Function to navigate into another directory
void changeDirectory(string &currentDir, const string &newDir)
{
    string potentialPath = currentDir + "/" + newDir;
    if (fs::exists(potentialPath) && fs::is_directory(potentialPath))
    {
        currentDir = potentialPath;
        cout << "Changed directory to: " << currentDir << endl;
    }
    else
    {
        cout << "Directory does not exist: " << potentialPath << endl;
    }
}

// Function to go up one directory
void goUpDirectory(string &currentDir)
{
    fs::path p(currentDir);
    if (p.has_parent_path())
    {
        currentDir = p.parent_path().string();
        cout << "Moved up to directory: " << currentDir << endl;
    }
    else
    {
        cout << "Already at the root directory." << endl;
    }
}

int main()
{
    string command;
    string filePath, content, source, destination, newDirName, targetDir;
    string currentDir = fs::current_path().string(); // Start at the current directory

    while (true)
    {
        clearScreen(); // Clear the terminal on each loop iteration

        cout << "\nCurrent Directory: " << currentDir << endl;
        cout << "\nMenu:" << endl;
        cout << "1. ls - List directories and files" << endl;
        cout << "2. mkdir - Create a new directory" << endl;
        cout << "3. touch - Create a file" << endl;
        cout << "4. cat - Read a file" << endl;
        cout << "5. echo - Write to a file" << endl;
        cout << "6. cp - Copy a file" << endl;
        cout << "7. mv - Move a file" << endl;
        cout << "8. cd - Change directory" << endl;
        cout << "9. cd .. - Go up one directory" << endl;
        cout << "10. exit - Exit" << endl;

        cout << "Enter a command (ls, mkdir, touch, cat, echo, cp, mv, cd, cd.., exit): ";
        cin >> command;

            if (command == "ls" || command == "1")
            {
                listContents(currentDir);
            }
            else if (command == "mkdir" || command == "2")
            {
                cout << "Enter the name of the new directory: ";
                cin >> newDirName;
                createDirectory(currentDir + "/" + newDirName);
            }
            else if (command == "touch" || command == "3")
            {
                cout << "Enter the name of the file to create: ";
                cin >> filePath;
                createFile(currentDir + "/" + filePath);
            }
            else if (command == "cat" || command == "4")
            {
                cout << "Enter the name of the file to read: ";
                cin >> filePath;
                readFile(currentDir + "/" + filePath);
            }

            else if (command == "echo" || command == "5")
            {
                cout << "Enter the name of the file to write to: ";
                cin >> filePath;
                cin.ignore(); // Ignore newline character after file path input
                cout << "Enter the content to write: ";
                getline(cin, content);
                writeFile(currentDir + "/" + filePath, content);
            }
            else if (command == "cp" || command == "6")
            {
                cout << "Enter the source file path (relative or full path): ";
                cin >> source;
                cout << "Enter the destination path (relative or full path): ";
                cin >> destination;
                copyFile(currentDir, source, destination); // Pass currentDir
            }
            else if (command == "mv" || command == "7")
            {
                cout << "Enter the source file path (relative or full path): ";
                cin >> source;
                cout << "Enter the destination path (relative or full path): ";
                cin >> destination;
                moveFile(currentDir, source, destination); // Pass currentDir
            }
            else if (command == "cd" || command == "8")
            {
                cout << "Enter the directory name to navigate into: ";
                cin >> targetDir;
                changeDirectory(currentDir, targetDir);
            }
            else if (command == "cd.." || command == "9")
            {
                goUpDirectory(currentDir);
            }
            else if (command == "exit" || command == "10")
            {
                cout << "Exiting the program." << endl;
                return 0;
            }
            else
            {
                cout << "Invalid choice. Please try again." << endl;
            }

        cout << "\nPress Enter to continue...";
        cin.ignore();
        cin.get(); // Wait for user to press Enter
    }

    return 0;
}
