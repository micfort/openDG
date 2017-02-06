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
// Date: 2-2-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#include "DGTriangleLayer.h"

OpenPSTD::GUI::DGTriangleLayer::DGTriangleLayer() : Layer()
{

}

void OpenPSTD::GUI::DGTriangleLayer::InitializeGL(QObject *context,
                                                  std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    f->glGenBuffers(1, &this->positionsBuffer);
    lines = 0;

    std::unique_ptr<std::string> vertexFile = std::unique_ptr<std::string>(
            new std::string(":/GPU/PassPosition.vert"));
    std::unique_ptr<std::string> fragmentFile = std::unique_ptr<std::string>(
            new std::string(":/GPU/FixedColor.frag"));
    std::unique_ptr<std::string> geometricFile = std::unique_ptr<std::string>(
            new std::string(":/GPU/Line.geom"));

    program = std::unique_ptr<QOpenGLShaderProgram>(new QOpenGLShaderProgram(nullptr));
    program->addShaderFromSourceFile(QOpenGLShader::Vertex, QString::fromStdString(*vertexFile));
    program->addShaderFromSourceFile(QOpenGLShader::Fragment, QString::fromStdString(*fragmentFile));
    program->addShaderFromSourceFile(QOpenGLShader::Geometry, QString::fromStdString(*geometricFile));
    program->link();

    program->bind();

    QColor color(255, 255, 255, 255);
    program->setUniformValue("u_color", color);
    program->setUniformValue("thickness", 0.01f);
    GLError("DGTriangleLayer program->setUniformValue");
}

void
OpenPSTD::GUI::DGTriangleLayer::PaintGL(QObject *context, std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    program->bind();
    program->enableAttributeArray("a_position");

    f->glBindBuffer(GL_ARRAY_BUFFER, this->positionsBuffer);
    GLError("DGTriangleLayer f->glBindBuffer");
    f->glVertexAttribPointer((GLuint) program->attributeLocation("a_position"), 2, GL_FLOAT, GL_FALSE, 0, 0);
    GLError("DGTriangleLayer f->glVertexAttribPointer");
    f->glDrawArrays(GL_LINES, 0, lines * 2);
    GLError("DGTriangleLayer f->glDrawArrays");

    program->disableAttributeArray("a_position");
}

void OpenPSTD::GUI::DGTriangleLayer::UpdateScene(const std::shared_ptr<OpenPSTD::GUI::Model> &m,
                                                 std::unique_ptr<QOpenGLFunctions, void (*)(void *)> const &f)
{
    program->bind();

    if(m->view->IsChanged())
    {
        this->viewMatrix = m->view->viewMatrix;
        program->setUniformValue("u_view", m->view->viewMatrix);
    }

    if (m->documentAccess->IsChanged())
    {
        auto doc = m->documentAccess->GetDocument();
        auto conf = doc->GetSceneConf();

        std::vector<QVector2D> positions;
        //*3*2*2 -> every element exist from 3 points(assumption that they are triangles) and every edge has 2 points
        positions.reserve(conf->DGIndices.size()*3*2);
        MinMaxValue minMaxPos;

        lines = 0;

        for (int i = 0; i < conf->DGIndices.size(); ++i)
        {
            auto elementSize = conf->DGIndices[i].size();
            for (int j = 0; j < elementSize; ++j)
            {
                //create the 2 points
                QVector2D p1(conf->DGVertices[conf->DGIndices[i][j]](0), conf->DGVertices[conf->DGIndices[i][j]](1));
                QVector2D p2(conf->DGVertices[conf->DGIndices[i][(j+1)%elementSize]](0), conf->DGVertices[conf->DGIndices[i][(j+1)%elementSize]](1));

                //update min max values
                minMaxPos = MinMaxValue::Combine(minMaxPos, MinMaxValue(p1, p2));

                //add to vector
                positions.push_back(p1);
                positions.push_back(p2);
                lines++;
            }
        }

        this->minMaxPos = minMaxPos;

        f->glBindBuffer(GL_ARRAY_BUFFER, this->positionsBuffer);
        f->glBufferData(GL_ARRAY_BUFFER, positions.size() * sizeof(QVector2D), positions.data(),
                        GL_DYNAMIC_DRAW);
    }

    if (m->IsChanged())
    {
        program->bind();
        program->setUniformValue("u_color", m->colorScheme->EditorDGTriangleColor());
    }
}

OpenPSTD::GUI::MinMaxValue OpenPSTD::GUI::DGTriangleLayer::GetMinMax()
{
    return this->minMaxPos;
}
