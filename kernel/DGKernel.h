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
// Date: 17-1-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose: A Kernel implemenation that uses DG to solve the the problem.
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef OPENPSTD_DGKERNEL_H
#define OPENPSTD_DGKERNEL_H

#include "KernelInterface.h"
#include "DG/DG2D.h"
#include "DG/RK.h"

namespace OpenPSTD
{
    namespace Kernel
    {
        class DGKernel : public KernelInterface, public DG::OutputInterface<float>,
                         public std::enable_shared_from_this<DGKernel>
        {
        private:
            std::shared_ptr<DG::System2D<float>> system;
            std::shared_ptr<DG::RK<float>> RK;
            float renderTime;
            OpenPSTD::Kernel::SimulationMetadata metadata;

            std::shared_ptr<OpenPSTD::Kernel::KernelCallback> callback;
        public:
            void initialize_kernel(std::shared_ptr<PSTDConfiguration> config,
                                   std::shared_ptr<KernelCallbackLog> callbackLog) override;

            void run(std::shared_ptr<KernelCallback> callback) override;

            SimulationMetadata get_metadata() override;

            void WriteMetadata(std::string name, MatrixX<float> data) override;

            void WriteData(int name, int index, MatrixX<float> state) override;
        };
    }
}


#endif //OPENPSTD_DGKERNEL_H
