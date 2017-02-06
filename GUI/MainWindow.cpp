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
// Date: 18-07-2015
//
//
// Authors: M. R. Fortuin
//
//
//////////////////////////////////////////////////////////////////////////


#include "MainWindow.h"
#include "AboutBoxesText.h"
#include "ExportImage.h"
#include "AddReceiverSpeaker.h"
#include <QFileDialog>
#include "operations/FileOperations.h"
#include "operations/MouseOperations.h"
#include "operations/EditOperations.h"
#include "operations/SettingsOperations.h"
#include "operations/ViewOperations.h"
#include "operations/LambdaOperation.h"
#include "operations/long/LOperationOperation.h"
#include "operations/long/SimulateLOperation.h"
#include "mouse/MouseSelectStrategy.h"
#include "mouse/MouseMoveSceneStrategy.h"
#include "mouse/MouseCreateDomainStrategy.h"
#include "mouse/MouseCreateSpeakerReceiverStrategy.h"
#include <QMessageBox>

namespace OpenPSTD
{
    namespace GUI
    {
        MainWindow::MainWindow(std::weak_ptr<OperationRunner> operationRunner, QWidget *parent) :
                QMainWindow(parent),
                ui(new Ui_MainWindow()),
                operationRunner(operationRunner),
                domainProperties(new DomainProperties()),
                applicationSettings(std::make_shared<ApplicationSettings>())
        {
            ui->setupUi(this);

            //create status bar
            progressBar = new QProgressBar(ui->statusbar);
            progressBar->setAlignment(Qt::AlignRight);
            progressBar->setMaximumSize(180, 19);
            progressBar->setValue(0);
            progressBar->setVisible(false);

            statusbarLabel = new QLabel(ui->statusbar);
            statusbarLabel->setAlignment(Qt::AlignRight);
            statusbarLabel->setMaximumHeight(19);
            statusbarLabel->setVisible(false);

            statusbarLabelFrameNumber = new QLabel(ui->statusbar);
            statusbarLabel->setAlignment(Qt::AlignLeft);
            statusbarLabel->setMaximumHeight(19);
            statusbarLabel->setVisible(false);

            ui->statusbar->addWidget(progressBar);
            ui->statusbar->addWidget(statusbarLabel);
            ui->statusbar->addWidget(statusbarLabelFrameNumber);

            this->updateTimer = new QTimer(this);
            this->updateTimer->setInterval(100);
            this->updateTimer->setSingleShot(false);
            this->updateTimer->setTimerType(Qt::CoarseTimer);
            QObject::connect(this->updateTimer, &QTimer::timeout, this,
                             [&]() {
                                 //run an empty operation, so that the update will be executed
                                 this->operationRunner.lock()->RunOperation(
                                         std::make_shared<EmptyOperation>());
                             });


            ui->mainView->SetOperationRunner(this->operationRunner);

            MouseHandlersActions.push_back(ui->actionMove_scene);
            MouseHandlersActions.push_back(ui->actionAdd_Domain);
            MouseHandlersActions.push_back(ui->actionSelect);
            MouseHandlersActions.push_back(ui->actionAdd_Receiver);
            MouseHandlersActions.push_back(ui->actionAdd_speaker);

            ui->actionMove_scene->setChecked(true);

            QObject::connect(ui->actionAbout, &QAction::triggered, this, &MainWindow::ShowAbout);
            QObject::connect(ui->actionAbout_icons, &QAction::triggered, this, &MainWindow::ShowAboutIcons);

            QObject::connect(ui->actionNew, &QAction::triggered, this, &MainWindow::New);
            QObject::connect(ui->actionOpen, &QAction::triggered, this, &MainWindow::Open);
            QObject::connect(ui->actionSave, &QAction::triggered, this, &MainWindow::Save);
            QObject::connect(ui->actionImport_Geometry, &QAction::triggered, this, &MainWindow::ImportGeometry);
            QObject::connect(ui->actionExport_Image, &QAction::triggered, this, &MainWindow::ExportImage);
            QObject::connect(ui->actionExport_HDF5, &QAction::triggered, this, &MainWindow::ExportHDF5);
            QObject::connect(ui->actionMove_scene, &QAction::triggered, this,
                             [&](bool checked) {
                                 ChangeMouseHandler(ui->actionMove_scene,
                                                    std::unique_ptr<MouseMoveSceneStrategy>(
                                                            new MouseMoveSceneStrategy()));
                             });
            QObject::connect(ui->actionAdd_Domain, &QAction::triggered, this,
                             [&](bool checked) {
                                 ChangeMouseHandler(ui->actionAdd_Domain,
                                                    std::unique_ptr<MouseCreateDomainStrategy>(
                                                            new MouseCreateDomainStrategy()));
                             });
            QObject::connect(ui->actionSelect, &QAction::triggered, this,
                             [&](bool checked) {
                                 ChangeMouseHandler(ui->actionSelect,
                                                    std::unique_ptr<MouseSelectStrategy>(
                                                            new MouseSelectStrategy()));
                             });
            QObject::connect(ui->actionAdd_Receiver, &QAction::triggered, this,
                             [&](bool checked) {
                                 ChangeMouseHandler(ui->actionAdd_Receiver,
                                                    std::unique_ptr<MouseCreateSpeakerReceiverStrategy>(
                                                            new MouseCreateSpeakerReceiverStrategy(
                                                                    OBJECT_RECEIVER)));
                             });
            QObject::connect(ui->actionAdd_speaker, &QAction::triggered, this,
                             [&](bool checked) {
                                 ChangeMouseHandler(ui->actionAdd_speaker,
                                                    std::unique_ptr<MouseCreateSpeakerReceiverStrategy>(
                                                            new MouseCreateSpeakerReceiverStrategy(
                                                                    OBJECT_SPEAKER)));
                             });

            QObject::connect(ui->actionDelete_selected, &QAction::triggered, this,
                             [&](bool checked) {
                                 this->operationRunner.lock()->RunOperation(std::make_shared<RemoveSelectedObjectOperation>());
                             });
            QObject::connect(ui->actionStart_simulation, &QAction::triggered, this,
                             [&](bool checked) {
                                 //create simulate operation
                                 auto simulationOp = std::make_shared<SimulateLOperation>();
                                 //create operation to start a long operation
                                 auto startLOpOp = std::make_shared<StartLOperation>(simulationOp);
                                 //execute operation
                                 this->operationRunner.lock()->RunOperation(startLOpOp);
                             });
            QObject::connect(ui->actionStopAction, &QAction::triggered, this,
                             [&](bool checked) {
                                 this->operationRunner.lock()->RunOperation(std::make_shared<StopLOperation>());
                             });

            QObject::connect(ui->actionView_complete_scene, &QAction::triggered, this,
                             [&](bool checked) {
                                 this->operationRunner.lock()->RunOperation(std::make_shared<ViewWholeScene>());
                             });

            QObject::connect(ui->actionShow_grid, &QAction::triggered, this,
                             [&](bool checked) {
                                 std::shared_ptr<LambdaOperation> op = std::make_shared<LambdaOperation>([checked](const Reciever &reciever) {
                                     reciever.model->interactive->GridVisible = checked;
                                     reciever.model->interactive->Change();
                                 });
                                 this->operationRunner.lock()->RunOperation(op);

                             });


            QObject::connect(ui->actionEdit_properties_of_domain, &QAction::triggered, this,
                             &MainWindow::EditSelectedDomain);
            QObject::connect(ui->actionDocument_Settings, &QAction::triggered, this, &MainWindow::EditDocumentSettings);
            QObject::connect(ui->actionApplication_Settings, &QAction::triggered, this, &MainWindow::EditApplicationSettings);
            QObject::connect(ui->actionAdd_Receiver_Speaker, &QAction::triggered, this, &MainWindow::ExecuteAddReceiverSpeaker);
            QObject::connect(ui->hsbFrame, &QScrollBar::valueChanged, this, &MainWindow::hsbFrameChanged);
        }

