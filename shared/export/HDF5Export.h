//
// Created by michiel on 24-2-2016.
//

#ifndef OPENPSTD_HDF5_H
#define OPENPSTD_HDF5_H

#include "openpstd-shared_export.h"
#include <shared/PSTDFile.h>

namespace OpenPSTD
{
    namespace Shared
    {
        class OPENPSTD_SHARED_EXPORT HDF5
        {
        private:
            void ExportPSTDData(int file_id, std::shared_ptr<PSTDFile> file, std::vector<int> domains, int startFrame, int endFrame);
            void ExportDGData(int file_id, std::shared_ptr<PSTDFile> file, int startFrame, int endFrame);
            void ExportReceiverData(int file_id, std::shared_ptr<PSTDFile> file, int startFrame, int endFrame);
            void ExportGeneral(int file_id, std::shared_ptr<PSTDFile> file);

        public:
            OPENPSTD_SHARED_EXPORT virtual void ExportData(std::string format, std::shared_ptr<PSTDFile> file, std::string output,
                                    std::vector<int> domains, int startFrame, int endFrame);
        };
    }
}


#endif //OPENPSTD_HDF5_H
