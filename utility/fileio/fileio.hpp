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
#ifndef UTILITY_INC_FILEIO_FILEIO_HPP_
#define UTILITY_INC_FILEIO_FILEIO_HPP_

#include <fstream>
#include <string>
#include <vector>

namespace utility {

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
     * FileOperationStatus replace()
     * Replace the whole line with the [line] parameter
     * Will return failure status if keyword is not found
     *
     * [in] keyword - the keyword used to find the line-to-be-replaced
     * [in] line - the new line that will replace the old
     *
     * [ret] status
    */
    FileOperationStatus replace(const std::string& keyword, const std::string& line);

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
    FileOperationStatus overWriteFile(const std::vector<std::string>& fileContents);
};

}  // namespace utility
#endif  // UTILITY_INC_FILEIO_FILEIO_HPP_