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
// Date: 23-1-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef OPENPSTD_GEOMETRYIMPORT_H
#define OPENPSTD_GEOMETRYIMPORT_H

#include "openpstd-shared_export.h"
#include <iostream>
#include <vector>
#include <memory>
#include <Eigen/Dense>
#include <kernel/KernelInterface.h>

namespace OpenPSTD
{
    namespace Shared
    {
        class OPENPSTD_SHARED_EXPORT GeometryImport
        {
        public:
            OPENPSTD_SHARED_EXPORT GeometryImport(std::unique_ptr<std::istream> input);
            std::shared_ptr<std::vector<std::vector<int>>> DGIndices;
            std::shared_ptr<std::vector<Eigen::Vector2f>> DGVertices;
            std::shared_ptr<std::vector<OpenPSTD::Kernel::DomainConf>> PSTDDomains;
        };

        class OPENPSTD_SHARED_EXPORT ErrorInGeometryFileException : public std::exception {
        public:
            OPENPSTD_SHARED_EXPORT const char *what() const noexcept override;
        };
    }
}

#endif //OPENPSTD_GEOMETRYIMPORT_H
