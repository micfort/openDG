//
// Created by michiel on 21-3-2016.
//

#ifndef OPENPSTD_PSTDFILEACCESS_H
#define OPENPSTD_PSTDFILEACCESS_H

#include "openpstd-shared_export.h"
#include "PSTDFile.h"
#include <memory>
#include <string>
#include <boost/filesystem.hpp>
#include "locking_ptr.h"

namespace OpenPSTD
{
    namespace Shared
    {
        class OPENPSTD_SHARED_EXPORT PSTDFileAccessInUseException : public std::exception
        {
        public:
            OPENPSTD_SHARED_EXPORT const char *what() const noexcept override;
        };

        class OPENPSTD_SHARED_EXPORT PSTDFileAccess: public InvalidationData
        {
        private:
            std::shared_ptr<PSTDFile> d;
            boost::filesystem::path realPath;
            std::shared_ptr<boost::recursive_mutex> mutex;

        public:
            OPENPSTD_SHARED_EXPORT PSTDFileAccess();
            OPENPSTD_SHARED_EXPORT ~PSTDFileAccess();

            OPENPSTD_SHARED_EXPORT locking_ptr<PSTDFile> GetDocument();

            OPENPSTD_SHARED_EXPORT void New(boost::filesystem::path filename);

            OPENPSTD_SHARED_EXPORT void Open(boost::filesystem::path filename);

            OPENPSTD_SHARED_EXPORT void Save();

            OPENPSTD_SHARED_EXPORT void SaveAs(boost::filesystem::path filename);

            OPENPSTD_SHARED_EXPORT void Close();

            OPENPSTD_SHARED_EXPORT virtual bool IsChanged() override;

            OPENPSTD_SHARED_EXPORT virtual void Reset() override;

            OPENPSTD_SHARED_EXPORT bool IsDocumentLoaded();

            OPENPSTD_SHARED_EXPORT std::string GetFilename();
        };
    }
}

#endif //OPENPSTD_PSTDFILEACCESS_H
