import os

csv = open("times.csv", "w")
csv.write("name,init,mult,size_x,size_y,run_nr,time\n")
for f in os.listdir("./times"):
    mult = "MULT" in f
    init = "INIT" in f
    if "REFERENCE" in f: 
        size_x = size_y = None
    else:
        size_x = f.split("_")[-3]
        size_y = f.split("_")[-2]
    run_nr = f.split("_")[-1].split(".")[0]
    fp = open(f"times/{f}", "r")
    time = float(fp.read())
    fp.close()
    csv.write(f"{init}{mult}{size_x}{size_y},{init},{mult},{size_x},{size_y},{run_nr},{time}\n")

csv.close()

