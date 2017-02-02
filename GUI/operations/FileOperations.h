//////////////////////////////////////////////////////////////////////////
// This file is part of openPSTD.                                       //
//                                                                      //
// openPSTD is free software: you can redistribute it and/or modify     //
// it under the terms of the GNU General Public License as published by //
// the Free Software Foundation, either version 3 of the License, or    //
// (at your option) any later version.                                  //
//                                                                      //
// openPSTD is distributed in the hope that it will be useful,          //
// but WITHOUT ANY WARRANTY; without even the implied warranty of       //
// MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        //
// GNU General Public License for more details.                         //
//                                                                      //
// You should have received a copy of the GNU General Public License    //
// along with openPSTD.  If not, see <http://www.gnu.org/licenses/>.    //
//                                                                      //
//////////////////////////////////////////////////////////////////////////

//////////////////////////////////////////////////////////////////////////
//
// Date:
//
//
// Authors:
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

//
// Created by michiel on 18-7-2015.
//

#ifndef OPENPSTD_FILEOPERATIONS_H
#define OPENPSTD_FILEOPERATIONS_H

#include "BaseOperation.h"
#include <string>
#include "../Model.h"

namespace OpenPSTD
{
    namespace GUI
    {
        class OpenFileOperation : public BaseOperation
        {
        public:
            OpenFileOperation(std::string filename);

            virtual void Run(const Reciever &reciever) override;

        private:
            std::string filename;
        };

        class NewFileOperation : public BaseOperation
        {
        public:
            NewFileOperation(std::string filename);

            virtual void Run(const Reciever &reciever) override;

        private:
            std::string filename;
        };

        class SaveFileOperation : public BaseOperation
        {
        public:
            virtual void Run(const Reciever &reciever) override;
        };

        class SaveAsFileOperation : public BaseOperation
        {
        public:
            SaveAsFileOperation(std::string filename);

            virtual void Run(const Reciever &reciever) override;

        private:
            std::string filename;
        };

        class ImportGeometryOperation: public BaseOperation
        {
        public:
            ImportGeometryOperation(std::string filename);

            void Run(const Reciever &reciever) override;
        private:
            std::string filename;
        };

        class ExportToHDF5Operation : public BaseOperation
        {
        public:
            ExportToHDF5Operation(std::string filename);

            virtual void Run(const Reciever &reciever) override;

        private:
            std::string filename;
        };

        enum class ImageFormat
        {
            PNG,
            BMP,
            JPG
        };

        class ExportToImageOperation : public BaseOperation
        {
        public:
            ExportToImageOperation(std::string directory, std::string name, OpenPSTD::GUI::ImageFormat format);

            virtual void Run(const Reciever &reciever) override;

            std::string directory;
            std::string name;
            int startFrame;
            int endFrame;
            ImageFormat format;
        };

    }
}

#endif //OPENPSTD_FILEOPERATIONS_H
