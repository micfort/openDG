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
// Date: 23-1-2017
//
//
// Authors: M. R. Fortuin
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#ifdef STAND_ALONE
#   define BOOST_TEST_MODULE Main
#endif

#include <boost/test/unit_test.hpp>
#include <iostream>
#include <shared/GeometryImport.h>

BOOST_AUTO_TEST_SUITE(Shared)
    BOOST_AUTO_TEST_SUITE(Shared_GeometryImport)

        BOOST_AUTO_TEST_CASE(Small_test)
        {
            using namespace OpenPSTD::Shared;

            GeometryImport import(std::unique_ptr<std::istringstream>(
                    new std::istringstream("start DG_Vertices 9\n"
                                                   "\t-1.0000000000000000e+00 -1.0000000000000000e+00\n"
                                                   "\t+1.0000000000000000e+00 -1.0000000000000000e+00\n"
                                                   "\t+0.0000000000000000e+00 -1.0000000000000000e+00\n"
                                                   "\t+1.0000000000000000e+00 +1.0000000000000000e+00\n"
                                                   "\t+1.0000000000000000e+00 +0.0000000000000000e+00\n"
                                                   "\t-1.0000000000000000e+00 +1.0000000000000000e+00\n"
                                                   "\t+0.0000000000000000e+00 +1.0000000000000000e+00\n"
                                                   "\t-1.0000000000000000e+00 +0.0000000000000000e+00\n"
                                                   "\t-1.6397527043499999e-01 -1.6397527043499999e-01\n"
                                                   "end\n"
                                                   "start DG_indices 8\n"
                                                   "\t7 0 8\n"
                                                   "\t8 0 2\n"
                                                   "\t6 5 7\n"
                                                   "\t3 6 4\n"
                                                   "\t1 4 2\n"
                                                   "\t6 7 8\n"
                                                   "\t4 6 8\n"
                                                   "\t2 4 8\n"
                                                   "end")));

            BOOST_CHECK_EQUAL(import.DGVertices->size(), 9);
            BOOST_CHECK_EQUAL(import.DGIndices->size(), 8);

			double epsilon = 1e-5;
			
            int i = 0;
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), -1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), -1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), +1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), -1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(),  0, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), -1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), +1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), +1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), +1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(),  0, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), -1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), +1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(),  0, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), +1, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), -1, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(),  0, epsilon);
            BOOST_CHECK_CLOSE((*import.DGVertices)[i].x(), -1.6397527043499999e-01, epsilon); BOOST_CHECK_CLOSE((*import.DGVertices)[i++].y(), -1.6397527043499999e-01, epsilon);

            i = 0;
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 7); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 0); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 8);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 8); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 0); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 2);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 6); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 5); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 7);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 6); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 4);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 1); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 4); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 2);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 6); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 7); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 8);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 4); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 6); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 8);
            BOOST_CHECK_EQUAL((*import.DGIndices)[i].size(), 3); BOOST_CHECK_EQUAL((*import.DGIndices)[i][0], 2); BOOST_CHECK_EQUAL((*import.DGIndices)[i][1], 4); BOOST_CHECK_EQUAL((*import.DGIndices)[i++][2], 8);

        }
    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()
