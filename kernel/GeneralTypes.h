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
// Date: 29-1-2016
//
//
// Authors: M. R. Fortuin
//
//
// Purpose: General types that can be used throughout the application.
//
//
//////////////////////////////////////////////////////////////////////////


#ifndef OPENPSTD_GENERALTYPES_H
#define OPENPSTD_GENERALTYPES_H

#include <memory>
#include <vector>
#include <Eigen/Dense>

namespace OpenPSTD
{
    namespace Kernel
    {
        const float NODETOL = 1e-8f;

        /**
         * short hand for a Vector
         */
        template<typename SimpleType>
        using VectorX = Eigen::Matrix<SimpleType, Eigen::Dynamic, 1>;

        /**
         * short hand for a Matrix
         */
        template<typename SimpleType>
        using MatrixX = Eigen::Matrix<SimpleType, Eigen::Dynamic, Eigen::Dynamic>;

        /**
         * short hand for a 1D Array
         */
        template<typename SimpleType>
        using ArrayX = Eigen::Array<SimpleType, Eigen::Dynamic, 1>;

        /**
         * short hand for a 2D Array
         */
        template<typename SimpleType>
        using ArrayXX = Eigen::Array<SimpleType, Eigen::Dynamic, Eigen::Dynamic>;

        using PSTD_FRAME_UNIT = float;
        using PSTD_FRAME = std::vector<PSTD_FRAME_UNIT>;
        using PSTD_FRAME_PTR = std::shared_ptr<PSTD_FRAME>;

        using PSTD_RECEIVER_DATA_UNIT = float;
        using PSTD_RECEIVER_DATA = std::vector<PSTD_FRAME_UNIT>;
        using PSTD_RECEIVER_DATA_PTR = std::shared_ptr<PSTD_FRAME>;

        using DG_FRAME_UNIT = float;
        using DG_FRAME = MatrixX<DG_FRAME_UNIT>;
        using DG_FRAME_PTR = std::shared_ptr<DG_FRAME>;
    }
}

#endif //OPENPSTD_GENERALTYPES_H
