import os

list_names = []
commands = ["register", "create", "showall", "join", "classwork", "people", "createpost", "viewpost", "exitclass", "showmy"]
def workload():
    for i in range (16):
        f1 = open("workloads/workload" + str(i) + ".txt", "w")
        for j in range (10):
            f1.write(commands[j] + "\n")
            if commands[j] == "register":
                f1.write(str(list_names[i]) + "\n")
                f1.write(str(list_names[i])+ "\n")
                f1.write(str(list_names[i])+ "\n")
            elif commands[j] == "create":
                f1.write(str(i)+ "\n")
            elif commands[j] == "join":
                f1.write(str(i)+ "\n")
            elif commands[j] == "createpost":
                f1.write(str(1) + "\n")
                f1.write(str(i)+ "\n")
                f1.write(str(i)+ "\n")
                f1.write(str(i)+ "\n")
                f1.write(str(i)+ "\n")
                f1.write(str(0)+ "\n")
            elif commands[j] == "viewpost":
                f1.write (str(1) + "\n")
                f1.write(str(i)+ "\n")
                f1.write(str(i)+ "\n")
        f1.close()

if __name__ == "__main__":
    for i in range (16):
        list_names.append(i)
    workload()    
