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
// Date: 19-1-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose: this file is used to serialize matrices to boost archives
//
//
//////////////////////////////////////////////////////////////////////////

#ifndef OPENPSTD_EIGENMATRIXSERIALIZATION_H
#define OPENPSTD_EIGENMATRIXSERIALIZATION_H

friend class boost::serialization::access;
template<class Archive>
void save(Archive & ar, const unsigned int version) const {
  derived().eval();
  const Index rows = derived().rows(), cols = derived().cols();
  ar & rows;
  ar & cols;
  for (Index j = 0; j < cols; ++j )
    for (Index i = 0; i < rows; ++i )
      ar & derived().coeff(i, j);
}

template<class Archive>
void load(Archive & ar, const unsigned int version) {
  Index rows, cols;
  ar & rows;
  ar & cols;
  if (rows != derived().rows() || cols != derived().cols() )
    derived().resize(rows, cols);
  ar & boost::serialization::make_array(derived().data(), derived().size());
}

template<class Archive>
void serialize(Archive & ar, const unsigned int file_version) {
  boost::serialization::split_member(ar, *this, file_version);
}

#endif //OPENPSTD_EIGENMATRIXSERIALIZATION_H
