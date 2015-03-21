########################################################################
#                                                                      #
# This file is part of openPSTD.                                       #
#                                                                      #
# openPSTD is free software: you can redistribute it and/or modify     #
# it under the terms of the GNU General Public License as published by #
# the Free Software Foundation, either version 3 of the License, or    #
# (at your option) any later version.                                  #
#                                                                      #
# openPSTD is distributed in the hope that it will be useful,          #
# but WITHOUT ANY WARRANTY; without even the implied warranty of       #
# MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the        #
# GNU General Public License for more details.                         #
#                                                                      #
# You should have received a copy of the GNU General Public License    #
# along with openPSTD.  If not, see <http://www.gnu.org/licenses/>.    #
#                                                                      #
########################################################################

__author__ = 'michiel'


import operations.BaseOperation
import os
import sys
import subprocess
import copy
import pickle
import pstd_data
import json

class Simulate(operations.BaseOperation.LongOperation):
    def __init__(self):
        super(Simulate, self).__init__()
        self.pstd_meshdata = None
        self.create_array = True
        self.create_plots = False

    def process(self, r):
        scene_desc = copy.deepcopy(r.model.SceneDesc)

        scene_desc['plotdir'] = os.path.join(r.model.get_calculation_directory(), scene_desc['plotdir'])

        print("Output directory: " + scene_desc['plotdir'])

        arguments = [sys.executable, "kernel/pstd.py", '-c']
        if self.create_array:
            arguments.append('-a')
        if self.create_plots:
            arguments.append('-p')

        sp = subprocess.Popen(arguments, stdin=subprocess.PIPE, stdout=subprocess.PIPE)

        pickle.dump(scene_desc, sp.stdin, 0)
        sp.stdin.flush()

        self.pstd_meshdata = pstd_data.PickleStream(sp.stdout).get()
        r.model.Simulation.simulation_result_pstd_mesh = self.pstd_meshdata
        r.model.Simulation.simulation_result_path = scene_desc['plotdir']

        while True:
            status = pstd_data.PickleStream(sp.stdout).get()
            self.change_status_text(status['message'])
            if status['status'] == 'running':
                r.model.Simulation.update_frame_info()
            elif status['status'] == 'success':
                return True
            elif status['status'] == 'error':
                return False




class CreateMovie(operations.BaseOperation.operation):
    def __init__(self):
        pass

    def run(self, r):
        pass