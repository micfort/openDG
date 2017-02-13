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
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#include "DGKernel.h"
#include "DG/DG2DBuilders.h"
#include "DG/LEE2D.h"
#include <boost/lexical_cast.hpp>

using namespace OpenPSTD::Kernel::DG;

void OpenPSTD::Kernel::DGKernel::initialize_kernel(std::shared_ptr<OpenPSTD::Kernel::PSTDConfiguration> config,
                                                   std::shared_ptr<OpenPSTD::Kernel::KernelCallbackLog> callbackLog)
{
    callbackLog->Info("Create DE");
    std::shared_ptr<LinearizedEulerEquationsDE2D<float>> DE = std::make_shared<LinearizedEulerEquationsDE2D<float>>(
            config->Settings.GetSoundSpeed(), config->Settings.GetDensityOfAir());

    callbackLog->Info("Build DG system");
    SimpleDG2DBuilder<float> builder;
    builder.Elements = config->DGIndices;
    builder.Vertices = config->DGVertices;
    this->system = builder.Build(config->Settings.GetDGOrder(), DE); //if the order is changed, in WriteData the corner data also changes!!!!

    callbackLog->Info("Initialize RK");
    this->RK = std::make_shared<LSERK<float>>();
    this->RK->SetBB(this->system);
    this->RK->SetOutput(this->shared_from_this());
    this->renderTime = config->Settings.GetRenderTime();

    callbackLog->Info("Simulation system initialized");
}

void OpenPSTD::Kernel::DGKernel::run(std::shared_ptr<OpenPSTD::Kernel::KernelCallback> callback)
{
    if(!this->system)
        throw KernelNotConfiguredException();
    this->callback = callback;
    this->RK->Calculate(this->renderTime);
}

OpenPSTD::Kernel::SimulationMetadata OpenPSTD::Kernel::DGKernel::get_metadata()
{
    if(!this->system)
        throw KernelNotConfiguredException();
    //populate this->metadata
    auto output = this->shared_from_this();
    this->system->OutputMatlabMetadata(output);
    this->metadata.Framecount = this->RK->GetTimeStepCount(this->renderTime);
    return this->metadata;
}

void OpenPSTD::Kernel::DGKernel::WriteMetadata(std::string name, MatrixX<float> data)
{
    if(name == "X")
    {
        this->metadata.DGXPositions = data;
    }
    else if(name == "Y")
    {
        this->metadata.DGYPositions = data;
    }
}

void OpenPSTD::Kernel::DGKernel::WriteData(int name, int index, MatrixX<float> state)
{
    if(name == DG::LinearizedEulerEquationsDE2D<float>::IndexPX)
    {
        _pxTemp = state;
    }
    else if(name == DG::LinearizedEulerEquationsDE2D<float>::IndexPY)
    {
        callback->Info("Calculated frame " + boost::lexical_cast<std::string>(index));
        DG_FRAME_PTR data = std::make_shared<DG_FRAME>(state.rows(), state.cols());
        *data = state+_pxTemp;

        //gets only the corners data
        DG_FRAME_PTR dataCorner = std::make_shared<DG_FRAME>(3, data->cols());
        dataCorner->row(0) = data->row(0);
        dataCorner->row(1) = data->row(6);
        dataCorner->row(2) = data->row(27);

        this->callback->WriteDGFrame(index, data, dataCorner);
    }

}
