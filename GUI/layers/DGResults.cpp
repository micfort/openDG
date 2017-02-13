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

#include "DGResults.h"

OpenPSTD::GUI::DGResults::DGResults() : Layer(), valuesInitialized(false)
{

}

void
OpenPSTD::GUI::DGResults::InitializeGL(QObject *context, std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    f->glGenBuffers(1, &this->positionsBuffer);
    f->glGenBuffers(1, &this->valuesBuffer);
    triangles = 0;

    std::unique_ptr<std::string> vertexFile = std::unique_ptr<std::string>(
            new std::string(":/GPU/DGResult.vert"));
    std::unique_ptr<std::string> fragmentFile = std::unique_ptr<std::string>(
            new std::string(":/GPU/DGResult.frag"));

    program = std::unique_ptr<QOpenGLShaderProgram>(new QOpenGLShaderProgram(nullptr));
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(*vertexFile));
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(*fragmentFile));
    program->link();
    GLError("DGResultsprogram->link");

    program->bind();
    GLError("DGResults program->bind");

    program->setUniformValue("v_log_min", -60.0f);
    GLError("DGResults program->setUniformValue");
}

void OpenPSTD::GUI::DGResults::PaintGL(QObject *context, std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    if(valuesInitialized)
    {
        program->bind();
        program->enableAttributeArray("a_position");
        program->enableAttributeArray("pressure");

        f->glBindBuffer(GL_ARRAY_BUFFER, this->positionsBuffer);
        GLError("DGResults f->glBindBuffer(this->positionsBuffer)");
        f->glVertexAttribPointer((GLuint) program->attributeLocation("a_position"), 2, GL_FLOAT, GL_FALSE, 0, 0);
        GLError("DGResults f->glVertexAttribPointer");

        f->glBindBuffer(GL_ARRAY_BUFFER, this->valuesBuffer);
        GLError("DGResults f->glBindBuffer(this->valuesBuffer)");
        f->glVertexAttribPointer((GLuint) program->attributeLocation("pressure"), 1, GL_FLOAT, GL_FALSE, 0, 0);
        GLError("DGResults f->glVertexAttribPointer");

        f->glDrawArrays(GL_TRIANGLES, 0, triangles * 3);
        GLError("DGResults f->glDrawArrays");

        program->disableAttributeArray("pressure");
        program->disableAttributeArray("a_position");
    }
}

void OpenPSTD::GUI::DGResults::UpdateScene(const std::shared_ptr<OpenPSTD::GUI::Model> &m,
                                           std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    program->bind();

    if(m->view->IsChanged())
    {
        program->setUniformValue("u_view", m->view->viewMatrix);
    }

    auto doc = m->documentAccess->GetDocument();

    if(m->interactive->visibleFrame >= 0 && m->interactive->visibleFrame < doc->GetResultsDGFrameCount())
    {
        if (m->documentAccess->IsChanged())
        {
            auto conf = doc->GetResultsSceneConf();

            std::vector<QVector2D> positions;
            positions.reserve(conf->DGIndices.size() * 3);
            MinMaxValue minMaxPos;

            for (int i = 0; i < conf->DGIndices.size(); ++i)
            {
                //create the 3 points
                QVector2D p1(conf->DGVertices[conf->DGIndices[i][0]](0),
                             conf->DGVertices[conf->DGIndices[i][0]](1));
                QVector2D p2(conf->DGVertices[conf->DGIndices[i][1]](0),
                             conf->DGVertices[conf->DGIndices[i][1]](1));
                QVector2D p3(conf->DGVertices[conf->DGIndices[i][2]](0),
                             conf->DGVertices[conf->DGIndices[i][2]](1));

                //update min max values
                minMaxPos = MinMaxValue::Combine(minMaxPos, MinMaxValue(p1, p2));

                //add to vector
                positions.push_back(p1);
                positions.push_back(p2);
                positions.push_back(p3);
            }
            triangles = conf->DGIndices.size();

            this->minMaxPos = minMaxPos;

            f->glBindBuffer(GL_ARRAY_BUFFER, this->positionsBuffer);
            f->glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(QVector2D), positions.data(), GL_STATIC_DRAW);
        }

        if (m->interactive->IsChanged())
        {
            Kernel::DG_FRAME_PTR frame = doc->GetResultsDGFrameCorner(m->interactive->visibleFrame);

            std::vector<float> values(frame->rows() * frame->cols());
            Eigen::Map<Kernel::DG_FRAME> map(values.data(), frame->rows(), frame->cols());

            map = *frame;

            f->glBindBuffer(GL_ARRAY_BUFFER, this->valuesBuffer);
            f->glBufferData(GL_ARRAY_BUFFER, values.size() * sizeof(float), values.data(), GL_DYNAMIC_DRAW);
            valuesInitialized = true;
        }
    }
}

OpenPSTD::GUI::MinMaxValue OpenPSTD::GUI::DGResults::GetMinMax()
{
    return this->minMaxPos;
}
