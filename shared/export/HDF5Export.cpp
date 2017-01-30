//
// Created by michiel on 24-2-2016.
//

#include "HDF5Export.h"
#include "kernel/PSTDKernel.h"

#include <hdf5.h>
#include <hdf5_hl.h>

#include <boost/lexical_cast.hpp>

namespace OpenPSTD
{
    namespace Shared
    {
        std::vector<hsize_t> getSize(unsigned long long rows, unsigned long long cols);

        OPENPSTD_SHARED_EXPORT void HDF5::ExportData(std::string format, std::shared_ptr <PSTDFile> file, std::string output,
                              std::vector<int> domains, int startFrame, int endFrame)
        {
            hid_t file_id;

            //create file
            file_id = H5Fcreate(output.c_str(), H5F_ACC_TRUNC, H5P_DEFAULT, H5P_DEFAULT);

            if (domains.size() == 0)
            {
                int domainCount = file->GetResultsDomainCount();

                for (int d = 0; d < domainCount; ++d)
                {
                    domains.push_back(d);
                }
            }

            ExportPSTDData(file_id, file, domains, startFrame, endFrame);
            ExportReceiverData(file_id, file, startFrame, endFrame);
            ExportDGData(file_id, file, startFrame, endFrame);
            ExportGeneral(file_id, file);

            /* close file */
            H5Fclose (file_id);
        }

