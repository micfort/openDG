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
// Date: 7-11-2016
//
//
// Authors: M. R. Fortuin
//
//
// Purpose:
//
//
//////////////////////////////////////////////////////////////////////////

#include "Macros.h"

#include <boost/test/unit_test.hpp>
#include <kernel/DG/Simplex.h>
#include <iostream>

using namespace OpenPSTD::Kernel;
using namespace OpenPSTD::Kernel::DG;
using namespace std;
using namespace Eigen;

BOOST_AUTO_TEST_SUITE(DG)
    BOOST_AUTO_TEST_SUITE(Simplex_tests)
        BOOST_AUTO_TEST_CASE(Simplex_1)
        {
            int i = 0;
            int j = 0;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedP(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedP << 0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746,0.70710678118654746;

            VectorX<double> P = Simplex2DP(ab, i, j);
            BOOST_CHECK(P.isApprox(expectedP));

        }

        BOOST_AUTO_TEST_CASE(Simplex_2)
        {
            int i = 3;
            int j = 2;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedP(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedP << -4.5825756949558416,-2.9143278417841145,-0.13853446706593461,1.8164598049806335,1.7366136529073219,-1.5263043145882799e-15,-1.7366136529073211,-1.8164598049806335,0.13853446706593461,2.9143278417841052,4.5825756949558416,-1.6571000185148597,-0.38826604355062011,0.066367041544620364,0.12989488681796921,0.057375509068556943,-0.057375509068557061,-0.12989488681796701,-0.066367041544619781,0.38826604355063066,1.6571000185148597,1.681276916061363,0.79135758664900668,-0.6153403960089745,-0.89295118001144902,7.1715148382183836e-16,0.89295118001144902,0.61534039600897428,-0.79135758664900391,-1.6812769160613594,1.6444415956772414,0.26808197510597731,-0.21868244403804443,-0.10562029066098119,0.10562029066098171,0.21868244403804588,-0.26808197510598042,-1.6444415956772358,-0.96828663004836946,-0.24177383506977279,0.92845157928044808,-7.213717806579591e-16,-0.92845157928044963,0.24177383506977257,0.9682866300483669,-2.7209043188800313,0.14255085161795647,0.99996112319794639,-0.99996112319794694,-0.1425508516179603,2.720904318880033,-2.2264993026505313,0.52947020467895256,-1.1316312587683043e-15,-0.52947020467895478,2.2264993026505326,-0.89603834613334765,0.28086277797666204,-0.2808627779766612,0.89603834613334687,-0.15447761642988875,-6.3030320742959133e-16,0.15447761642988989,-0.0054490328902924044,0.0054490328902926221,-0;

            VectorX<double> P = Simplex2DP(ab, i, j);
            BOOST_CHECK(P.isApprox(expectedP));

        }

        BOOST_AUTO_TEST_CASE(Simplex_3)
        {
            int i = 10;
            int j = 10;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedP(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedP << 14.849242404917472,-6.0477434501119758,4.6281238163909348,-4.0202679162248192,3.7382942137532784,-3.6543057480851533,3.7382942137532797,-4.0202679162248192,4.6281238163909348,-6.0477434501118932,14.849242404917472,4.2537648087368867,-0.94001624668457207,0.19952443725103763,-0.038267878911089258,0.0063064412868570601,0.0063064412868572978,-0.038267878911086774,0.1995244372510408,-0.94001624668458461,4.2537648087368867,1.10539416672691,-0.4032785632810672,-0.24806869315693914,0.26443318957977702,-0.22765779645004028,0.26443318957978112,-0.24806869315693811,-0.40327856328105433,1.1053941667268934,-2.2337013202062517,0.21493749123792846,-0.95806713976717395,0.4188544315576776,0.41885443155767826,-0.95806713976717517,0.21493749123791564,-2.2337013202061864,-3.5415642770599729,-0.32770363573883671,-0.12020044970693751,-0.60199228514762637,-0.12020044970694138,-0.32770363573883332,-3.5415642770599685,1.2085854948094354,-1.1647175000092069,-1.2109522679638625,-1.2109522679638627,-1.1647175000092036,1.2085854948094017,3.4476725566234676,-0.81630702555046941,-1.8026437787395675,-0.81630702555047996,3.4476725566234525,2.9659335131966524,-0.035937179812260862,-0.035937179812258017,2.9659335131966471,0.024717070155542302,-0.0015996043703693991,0.024717070155543731,6.1567755082554687e-07,6.1567755082577282e-07,0;

            VectorX<double> P = Simplex2DP(ab, i, j);
            BOOST_CHECK(P.isApprox(expectedP));

        }

        BOOST_AUTO_TEST_CASE(GradSimplex2D_1)
        {
            int id = 0;
            int jd = 1;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedDmodedr(66);
            VectorX<double> expectedDmodeds(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedDmodedr << -0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,-0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0;
            expectedDmodeds << 1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5,1.5;

            GradSimplex2DPResult<double> result = GradSimplex2DP(ab, id, jd);
            BOOST_CHECK(result.dmodedr.isApprox(expectedDmodedr));
            BOOST_CHECK(result.dmodeds.isApprox(expectedDmodeds));
        }

        BOOST_AUTO_TEST_CASE(GradSimplex2D_2)
        {
            int id = 5;
            int jd = 3;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedDmodedr(66);
            VectorX<double> expectedDmodeds(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedDmodedr << -105.53435459602713,-62.900866971744207,-4.4539457264850943,17.535977579575455,0.84346573793260349,-13.191794324503388,0.84346573793258506,17.535977579575455,-4.4539457264850943,-62.900866971743923,-105.53435459602713,10.83169820246526,14.556538108127864,-3.2286437713337746,-5.2693495440981595,3.4944763528204779,3.4944763528204703,-5.2693495440981568,-3.2286437713337448,14.556538108127461,10.83169820246526,34.761311622452993,3.9482643049932675,0.26049664381316884,0.35619214202166416,-1.1726030325324925,0.35619214202165866,0.260496643813173,3.9482643049931578,34.761311622452844,-49.265724352565428,-13.149596593528713,8.2005368200457127,-2.7094522526302449,-2.7094522526302471,8.2005368200457252,-13.149596593528846,-49.265724352565243,-1.9042553321374944,4.8287190261458717,-7.3601955563416483,8.0217146811879534,-7.3601955563416848,4.8287190261458814,-1.904255332137609,108.83230317715289,-1.9409442442422489,0.33040724000792177,0.33040724000787908,-1.9409442442423543,108.83230317715304,100.53839461971748,-11.706333047853812,9.1548423415939233,-11.706333047853855,100.53839461971747,32.916518993905406,-2.4438447298416999,-2.4438447298416817,32.916518993905392,3.3520512171612529,0.23521594484304306,3.3520512171612831,0.040141491172034346,0.040141491172036213,0;
            expectedDmodeds << -175.89059099337868,-40.651187750113927,72.283987303553374,15.415218400536599,-60.560783784447814,-6.5958971622516227,61.404249522380432,2.1207591790388607,-76.737933030038462,-22.249679221630394,70.356236397351566,-67.981184483521915,1.3106411935432616,10.663701234842874,-5.7607031343911093,-4.707235608685453,8.2017119615059357,0.49135359029295933,-13.892345006176646,13.24589691458389,78.812882685987191,23.493312389840728,-4.0867050976525992,-7.1298511855365989,8.3884832630144057,-0.58630151626625682,-8.0322911209927543,7.390347829349766,8.0349694026458298,11.267999232612247,7.3998993377063256,0.24946540820930457,2.5301913291079119,-4.6036421830774081,1.8941899304471581,5.6703454909378168,-13.399062001738127,-56.665623690271495,-18.150642835821365,6.536038665177057,-4.4836216344599604,4.0108573405939829,-2.8765739218817274,-1.70731963903118,16.246387503683753,-3.2979485811258753,-1.3204381823300779,1.7376918450417069,-1.4072846050338117,-0.62050606191225743,112.13025175827887,8.4763506926497225,-4.235199477314068,4.5774211707969572,-7.4711335705397843,92.062043927067748,4.2378160314883777,-0.099818045248708159,-2.3440266845929796,28.678702962417017,0.5062022618339268,0.11760797242151975,2.8458489553273494,0.0065173052195185953,0.033624185952517101,0;

            GradSimplex2DPResult<double> result = GradSimplex2DP(ab, id, jd);
            BOOST_CHECK(result.dmodedr.isApprox(expectedDmodedr));
            BOOST_CHECK(result.dmodeds.isApprox(expectedDmodeds));
        }

        BOOST_AUTO_TEST_CASE(GradSimplex2D_3)
        {
            int id = 7;
            int jd = 4;
            VectorX<double> a(66);
            VectorX<double> b(66);
            ArrayXX<double> ab(66, 2);
            VectorX<double> expectedDmodedr(66);
            VectorX<double> expectedDmodeds(66);

            a << -1,-0.9340014304080595,-0.7844834736631443,-0.56523532699620493,-0.29575813558693942,2.2204460492503131e-16,0.2957581355869392,0.56523532699620493,0.7844834736631443,0.93400143040805927,1,-1,-0.9039230039283328,-0.71618941421050597,-0.45862057964924374,-0.15774783927380909,0.15774783927380942,0.4586205796492433,0.71618941421050653,0.90392300392833169,1,-1.0000000000000004,-0.87988402041245672,-0.65073852599441051,-0.34488312271287414,2.2204460492503131e-16,0.34488312271287391,0.65073852599441051,0.87988402041245628,1,-0.99999999999999989,-0.85382070209978722,-0.57103752274935116,-0.20033546136011937,0.20033546136011937,0.57103752274935093,0.85382070209978789,0.99999999999999933,-1,-0.81706949643142879,-0.45741175337943896,2.2204460492503131e-16,0.45741175337943929,0.81706949643142868,1,-1,-0.75687614006542048,-0.28161624176456224,0.28161624176456268,0.75687614006542003,1,-1,-0.64955122615731642,4.4408920985006262e-16,0.64955122615731598,1,-1,-0.44261358688404373,0.44261358688404306,1,-0.999999999999999,4.2188474935755949e-15,1,-1,1.0000000000000067,-1;
            b << -1,-1,-1,-1,-1,-1,-1,-1,-1,-0.99999999999999989,-1,-0.93400143040805939,-0.90832684462285529,-0.8960431364598922,-0.89123812190023532,-0.88986404113259854,-0.88986404113259854,-0.89123812190023521,-0.8960431364598922,-0.90832684462285618,-0.93400143040805939,-0.78448347366314441,-0.73094144337958478,-0.70266274923405247,-0.68975123147782536,-0.68613038577762142,-0.68975123147782558,-0.70266274923405236,-0.73094144337958422,-0.7844834736631443,-0.56523532699620505,-0.48806130091019845,-0.44650772492108542,-0.42874260283457399,-0.42874260283457416,-0.44650772492108576,-0.48806130091019867,-0.56523532699620505,-0.2957581355869392,-0.20412896393866919,-0.15693480711118951,-0.14251479433085162,-0.15693480711118896,-0.20412896393866892,-0.29575813558693947,-2.7755575615628914e-16,0.093993005071267621,0.13625895639891117,0.13625895639891111,0.093993005071267788,2.7755575615628914e-16,0.29575813558693947,0.37929942281043405,0.40532549846810473,0.3792994228104335,0.2957581355869392,0.56523532699620493,0.62698457983947642,0.62698457983947686,0.56523532699620505,0.7844834736631443,0.81665368924571158,0.78448347366314419,0.9340014304080595,0.9340014304080595,1;
            ab << a, b;
            expectedDmodedr << 265.63132345414385,86.622035809974861,-39.022801443091289,6.6196461086991727,13.731782165946861,-20.75244714485499,13.731782165946827,6.6196461086991727,-39.022801443091289,86.622035809973937,265.63132345414385,-103.97311483326597,-15.909832502946333,13.522336354013127,-8.7538225131870462,3.0488233319526716,3.048823331952653,-8.7538225131870515,13.522336354013175,-15.90983250294572,-103.97311483326597,66.526753574881141,3.120423008531251,-6.6055864147945833,7.5227294842098473,-7.7452625496421446,7.5227294842098456,-6.6055864147945806,3.1204230085310618,66.526753574880885,-21.58794283345113,5.3803886420173219,-2.445550100746646,0.70979620948720856,0.70979620948720856,-2.4455501007466709,5.3803886420171372,-21.587942833450981,-73.730251790765578,-3.9798880891314905,8.0098204964021686,-8.6863614316931699,8.0098204964022131,-3.9798880891315336,-73.730251790765848,246.69471543446326,-40.30036497149932,11.729863382375521,11.729863382375582,-40.30036497149927,246.69471543446392,183.80141249978431,-7.7047272178861004,-8.4383974001857514,-7.7047272178860595,183.80141249978436,30.251856002089617,1.3200725002722531,1.3200725002722462,30.251856002089593,0.90216081475502008,-0.029306322248343841,0.90216081475503507,0.0011231981511142558,0.0011231981511143567,0;
            expectedDmodeds << 412.67723465197395,-64.233148999498425,-77.387846142420074,131.0809035478151,-90.223988243726296,-10.376223572427294,103.95577040967329,-124.46125743911594,38.365044699328791,150.85518480947309,-147.04591119783007,45.857971133148489,4.4339810269356299,-1.2481973615030313,-7.458366287124254,12.204690049023508,-9.1558667170708592,-1.2954562260628146,14.770533715516136,-20.34381352988088,-149.83108596641443,-37.132971940804573,2.4176029268986383,1.3467975358638968,0.34245328657401214,-3.8726312748210647,7.1802761976358243,-7.9523839506584935,0.70282008163255705,103.65972551568485,32.803626784814398,-6.9532045061535506,1.9164398261152709,-0.59260814182904487,1.3024043513162644,-4.3619899268619626,12.333593148170747,-54.391569618264874,-23.405704134907236,7.8054728617042146,-0.97921627532362476,-4.3431807158465974,8.9890367717258393,-11.785360950835742,-50.324547655858645,-5.7578776341640703,-5.2117219131161274,2.1158185141877306,9.6140448681878219,-35.088643058383155,252.45259306862789,12.061292873015493,1.32718281660548,-4.2191987000928677,-9.0319100344915615,171.74011962676889,2.959785106795854,0.50949066290450495,0.81058183736774603,27.29207089529374,0.102673875683473,-0.014653161124171586,0.79948693907155932,0.00013694253764280178,0.00098625561347153281,0;

            GradSimplex2DPResult<double> result = GradSimplex2DP(ab, id, jd);
            BOOST_CHECK(result.dmodedr.isApprox(expectedDmodedr));
            BOOST_CHECK(result.dmodeds.isApprox(expectedDmodeds));
        }

    BOOST_AUTO_TEST_SUITE_END()
BOOST_AUTO_TEST_SUITE_END()