        void MainWindow::UpdateFromModel(std::shared_ptr<Model> const &model, std::shared_ptr<BackgroundWorker> worker)
        {
            Shared::locking_ptr <Shared::PSTDFile> doc;
            if(model->documentAccess->IsDocumentLoaded())
            {
                doc = model->documentAccess->GetDocument();
                this->setWindowTitle(QString::fromStdString("OpenPSTD - " + model->documentAccess->GetFilename()));
            }
            else
                this->setWindowTitle(QString::fromStdString("OpenPSTD - No document loaded"));

            ui->mainView->UpdateFromModel(model);
            ui->mainView->update();

            applicationSettings->UpdateFromModel(model);
            this->UpdateDisableWidgets(model, worker);
            this->UpdateHsbFrame(model, worker);

            if(model->documentAccess->IsDocumentLoaded())
            {
                this->fileSettings = doc->GetSceneConf()->Settings;
                if (model->interactive->IsChanged() && model->interactive->Selection.Type == SELECTION_DOMAIN)
                {
                    auto conf = model->documentAccess->GetDocument()->GetSceneConf();
                    int i = model->interactive->Selection.SelectedIndex;
                    domainProperties->SetDomain(conf->Domains[i]);
                }
            }

            if(model->interactive->visibleFrame >= 0)
            {
                this->statusbarLabelFrameNumber->show();
                this->statusbarLabelFrameNumber->setText("Frame: " + QString::number(model->interactive->visibleFrame));
            }
            else
            {
                this->statusbarLabelFrameNumber->hide();
            }

            if(!worker->IsIdle() && 0 <= worker->GetCurrentProgress() && worker->GetCurrentProgress() <= 1)
            {
                this->progressBar->show();
                this->statusbarLabel->show();
                this->progressBar->setValue((int)(worker->GetCurrentProgress()*100));
                this->statusbarLabel->setText(QString::fromStdString(worker->GetCurrentName()));
            }
            else
            {
                this->progressBar->hide();
                this->statusbarLabel->hide();
            }

            this->updateTimer->start();
        }

