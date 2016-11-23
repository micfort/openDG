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
// Date: 22-11-2016
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
#include <kernel/DG/DG2D.h>
#include <kernel/DG/RK.h>

#include <iostream>

using namespace OpenPSTD::Kernel::DG;
using namespace std;
using namespace Eigen;

BOOST_AUTO_TEST_SUITE(DG)
    BOOST_AUTO_TEST_SUITE(DG_LEE_2D)

        BOOST_AUTO_TEST_CASE(DG_LEE_p_start)
        {
            int K = 58;
            int N = 4;
            MatrixX<double> pExpected(N+1,K);
            pExpected <<
                      0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000009	,	0.000000000000211	,	0.000000000004196	,	0.000000000071093	,	0.000000001024741	,	0.000000012565289	,	0.000000131069417	,	0.000001163056115	,	0.000008779512319	,	0.000056378113316	,	0.000307979001018	,	0.001431205827213	,	0.005657877077737	,	0.019027220097393	,	0.054433667749669	,	0.132473886108031	,	0.274260571689522	,	0.483021986324738	,	0.723670458356205	,	0.922327613321088	,	1.000000000000000	,	0.922327613321087	,	0.723670458356207	,	0.483021986324738	,	0.274260571689522	,	0.132473886108031	,	0.054433667749669	,	0.019027220097393	,	0.005657877077737	,	0.001431205827213	,	0.000307979001018	,	0.000056378113316	,	0.000008779512319	,	0.000001163056115	,	0.000000131069417	,	0.000000012565289	,	0.000000001024741	,	0.000000000071093	,	0.000000000004196	,	0.000000000000211	,	0.000000000000009	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,
                    0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000001	,	0.000000000000016	,	0.000000000000357	,	0.000000000006919	,	0.000000000114008	,	0.000000001598068	,	0.000000019055790	,	0.000000193298762	,	0.000001668021372	,	0.000012244599110	,	0.000076464165467	,	0.000406201719294	,	0.001835675804636	,	0.007057008364691	,	0.023078931750230	,	0.064206825124425	,	0.151955740231385	,	0.305930972671621	,	0.523962501181356	,	0.763391619310985	,	0.946160887586890	,	0.997592135400629	,	0.894770102422755	,	0.682716397693998	,	0.443138645431393	,	0.244686123044255	,	0.114934252555233	,	0.045926149376506	,	0.015611369907454	,	0.004514320787309	,	0.001110488949720	,	0.000232384141843	,	0.000041368441216	,	0.000006264728404	,	0.000000807059884	,	0.000000088446305	,	0.000000008245634	,	0.000000000653941	,	0.000000000044119	,	0.000000000002532	,	0.000000000000124	,	0.000000000000005	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,
                    0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000002	,	0.000000000000044	,	0.000000000000959	,	0.000000000017624	,	0.000000000275422	,	0.000000003661609	,	0.000000041410991	,	0.000000398409528	,	0.000003260725411	,	0.000022702263630	,	0.000134460437281	,	0.000677470358381	,	0.002903731788591	,	0.010587492655991	,	0.032839774572585	,	0.086651809156732	,	0.194502650541229	,	0.371401655695462	,	0.603298949532648	,	0.833665299676626	,	0.979989229788574	,	0.979989229788573	,	0.833665299676626	,	0.603298949532648	,	0.371401655695462	,	0.194502650541230	,	0.086651809156732	,	0.032839774572584	,	0.010587492655991	,	0.002903731788591	,	0.000677470358381	,	0.000134460437281	,	0.000022702263630	,	0.000003260725411	,	0.000000398409528	,	0.000000041410991	,	0.000000003661609	,	0.000000000275422	,	0.000000000017624	,	0.000000000000959	,	0.000000000000044	,	0.000000000000002	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,
                    0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000005	,	0.000000000000124	,	0.000000000002532	,	0.000000000044119	,	0.000000000653941	,	0.000000008245634	,	0.000000088446305	,	0.000000807059884	,	0.000006264728404	,	0.000041368441216	,	0.000232384141843	,	0.001110488949720	,	0.004514320787309	,	0.015611369907454	,	0.045926149376506	,	0.114934252555233	,	0.244686123044255	,	0.443138645431393	,	0.682716397693996	,	0.894770102422756	,	0.997592135400629	,	0.946160887586890	,	0.763391619310985	,	0.523962501181356	,	0.305930972671621	,	0.151955740231385	,	0.064206825124425	,	0.023078931750230	,	0.007057008364691	,	0.001835675804636	,	0.000406201719294	,	0.000076464165467	,	0.000012244599110	,	0.000001668021372	,	0.000000193298762	,	0.000000019055790	,	0.000000001598068	,	0.000000000114008	,	0.000000000006919	,	0.000000000000357	,	0.000000000000016	,	0.000000000000001	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,
                    0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000009	,	0.000000000000211	,	0.000000000004196	,	0.000000000071093	,	0.000000001024741	,	0.000000012565289	,	0.000000131069417	,	0.000001163056115	,	0.000008779512319	,	0.000056378113316	,	0.000307979001018	,	0.001431205827213	,	0.005657877077737	,	0.019027220097393	,	0.054433667749669	,	0.132473886108031	,	0.274260571689522	,	0.483021986324738	,	0.723670458356205	,	0.922327613321088	,	1.000000000000000	,	0.922327613321087	,	0.723670458356207	,	0.483021986324738	,	0.274260571689522	,	0.132473886108031	,	0.054433667749669	,	0.019027220097393	,	0.005657877077737	,	0.001431205827213	,	0.000307979001018	,	0.000056378113316	,	0.000008779512319	,	0.000001163056115	,	0.000000131069417	,	0.000000012565289	,	0.000000001024741	,	0.000000000071093	,	0.000000000004196	,	0.000000000000211	,	0.000000000000009	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	,	0.000000000000000	;


            std::shared_ptr<LinearizedEulerEquationsDE<double>> de = std::make_shared<LinearizedEulerEquationsDE<double>>();
            std::shared_ptr<System1D<double>> s = std::make_shared<System1D<double>>(K, N, -2.0, 0.0, de);

            MatrixX<double> p(N+1,K);
            for(int k = 0; k  < K; k++)
            {
                p.col(k) = s->Elements[k]->u[0];
            }

            BOOST_CHECK(p.isApprox(pExpected));
        }

    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()