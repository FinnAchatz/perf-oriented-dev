import os


def sbatch(program, name=None, meassure_cmd="time", run_cmd="sbatch"):
    name = program
    if (meassure_cmd=="time"):
        os.system("mkdir -p times")
        meassure_cmd = f"/usr/bin/time -o ./times/{name}.time -f '%e'"
    script_file = open(f"scripts/{name}.sh", "w")
    
    script = f"""
#!/bin/bash

# Execute job in the partition "lva" unless you have special requirements.
#SBATCH --partition=lva
# Name your job to be able to identify it later
#SBATCH --job-name fa-{name}
# Redirect output stream to this file
#SBATCH --output=output/{name}.log
# Maximum number of tasks (=processes) to start in total
#SBATCH --ntasks=1
# Maximum number of tasks (=processes) to start per node
#SBATCH --ntasks-per-node=1
# Enforce exclusive node allocation, do not share with other jobs
#SBATCH --exclusive

echo -n \"{program}\  "  
{meassure_cmd} ./build/{program}
    """
    script_file.write(script)
    script_file.close()
    os.system(f"{run_cmd} ./scripts/{name}.sh")




os.system("mkdir -p scripts")
# run all files in build
for program_file in os.listdir("./build"):
    # sbatch files
    sbatch(program_file, run_cmd="bash")