        void MainWindow::New()
        {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Create PSTD file"), QString(),
                                                            tr("PSTD file (*.pstd)"));
            if (!fileName.isNull())
            {
                auto op = std::make_shared<NewFileOperation>(fileName.toStdString());
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::Open()
        {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open PSTD file"), QString(),
                                                            tr("PSTD file (*.pstd)"));
            if (!fileName.isNull())
            {
                auto op = std::make_shared<OpenFileOperation>(fileName.toStdString());
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::Save()
        {
            auto op = std::make_shared<SaveFileOperation>();
            this->operationRunner.lock()->RunOperation(op);
        }

        void MainWindow::ChangeMouseHandler(QAction *action, std::unique_ptr<MouseStrategy> mouseHandler)
        {
            for (int i = 0; i < this->MouseHandlersActions.size(); i++)
            {
                this->MouseHandlersActions[i]->setChecked(false);
            }
            action->setChecked(true);

            auto op = std::make_shared<ChangeMouseHandlerOperations>(std::move(mouseHandler));
            this->operationRunner.lock()->RunOperation(op);
        }

        void MainWindow::EditSelectedDomain()
        {
            if (this->domainProperties->exec() == QDialog::Accepted)
            {
                auto op = std::make_shared<EditSelectedDomainEdgesOperation>();
                op->AbsorptionT = this->domainProperties->AbsorptionT();
                op->AbsorptionB = this->domainProperties->AbsorptionB();
                op->AbsorptionL = this->domainProperties->AbsorptionL();
                op->AbsorptionR = this->domainProperties->AbsorptionR();
                op->LRT = this->domainProperties->LRT();
                op->LRB = this->domainProperties->LRB();
                op->LRL = this->domainProperties->LRL();
                op->LRR = this->domainProperties->LRR();
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::UpdateDisableWidgets(std::shared_ptr<Model> const &model, std::shared_ptr<BackgroundWorker> worker)
        {
            ui->actionSave->setEnabled(model->documentAccess->IsDocumentLoaded());
            ui->actionImport_Geometry->setEnabled(model->documentAccess->IsDocumentLoaded());
            ui->actionMove_scene->setEnabled(model->documentAccess->IsDocumentLoaded());
            ui->actionView_complete_scene->setEnabled(model->documentAccess->IsDocumentLoaded());

            ui->actionStopAction->setEnabled(!worker->IsIdle());

            bool documentEdit = worker->IsIdle() && model->documentAccess->IsDocumentLoaded();

            ui->actionAdd_Domain->setEnabled(documentEdit);
            ui->actionAdd_Receiver->setEnabled(documentEdit);
            ui->actionAdd_speaker->setEnabled(documentEdit);
            ui->actionSelect->setEnabled(documentEdit);
            ui->actionDocument_Settings->setEnabled(documentEdit);
            ui->actionStart_simulation->setEnabled(documentEdit);
            ui->actionExport_Image->setEnabled(documentEdit);
            ui->actionExport_HDF5->setEnabled(documentEdit);

            ui->actionDelete_selected->setEnabled(documentEdit && model->interactive->Selection.Type != SELECTION_NONE);
            ui->actionEdit_properties_of_domain->setEnabled(documentEdit && model->interactive->Selection.Type == SELECTION_DOMAIN);
            ui->actionResize_domain->setEnabled(documentEdit && model->interactive->Selection.Type == SELECTION_DOMAIN);
        }


        void MainWindow::UpdateHsbFrame(std::shared_ptr<Model> const &model, std::shared_ptr<BackgroundWorker> worker)
        {
            bool documentEdit = model->documentAccess->IsDocumentLoaded();
            if(documentEdit)
            {
                auto doc = model->documentAccess->GetDocument();
                bool anyFrame = false;
                int max = 0;
                int domains = doc->GetResultsDomainCount();
                int frameCount;

                for(int d = 0; d < domains; d++)
                {
                    frameCount = doc->GetResultsFrameCount(d);
                    anyFrame |= frameCount > 0;
                    max = std::max(max, frameCount-1);
                }

                frameCount = doc->GetResultsDGFrameCount();
                anyFrame |= frameCount > 0;
                max = std::max(max, frameCount-1);

                ui->hsbFrame->setEnabled(anyFrame);
                ui->hsbFrame->setMaximum(max);
                ui->hsbFrame->setMinimum(0);
                ui->hsbFrame->setValue(anyFrame?model->interactive->visibleFrame:0);
                this->maxFrame = max;
            }
            else
            {
                ui->hsbFrame->setEnabled(false);
            }
        }

        void MainWindow::EditDocumentSettings()
        {
            std::unique_ptr<DocumentSettings> documentSettings(new DocumentSettings());
            documentSettings->UpdateFromModel(this->fileSettings);
            if (documentSettings->exec() == QDialog::Accepted)
            {
                this->operationRunner.lock()->RunOperation(
                        std::make_shared<EditDocumentSettingsOperation>(documentSettings->GetResult()));
            }
        }

        void MainWindow::EditApplicationSettings()
        {
            if (this->applicationSettings->exec() == QDialog::Accepted)
            {
                this->operationRunner.lock()->RunOperation(
                        std::make_shared<UpdateSettingsOperation>(this->applicationSettings));
            }
        }

        void MainWindow::ShowAbout()
        {
            QMessageBox::about(this, "About OpenPSTD", QString::fromStdString(ABOUT_OPENPSTD));
        }

        void MainWindow::ShowAboutIcons()
        {
            QMessageBox::about(this, "About icons", QString::fromStdString(ABOUT_NOUN_ICONS));
        }

        void MainWindow::hsbFrameChanged(int value)
        {
            this->operationRunner.lock()->RunOperation(std::make_shared<ChangeViewingFrame>(value));
        }

        void MainWindow::ImportGeometry()
        {
            QString fileName = QFileDialog::getOpenFileName(this, tr("Open geometry file"), QString(),
                                                            tr("Geometry file (*.geo)"));
            if (!fileName.isNull())
            {
                auto op = std::make_shared<ImportGeometryOperation>(fileName.toStdString());
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::ExportHDF5()
        {
            QString fileName = QFileDialog::getSaveFileName(this, tr("Export to HDF5"), QString(),
                                                            tr("HDF5 file (*.h5)"));
            if (!fileName.isNull())
            {
                auto op = std::make_shared<ExportToHDF5Operation>(fileName.toStdString());
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::ExportImage()
        {
            std::unique_ptr<GUI::ExportImage> ui_exportImage(new GUI::ExportImage(maxFrame));
            if (ui_exportImage->exec() == QDialog::Accepted)
            {
                auto op = std::make_shared<ExportToImageOperation>(
                        ui_exportImage->GetDirectory(),
                        ui_exportImage->GetName(),
                        ui_exportImage->GetFormat());
                op->startFrame = ui_exportImage->GetStartFrame();
                op->endFrame = ui_exportImage->GetEndFrame();
                this->operationRunner.lock()->RunOperation(op);
            }
        }

        void MainWindow::ExecuteAddReceiverSpeaker()
        {
            std::unique_ptr<AddReceiverSpeaker> ui_add(new AddReceiverSpeaker());
            if (ui_add->exec() == QDialog::Accepted)
            {
                auto op = std::make_shared<CreateReceiverSpeakerOperation>(ui_add->GetOptions());
                this->operationRunner.lock()->RunOperation(op);
            }
        }


    }
}