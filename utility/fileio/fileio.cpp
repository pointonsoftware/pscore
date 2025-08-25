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
#include "fileio.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <iostream>

namespace utility {

FileIo::FileIo(const std::string& file) : mFileName(file) {
    open();  // We open the file right on object creation
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
#ifdef _WIN32
        buf.erase(std::remove(buf.begin(), buf.end(), '\r'), buf.end());
#endif
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

    {
        // Read
        std::vector<std::string> readContainer;
        read(&readContainer);
        {
            // Find
            VectorIterator value = findVectorContent(keyword, &readContainer);
            *out = value != readContainer.end() ? *(value) : std::string("");
        }
    }

    return FileOperationStatus::SUCCESS;
}

FileOperationStatus FileIo::find_and_replace(const std::string& keyword,
                                             const std::string& newline) {
    if (!isFileOpen()) {
        return FileOperationStatus::FILE_NOT_FOUND;
    }

    // Read
    std::vector<std::string> readContainer;
    read(&readContainer);

    // Try to find the key
    VectorIterator lineToReplace = findVectorContent(keyword, &readContainer);

    if (lineToReplace == readContainer.end()) {
        // Key not found!
        return FileOperationStatus::FAILED;
    }

    // Replace the current contents then overwrite the file
    return overWriteFile(replaceVectorElement(lineToReplace, readContainer, newline));
}

std::vector<std::string> FileIo::replaceVectorElement(VectorIterator key,
                    const std::vector<std::string>& container, const std::string& newElement) {
    if (key != container.end()) {
        // Replace here!
        *key = newElement;
    }
    return container;
}

VectorIterator FileIo::findVectorContent(const std::string& keyword,
                                         std::vector<std::string>* container) {
    return std::find_if(container->begin(), container->end(), [&keyword](const std::string& str) {
            return str.find(keyword) != std::string::npos;
     });
}

FileOperationStatus FileIo::discard() {
    return std::remove(mFileName.c_str()) ?
        FileOperationStatus::FAILED :
        FileOperationStatus::SUCCESS;
}

FileOperationStatus FileIo::clear_contents() {
    if (!isFileOpen()) {
        return FileOperationStatus::FAILED;
    }
    // First close the file
    close();
    {
        // Clear contents
        std::ofstream(mFileName, std::ios::out | std::ios::trunc);
    }
    // Reopen
    open();
    return FileOperationStatus::SUCCESS;
}

std::string FileIo::get_last_line() {
    if (!isFileOpen()) {
        throw std::runtime_error("No file opened.");
    }
    std::string buf;
    // Set ostream to the end line of the file
    mFile.seekg(-1, std::ios_base::end);
    if (mFile.peek() == '\n') {
        // Read backwards until we find the starting point
        mFile.seekg(-1, std::ios_base::cur);
        for (int i = mFile.tellg(); i > 0; i--) {
            if (mFile.peek() == '\n') {
                // We found the end of the second-to-the-last line
                mFile.get();
                break;
            }
            mFile.seekg(i, std::ios_base::beg);
        }
    }
    // Read
    getline(mFile, buf);
    // Reset seek
    mFile.clear();
    return buf;
}

bool FileIo::isFileOpen() {
    return mFile.is_open();
}

FileOperationStatus FileIo::overWriteFile(const std::vector<std::string>& fileContents) {
    // temporarily close our member file for overwriting
    close();
    // reopen the file as ostream (to overwrite!)
    std::ofstream newFile(mFileName);
    if (!newFile.is_open()) {
        // not sure what can cause us to fail reopening the file
        // maybe a race-condition? (future proofing)
        // anyhow, let's try to reopen through our member file to keep other operations running
        return open();
    }
    // let's write!
    for (const std::string& temp : fileContents) {
        newFile << temp << std::endl;
    }
    // make sure to reopen our member file
    return open();
}

FileOperationStatus FileIo::open() {
    mFile.open(mFileName.c_str(), std::ios::in | std::ios::out | std::ios::app | std::ios::binary);
    return mFile.good() ? FileOperationStatus::SUCCESS : FileOperationStatus::FAILED;
}

void FileIo::close() {
    mFile.close();
}

}  // namespace utility