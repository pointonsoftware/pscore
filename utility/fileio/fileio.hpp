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
#ifndef UTILITY_FILEIO_FILEIO_HPP_
#define UTILITY_FILEIO_FILEIO_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace utility {

using VectorIterator = std::vector<std::string>::iterator;

enum class FileOperationStatus {
    SUCCESS = 0x00,
    FAILED = 0x01,
    FILE_NOT_FOUND = 0x02,
    PERMISSION_DENIED = 0x03
};

/*
 * Warning: FileIo class is not tested for thread-safety
*/
class FileIo {
 public:
    /*!
     * Caller must provide the complete file path and file name
     * Will create a new file if it doesn't exist
    */
    explicit FileIo(const std::string& file);

    /*!
     * File stream will close upon destruction
    */
    ~FileIo();

     /*!
     * FileOperationStatus read()
     * Reads the file line by line and store them in the vector
     *
     * @params
     * [out] container
     *
     * [ret] status
    */
    FileOperationStatus read(std::vector<std::string>* container);

    /*!
     * FileOperationStatus write()
     * Will write the passed string at the end of the file as a new line
     *
     * @params
     * [in] str
     *
     * [ret] status
    */
    FileOperationStatus write(const std::string& str);

    /*!
     * FileOperationStatus find()
     * Will find the keyword in the file.
     * If keyword is found, will return the whole line through the [out] parameter
     * Otherwise, will return empty string
     *
     * @params
     * [in] keyword
     * [out] out
     *
     * [ret] status
    */
    FileOperationStatus find(const std::string& keyword, std::string* out);

    /*!
     * FileOperationStatus find_and_replace()
     * Find a line that contains the keyword and replace with the [newline] parameter
     * Will return failure status if keyword is not found
     *
     * [in] keyword - the keyword used to find the line-to-be-replaced
     * [in] newline - the new line that will replace the old
     *
     * [ret] status
    */
    FileOperationStatus find_and_replace(const std::string& keyword, const std::string& newline);

    /*!
     * FileOperationStatus discard()
     * Will delete the file
     *
     * Warning!!! File will be removed.
     *
     * [ret] status
    */
    FileOperationStatus discard();

 private:
    std::fstream mFile;
    const std::string mFileName;
    bool isFileOpen();
    void openFile(const std::string& file);
    void closeFile();

    /*!
     * VectorIterator overWriteFile()
     * Overwrites our mFile with [fileContents] parameter
     *
     * [in] fileContents - the new contents to place in the file
     *
     * [ret] status
    */
    FileOperationStatus overWriteFile(const std::vector<std::string>& fileContents);

    /*!
     * VectorIterator findVectorContent()
     * Find the key from the container and return the iterator
     * Returns container.end() if key is not found
     *
     * [in] key - the keyword to find
     * [in] container  - the vector container
     *
     * [ret] pointer to the element when found
    */
    VectorIterator findVectorContent(const std::string& keyword,
                                     std::vector<std::string>* container);

    /*!
     * FileOperationStatus replace()
     * Replace an element in the container with [newElement] parameter
     *
     * [in] key - pointer to the element that will be replaced in the vector
     * [in] container  - the vector container
     * [in] line - the new line that will replace the old
     *
     * [ret] New vector (container + updated element)
    */
    std::vector<std::string> replaceVectorElement(VectorIterator key,
                    const std::vector<std::string>& container, const std::string& newElement);
};

}  // namespace utility
#endif  // UTILITY_FILEIO_FILEIO_HPP_
