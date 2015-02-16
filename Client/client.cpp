#include "client.h"
#include <iostream>
#include "dirent.h" // for file reading
#include "hash.h"
using namespace std;

FileInfo newFileInfo(string name, string hash, string cdnAddr) {
  FileInfo f = FileInfo();
  f.name = name;
  f.hash = hash;
  f.cdnAddr = cdnAddr;
  return f;
}

void printFileInfo(FileInfo f) {
  printf("%s %s %s\n", f.name.c_str(), f.hash.c_str(), f.cdnAddr.c_str());
}

Client::Client() {
}

Client::~Client() {
}

void Client::syncDownload() {
  // Get list of files in directory
  vector<FileInfo> files = getListOfFilesFromDirectory();
  for (size_t i = 0; i < files.size(); i++)
    printFileInfo(files[i]);

  // Compare with origin server
  vector<FileInfo> diffFiles = compareListOfFiles(files);

  // For each file that needs to be updated, download
  for(size_t i = 0; i < diffFiles.size();i ++)
    downloadFile(diffFiles[i]);
}

void Client::syncUpload() {
  // Get list of files in directory
  vector<FileInfo> files = getListOfFilesFromDirectory();
  for (size_t i = 0; i < files.size(); i++)
    printFileInfo(files[i]);

  // Compare with origin server
  vector<FileInfo> diffFiles = compareListOfFiles(files);

  // For each file that needs to be updated, upload
  for(size_t i = 0; i < diffFiles.size();i ++)
    uploadFile(diffFiles[i]);
}

vector<FileInfo> Client::compareListOfFiles(vector<FileInfo>& files) {
  // Upload list of file / hashes
  // return list of fileNames that need to be dl'd / uploaded
  vector<string> diff;

  // upload files
  // diff = what server returns as files needed to download

  // return diff;
  return files;
}

vector<FileInfo> Client::getListOfFilesFromDirectory() {
  cout << "Getting list of files from ./" << endl;
  vector<FileInfo> files;

  DIR *dir = opendir(".");
  if (dir == NULL) {
    cout << "Could not open directory ./" << endl;
    return files;
  }

  struct dirent *ent;
  while ((ent = readdir(dir)) != NULL) {
    // Skip hidden files
    if (ent->d_name[0] == '.')
      continue;

    // Convert to string object and add to return vector
    FileInfo f = newFileInfo(ent->d_name, hashFile(ent->d_name));
    files.push_back(f);
  }

  return files;
}

void Client::downloadFile(FileInfo f) {
  // directly download file from cdn
  printf("Downloading file... ");
  printFileInfo(f);
  // request file f communication
}

void Client::uploadFile(FileInfo f) {
  printf("Uploading file... ");
  printFileInfo(f);
  // upload file to cdn node
}