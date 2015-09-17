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
//
//
// Authors:
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

//
// Created by michiel on 31-8-2015.
//

#ifndef OPENPSTD_SELECTDOMAINOPERATION_H
#define OPENPSTD_SELECTDOMAINOPERATION_H

#include "BaseOperation.h"

class SelectIndexedObjectOperation : public BaseOperation
{
private:
    SelectionType type;
    int index;
public:
    SelectIndexedObjectOperation(SelectionType type, int index);

    virtual void Run(const Reciever &reciever) override;
};

class SelectDomainOperation : public SelectIndexedObjectOperation
{
public:
    SelectDomainOperation(int selectDomainIndex);
};

class DeselectDomainOperation : public SelectIndexedObjectOperation
{
public:
    DeselectDomainOperation();
};

class SelectObjectOperation: public BaseOperation
{
private:
    QVector2D ScreenPosition;
public:
    SelectObjectOperation(QVector2D ScreenPosition);

    virtual void Run(const Reciever &reciever) override;
};


#endif //OPENPSTD_SELECTDOMAINOPERATION_H
