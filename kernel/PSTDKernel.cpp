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
//      18-7-2015
//
// Authors:
//      Michiel Fortuijn
//      Omar  Richardson
//
//////////////////////////////////////////////////////////////////////////

#include <signal.h>
#include "PSTDKernel.h"


//-----------------------------------------------------------------------------
// interface of the kernel

PSTDKernel::PSTDKernel(std::shared_ptr<PSTDFileConfiguration> config) {
    Kernel::debug("Initialzing kernel");
    this->config = config;
    this->settings = std::make_shared<PSTDFileSettings>(config->Settings);
    Kernel::Scene scene(this->config);
    this->scene = std::make_shared<Kernel::Scene>(scene);
    this->initialize_scene();
    auto wnd = Kernel::WaveNumberDiscretizer();
    this->wnd = std::make_shared<Kernel::WaveNumberDiscretizer>(wnd);
    Kernel::debug("Finished initialzing kernel");
}


void PSTDKernel::initialize_scene() {
    Kernel::debug("Initialzing scene");
    this->add_domains();
    scene->add_pml_domains();
    this->add_speakers();
    this->add_receivers();
    scene->compute_rho_arrays();
    scene->compute_pml_matrices();
    Kernel::debug("Finished initializing");
}


void PSTDKernel::add_domains() {
    int domain_id_int = 0;
    std::vector<std::shared_ptr<Kernel::Domain>> domains;
    for (auto domain: this->config->Domains) {
        Kernel::debug("Initializing domain " + std::to_string(domain_id_int));
        std::vector<float> tl = scale_to_grid(domain.TopLeft);
        std::vector<float> s = scale_to_grid(domain.Size);
        std::shared_ptr<Kernel::Point> grid_top_left = std::make_shared<Kernel::Point>((int) tl.at(0), (int) tl.at(1));
        std::shared_ptr<Kernel::Point> grid_size = std::make_shared<Kernel::Point>((int) s.at(0), (int) s.at(1));
        std::map<Kernel::Direction, Kernel::EdgeParameters> edge_param_map = translate_edge_parameters(domain);
        std::string domain_id = "Domain" + std::to_string(domain_id_int);
        std::shared_ptr<Kernel::Domain> domain_ptr(
                new Kernel::Domain(this->settings, domain_id, default_alpha, grid_top_left,
                                   grid_size, false, this->wnd, edge_param_map, nullptr));
        domains.push_back(domain_ptr);
        domain_id_int++;
    }
    for (auto domain: domains) {
        domain->post_initialization();
        scene->add_domain(domain);
    }
}


void PSTDKernel::add_speakers() {
    //Inconsistent: We created domains in this class, and speakers in the scene class
    for (auto speaker: this->config->Speakers) {
        std::vector<float> location = scale_to_grid(speaker);
        Kernel::debug(
                "Initialzing Speaker (" + std::to_string(location.at(0)) + ", " + std::to_string(location.at(1)) + ")");
        this->scene->add_speaker(location.at(0), location.at(1), 0); // Z-coordinate is 0
    }
}

void PSTDKernel::add_receivers() {
    //Inconsistent: We created domains in this class, and receivers in the scene class
    for (auto receiver: this->config->Receivers) {
        std::vector<float> location = scale_to_grid(receiver);
        this->scene->add_receiver(location.at(0), location.at(1), 0);
    }
}

void PSTDKernel::run(KernelCallback *callback) {
    int solver_num = this->config->Settings.GetGPUAccel() + (this->config->Settings.GetMultiThread() << 1);
    std::shared_ptr<Kernel::Solver> solver;
    switch (solver_num) {
        case 0:
            solver = std::shared_ptr<Kernel::Solver>(new Kernel::SingleThreadSolver(this->scene, callback));
            break;
        case 1:
            solver = std::shared_ptr<Kernel::Solver>(new Kernel::GPUSingleThreadSolver(this->scene, callback));
            break;
        case 2:
            solver = std::shared_ptr<Kernel::Solver>(new Kernel::MultiThreadSolver(this->scene, callback));
            break;
        case 3:
            solver = std::shared_ptr<Kernel::Solver>(new Kernel::GPUMultiThreadSolver(this->scene, callback));
            break;
        default:
            //Raise Error
            break;
    }
    solver->compute_propagation();
}

std::vector<std::vector<int>> PSTDKernel::GetDomainMetadata() {

}


std::vector<float> PSTDKernel::scale_to_grid(QVector2D world_vector) {
    QVector2D scaled_vector = world_vector / this->settings->GetGridSpacing();
    return std::vector<float>{scaled_vector[0], scaled_vector[1]};
}

std::vector<float> PSTDKernel::scale_to_grid(QVector3D world_vector) {
    //Not yet adapted to 3D.
    QVector3D scaled_vector = world_vector / this->settings->GetGridSpacing();
    return std::vector<float>{scaled_vector[0], scaled_vector[1]};
}

std::map<Kernel::Direction, Kernel::EdgeParameters> PSTDKernel::translate_edge_parameters(Domain domain) {
    std::map<Kernel::Direction, Kernel::EdgeParameters> edge_parameters;
    edge_parameters[Kernel::Direction::LEFT] = {domain.L.LR, domain.L.Absorption};
    edge_parameters[Kernel::Direction::RIGHT] = {domain.R.LR, domain.R.Absorption};
    edge_parameters[Kernel::Direction::BOTTOM] = {domain.B.LR, domain.B.Absorption};
    edge_parameters[Kernel::Direction::TOP] = {domain.T.LR, domain.T.Absorption};
    return edge_parameters;
}

std::vector<int> PSTDKernel::round_off(std::vector<float> vector) {
    assert(vector.size() == 2); // We don't need to be very general here.
    return std::vector<int>{(int) vector.at(0), (int) vector.at(1)};
}
