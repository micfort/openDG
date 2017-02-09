//////////////////////////////////////////////////////////////////////////
//                                                                      //
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

//DGResult.frag

#version 330

uniform float v_log_min;
in float pressure2;
out vec4 color;

void main()
{
    //value is between -1 and +1, also the result is between 0 and 1 (everything below 0 will be ignored)
    float result = 20*(log(abs(pressure2))/log(10))/-v_log_min+1;
    color = vec4(clamp(result*3, 0, 1), clamp(result*3-1.0/3.0, 0, 1), clamp(result*3-2.0/3.0, 0, 1), 1);
}
