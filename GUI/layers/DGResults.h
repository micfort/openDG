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
// Date: 6-2-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef OPENPSTD_DGRESULTS_H
#define OPENPSTD_DGRESULTS_H

#include "GUI/Viewer2D.h"

namespace OpenPSTD
{
    namespace GUI
    {
        class DGResults : public Layer
        {
        private:
            std::unique_ptr<QOpenGLShaderProgram> program;
            unsigned int positionsBuffer;
            unsigned int valuesBuffer;
            int triangles;
            int i1, i2, i3;
            bool valuesInitialized;

            MinMaxValue minMaxPos;

            int GetClosest(QVector2D p, Kernel::VectorX<float> x, Kernel::VectorX<float> y);
        public:
            DGResults();

            void InitializeGL(QObject *context, std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f) override;

            void PaintGL(QObject *context, std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f) override;

            void UpdateScene(std::shared_ptr<Model> const &m,
                             std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f) override;

            MinMaxValue GetMinMax() override;
        };
    }
}


#endif //OPENPSTD_DGRESULTS_H
