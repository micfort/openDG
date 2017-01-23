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

#include "GeometryImport.h"

using namespace OpenPSTD::Shared;
using namespace OpenPSTD::Kernel;
using namespace Eigen;
using namespace std;

OPENPSTD_SHARED_EXPORT GeometryImport::GeometryImport(unique_ptr<istream> input):
        DGIndices(make_shared<vector<vector<int>>>()),
        DGVertices(make_shared<vector<Vector2f>>()),
        PSTDDomains(make_shared<vector<DomainConf>>())
{
    std::string start, type, end;
    int count;
    while(!input->eof())
    {
        *input >> start;
        if (start != "start")
            throw ErrorInGeometryFileException();
        *input >> type >> count;

        if(type == "PSTD_domains")
        {
            this->PSTDDomains->reserve(count);
            for (int i = 0; i < count; ++i)
            {
                float x, y, w, h, a_t, a_b, a_l, a_r;
                bool LR_t, LR_b, LR_l, LR_r;
                OpenPSTD::Kernel::DomainConf result;
                *input >> x >> y >> w >> h;
                result.TopLeft.setX(x);
                result.TopLeft.setY(y);
                result.Size.setX(w);
                result.Size.setX(h);
                *input >> result.T.Absorption;
                *input >> result.B.Absorption;
                *input >> result.L.Absorption;
                *input >> result.R.Absorption;
                *input >> result.T.LR;
                *input >> result.B.LR;
                *input >> result.L.LR;
                *input >> result.R.LR;
                this->PSTDDomains->push_back(result);
            }
        }
        else if(type == "DG_Vertices")
        {
            this->DGVertices->reserve(count);
            for (int i = 0; i < count; ++i)
            {
                Vector2f result;
                float x, y;
                *input >> x >> y;
                result << x, y;
                this->DGVertices->push_back(result);
            }

        }
        else if(type == "DG_indices")
        {
            this->DGIndices->reserve(count);
            for (int i = 0; i < count; ++i)
            {
                vector<int> result;
                int i1, i2, i3;
                *input >> i1 >> i2 >> i3;
                result.push_back(i1);
                result.push_back(i2);
                result.push_back(i3);
                this->DGIndices->push_back(result);
            }
        }
        else
        {
            throw ErrorInGeometryFileException();
        }
        *input >> end;
        if (end != "end")
            throw ErrorInGeometryFileException();
    }

}

OPENPSTD_SHARED_EXPORT const char* ErrorInGeometryFileException::what() const noexcept
{
    return "error";
}
