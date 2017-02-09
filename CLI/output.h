//
// Created by michiel on 24-1-2016.
//

#ifndef OPENPSTD_OUTPUT_CLI_H
#define OPENPSTD_OUTPUT_CLI_H

#include <shared/PSTDFile.h>
namespace OpenPSTD
{
    namespace CLI
    {
        class CLIOutput : public Kernel::KernelCallback
        {
        private:
            std::shared_ptr<Shared::PSTDFile> _file;
            bool _debugInfo;
        public:
            CLIOutput(std::shared_ptr<Shared::PSTDFile> file, bool debugInfo) : _file(file), _debugInfo(debugInfo)
            { };

            virtual void Callback(Kernel::CALLBACKSTATUS status, std::string message, int frame) override;

            virtual void WriteFrame(int frame, int domain, Kernel::PSTD_FRAME_PTR data) override;

            virtual void WriteSample(int startSample, int receiver, std::vector<float> data) override;

            void WriteDGFrame(int frame, Kernel::DG_FRAME_PTR data, Kernel::DG_FRAME_PTR cornerData) override;

            virtual void Fatal(std::string message) override;

            virtual void Error(std::string message) override;

            virtual void Warning(std::string message) override;

            virtual void Info(std::string message) override;

            virtual void Debug(std::string message) override;
        };
    }
}
#endif //OPENPSTD_OUTPUT_CLI_H
