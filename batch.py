import os
import time
import subprocess
import psutil
import platform

from datetime import datetime
import csv
from collections import defaultdict

res_path = "res/matrices/"
data_file = "data/data.csv"

def run_subprocess(cmd):

    flag = False
    #if cmd[0] == "matlab":
    #    flag = True
    #    cmd = cmd[1]

    p = subprocess.Popen(cmd, shell = flag)
    proc = psutil.Process(p.pid)
    mem_table = []

    while p.poll() == None:
        mem = proc.memory_info()
        mem_table.append((mem.rss, mem.vms)) #in bytes
        time.sleep(1)

    peak_mem = [max(y) for y in zip(*mem_table)]

    with open(data_file, "a") as logfile:
        logfile.write(str(peak_mem[0]) + ", " + str(peak_mem[1]) + "\n")

def main():

    if not os.path.exists("data/"):
        os.makedirs("data/")
    
    if not os.path.exists("data/data.csv"):
        with open(data_file, "a") as logfile:
            header_writer = csv.writer(logfile, delimiter=",")
            header_writer.writerow(["date", "platform", "name", "library", "factorization time", "resolution time", "relative error", "physical memory", "virtual memory"])

    res_list = os.listdir(res_path)

    matrices = []

    for file in res_list:
        path = os.path.join(res_path, file)
        size = os.path.getsize(path)
        matrices.append((size, path))

    matrices.sort(key = lambda s: s[0])

    # For debug
    matrices = matrices[:2]

    for mat in matrices:
        mat_name = mat[1]
        _, ext = os.path.splitext(mat_name)

        if(ext == ".mat"):
            # Run MATLAB script
            cmd = ["matlab", "-batch", "cd matlab;main(\'../" + mat_name + "\');"]
            #cmd = ["matlab", "matlab -nojvm -nodisplay -nosplash -nodesktop -r \"try;cd matlab;main(\'../" + mat_name + "\');catch;end;quit;\""]
            #cmd = ["matlab", "-nojvm", "-nodisplay", "-nosplash", "-nodesktop", "-r", "\"try;cd matlab;main(\'../" + mat_name + "\');catch;end;quit;\""]
            print(f"running matlab for {mat_name}")
            run_subprocess(cmd)

        else:
            # Run Python script, then C++
            platform_str = platform.system()

            if (platform_str != "Windows"):
                cmd = ["python", "python/main.py", mat_name]
                print(f"running python for {mat_name}")
                run_subprocess(cmd)
            
            cmd = ["c++/main.exe", mat_name]
            print(f"running c++ for {mat_name}")
            run_subprocess(cmd)

    #timestamp = datetime.now().strftime('%d%m%Y%H%M%S')
    #os.rename(data_file, "log/data-" + timestamp + ".csv")

main()

