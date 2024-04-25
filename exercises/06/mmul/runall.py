import os

def srun(program, name=None, meassure_cmd="time", run_cmd = None):
    name = program
    if (meassure_cmd=="time"):
        os.system("mkdir -p times")
        meassure_cmd=f"/usr/bin/time -o ./times/{name}.time -f 'e'",
    run_cmd = f"srun --partition=lva --job-name fa-{name} --output=output/{name}.log --ntasks=1 --ntasks-per-node=1 --exclusive"
    os.system(f"{run_cmd} {meassure_cmd} {program}")

# run all files in build
for program_file in os.listdir("./build"):
    # srun files
    print(program_file)
    srun(program_file)

