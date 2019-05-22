import os
import time
import subprocess
import psutil

def run_subprocess(cmd):
    logs_list = os.listdir(log_path)

    p = subprocess.Popen(cmd, shell=True)
    proc = psutil.Process(p.pid)
    mem_table = []

    while p.poll() == None:
        mem = proc.memory_info()
        mem_table.append((mem.rss, mem.vms)) #in bytes
        time.sleep(1)

    new_logs_list = os.listdir(log_path)
    target_log = list(set(new_logs_list) - set(logs_list))

    avg_mem = [sum(y) / len(y) for y in zip(*mem_table)]

    if (len(target_log) == 1):
        logfile = open(log_path + target_log[0], "a")
        logfile.write("Physical memory, " + str(avg_mem[0]) + "\n")
        logfile.write("Virtual memory, " + str(avg_mem[1]) + "\n")

        logfile.close()

res_path = "res/matrices/"
log_path = "log/"
res_list = os.listdir(res_path)

matrices = []

for file in res_list:
    path = os.path.join(res_path, file)
    size = os.path.getsize(path)
    matrices.append((size, path))

matrices.sort(key = lambda s: s[0])

matrices = matrices[:2]

for mat in matrices:
    mat_name = mat[1]
    name, ext = os.path.splitext(mat_name)

    if(ext == ".mat"):
        # Run MATLAB script

        cmd = "matlab -nojvm -nodisplay -nosplash -nodesktop -r \"try;cd matlab;main(\'../" + mat_name + "\');catch;end;quit;\""  
        run_subprocess(cmd)

    else:
        # Run Python script, then C++
        cmd = "python python/main.py " + mat_name
        run_subprocess(cmd)

        cmd = "c++/main.exe " + mat_name
        run_subprocess(cmd)
            