        void HDF5::ExportPSTDData(int file_id, std::shared_ptr<PSTDFile> file, std::vector<int> domains, int startFrame, int endFrame)
        {
            Kernel::PSTDKernel k(false, false);
            k.initialize_kernel(file->GetSceneConf(), std::make_shared<OpenPSTD::Kernel::KernelCallbackLog>());
            auto metadata = k.get_metadata();

            hid_t frame_dir_id = H5Gcreate2(file_id, "/PSTD", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            for(int d : domains)
            {
                std::string domainLoc = "/PSTD/" + boost::lexical_cast<std::string>(d);
                hid_t frame_index_id = H5Gcreate2(file_id, domainLoc.c_str(), H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

                int domain_startframe = startFrame > -1?startFrame:0;
                int domain_endFrame = endFrame > -1?endFrame:file->GetResultsFrameCount(d) - 1;

                for (int f = domain_startframe; f <= domain_endFrame; ++f)
                {
                    std::string location = domainLoc + "/" + boost::lexical_cast<std::string>(f);

                    std::vector<hsize_t> size;
                    size.push_back(metadata.DomainMetadata[d][0]);
                    size.push_back(metadata.DomainMetadata[d][1]);

                    //get data and write to file
                    auto data = file->GetResultsFrame(f, d);
                    H5LTmake_dataset(file_id, location.c_str(), 2, size.data(), H5T_NATIVE_FLOAT, data->data());
                }

                H5Gclose(frame_index_id);
            }

            H5Gclose(frame_dir_id);
        }

        void HDF5::ExportReceiverData(int file_id, std::shared_ptr<PSTDFile> file, int startFrame, int endFrame)
        {
            hid_t receiver_dir_id = H5Gcreate2(file_id, "/receiver", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            int receiverCount = file->GetResultsReceiverCount();
            for(int r = 0; r < receiverCount; r++)
            {
                std::string receiverLoc = "/receiver/" + boost::lexical_cast<std::string>(r);
                auto data = file->GetReceiverData(r);

                std::vector<hsize_t> size;
                size.push_back(data->size());

                H5LTmake_dataset(file_id, receiverLoc.c_str(), 1, size.data(), H5T_NATIVE_FLOAT, data->data());
            }

            H5Gclose(receiver_dir_id);
        }

        void HDF5::ExportDGData(int file_id, std::shared_ptr<PSTDFile> file, int startFrame, int endFrame)
        {
            int dg_startframe = startFrame > -1?startFrame:0;
            int dg_endFrame = endFrame > -1?endFrame:file->GetResultsDGFrameCount() - 1;

            hid_t frame_dir_id = H5Gcreate2(file_id, "/DG", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            std::string xlocation = "/DG/X";
            std::string ylocation = "/DG/Y";

            //get data and write to file
            Kernel::DG_FRAME_PTR X = file->GetDGXPositions();
            Kernel::DG_FRAME_PTR Y = file->GetDGYPositions();

            std::cout << *X << std::endl;

            std::vector<Kernel::DG_FRAME_UNIT> xData(X->rows() * X->cols());
            std::vector<Kernel::DG_FRAME_UNIT> yData(Y->rows() * Y->cols());
            Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> xMap(xData.data(), X->rows(), X->cols());
            Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> yMap(yData.data(), Y->rows(), Y->cols());
            xMap = *X;
            yMap = *Y;

            std::vector<hsize_t> size = getSize(X->rows(), X->cols());

            H5LTmake_dataset(file_id, xlocation.c_str(), 2, size.data(), H5T_NATIVE_FLOAT, xData.data());
            H5LTmake_dataset(file_id, ylocation.c_str(), 2, size.data(), H5T_NATIVE_FLOAT, yData.data());

            for (int f = dg_startframe; f <= dg_endFrame; ++f)
            {
                std::string location = "/DG/" + boost::lexical_cast<std::string>(f);

                //get data and write to file
                Kernel::DG_FRAME_PTR frame = file->GetResultsDGFrame(f);

                std::vector<Kernel::DG_FRAME_UNIT> data(frame->rows() * frame->cols());
                Eigen::Map<Eigen::Matrix<float, Eigen::Dynamic, Eigen::Dynamic, Eigen::RowMajor>> map(data.data(), frame->rows(), frame->cols());
                map = *frame;

                H5LTmake_dataset(file_id, location.c_str(), 2, size.data(), H5T_NATIVE_FLOAT, data.data());
            }

            H5Gclose(frame_dir_id);
        }


        void SaveVariable(hid_t file_id, std::string name, float value)
        {
            std::string loc = "/Settings/" + name;
            std::vector<hsize_t> size;
            size.push_back(1);
            H5LTmake_dataset(file_id, loc.c_str(), 1, size.data(), H5T_NATIVE_FLOAT, &value);
        }

        void SaveVariable(hid_t file_id, std::string name, int value)
        {
            std::string loc = "/Settings/" + name;
            std::vector<hsize_t> size;
            size.push_back(1);
            H5LTmake_dataset(file_id, loc.c_str(), 1, size.data(), H5T_NATIVE_INT, &value);
        }

        void SaveVariable(hid_t file_id, std::string name, bool value)
        {
            hbool_t v2 = value;

            std::string loc = "/Settings/" + name;
            std::vector<hsize_t> size;
            size.push_back(1);
            H5LTmake_dataset(file_id, loc.c_str(), 1, size.data(), H5T_NATIVE_HBOOL, &v2);
        }

        void HDF5::ExportGeneral(int file_id, std::shared_ptr<PSTDFile> file)
        {
            auto conf = file->GetResultsSceneConf();

            hid_t frame_dir_id = H5Gcreate2(file_id, "/Settings", H5P_DEFAULT, H5P_DEFAULT, H5P_DEFAULT);

            SaveVariable(file_id, "RenderTime", conf->Settings.GetRenderTime());
            SaveVariable(file_id, "SoundSpeed", conf->Settings.GetSoundSpeed());
            SaveVariable(file_id, "AttenuationOfPMLCells", conf->Settings.GetAttenuationOfPMLCells());
            SaveVariable(file_id, "MaxFrequency", conf->Settings.GetMaxFrequency());
            SaveVariable(file_id, "DensityOfAir", conf->Settings.GetDensityOfAir());
            SaveVariable(file_id, "PatchError", conf->Settings.GetPatchError());
            SaveVariable(file_id, "FactRK", conf->Settings.GetFactRK());
            SaveVariable(file_id, "GridSpacing", conf->Settings.GetGridSpacing());
            SaveVariable(file_id, "BandWidth", conf->Settings.GetBandWidth());
            SaveVariable(file_id, "WaveLength", conf->Settings.GetWaveLength());
            SaveVariable(file_id, "SpectralInterpolation", conf->Settings.GetSpectralInterpolation());
            SaveVariable(file_id, "PMLCells", conf->Settings.GetPMLCells());

            H5Gclose(frame_dir_id);
        }

        std::vector<hsize_t> getSize(unsigned long long rows, unsigned long long cols)
        {
            std::vector<hsize_t> size;
            size.push_back(cols);
            size.push_back(rows);
            return size;
        }
    }
}