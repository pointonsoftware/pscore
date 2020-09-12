/**************************************************************************************************
*                                            PSCORE                                               *
*                               Copyright (C) 2020 Pointon Software                               *
*                                                                                                 *
*           This program is free software: you can redistribute it and/or modify                  *
*           it under the terms of the GNU Affero General Public License as published              *
*           by the Free Software Foundation, either version 3 of the License, or                  *
*           (at your option) any later version.                                                   *
*                                                                                                 *
*           This program is distributed in the hope that it will be useful,                       *
*           but WITHOUT ANY WARRANTY; without even the implied warranty of                        *
*           MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the                         *
*           GNU Affero General Public License for more details.                                   *
*                                                                                                 *
*           You should have received a copy of the GNU Affero General Public License              *
*           along with this program.  If not, see <https://www.gnu.org/licenses/>.                *
*                                                                                                 *
*           Ben Ziv <pointonsoftware@gmail.com>                                                   *
*                                                                                                 *
**************************************************************************************************/
#include <fileio/fileio.hpp>
#include <algorithm>
#include <iostream>

namespace utility {

FileIo::FileIo(const std::string& file) : mFileName(file) {
    openFile(file);
}

FileIo::~FileIo() {
    closeFile();
}

FileOperationStatus FileIo::read(std::vector<std::string>* container) {
    if (!container) {
        return FileOperationStatus::FAILED;
    }
    if (!isFileOpen()) {
        return FileOperationStatus::FILE_NOT_FOUND;
    }
    // Set ostream to the first line of the file
    mFile.seekg(0);
    // read
    std::string buf;
    while (getline(mFile, buf)) {
        container->emplace_back(buf);
    }
    mFile.clear();
    return FileOperationStatus::SUCCESS;
}

FileOperationStatus FileIo::write(const std::string& str) {
    if (!isFileOpen()) {
        return FileOperationStatus::FILE_NOT_FOUND;
    }
    // write
    mFile << str << std::endl;
    return FileOperationStatus::SUCCESS;
}

FileOperationStatus FileIo::find(const std::string& keyword, std::string* out) {
    if (!out) {
        return FileOperationStatus::FAILED;
    }
    if (!isFileOpen()) {
        return FileOperationStatus::FILE_NOT_FOUND;
    }
    // read
    std::vector<std::string> readContainer;
    read(&readContainer);
    // find
    *out = [&readContainer, &keyword]() {
                for (const std::string temp : readContainer) {
                    if (temp.find(keyword) != std::string::npos) {
                        return temp;
                    }
                }
                return std::string("");
            }();
    return FileOperationStatus::SUCCESS;
}

FileOperationStatus FileIo::replace(const std::string& keyword, const std::string& line) {
     if (!isFileOpen()) {
        return FileOperationStatus::FILE_NOT_FOUND;
    }
    // read
    std::vector<std::string> readContainer;
    read(&readContainer);
    // try to find and replace
    const bool keywordFound = [&readContainer, &keyword, &line]() {
        using VectorIterator = std::vector<std::string>::iterator;
        for (VectorIterator it = readContainer.begin(); it != readContainer.end(); ++it) {
             if (it->find(keyword) != std::string::npos) {
                *it = line;
                return true;
            }
        }
        return false;
    }();
    return (keywordFound ? overWriteFile(readContainer) : FileOperationStatus::FAILED);
}

FileOperationStatus FileIo::discard() {
    return std::remove(mFileName.c_str()) ?
        FileOperationStatus::FAILED :
        FileOperationStatus::SUCCESS;
}

bool FileIo::isFileOpen() {
    return mFile.is_open();
}

FileOperationStatus FileIo::overWriteFile(const std::vector<std::string>& fileContents) {
    // temporarily close our member file for overwriting
    closeFile();
    // reopen the file as ostream (to overwrite!)
    std::ofstream newFile(mFileName);
    if (!newFile.is_open()) {
        // not sure what can cause us to fail reopening the file
        // maybe a race-condition? (future proofing)
        // anyhow, let's try to reopen through our member file to keep other operations running
        openFile(mFileName);
        return FileOperationStatus::FILE_NOT_FOUND;
    }
    // let's write!
    for (const std::string temp : fileContents) {
        newFile << temp << std::endl;
    }
    // make sure to reopen our member file
    openFile(mFileName);
    return FileOperationStatus::SUCCESS;
}

void FileIo::openFile(const std::string& file) {
    mFile.open(file.c_str(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
    // (todo) might have to return a status from this function
    // Future callers might need to know if we have successfully created/opened the file
}

void FileIo::closeFile() {
    mFile.close();
}

}  // namespace utility