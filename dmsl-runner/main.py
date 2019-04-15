import os
import sys
import json
import time

def json_paser(injson):
    jsonin = json.loads(injson)
    if jsonin["language"] is "dmsl":
        code = jsonin["code"]
        return code
    else:
        print("Error in json")
        pass


def dmsl_runner(code):
    temp = str(time.time()).replace(".", "a")[0: 6]
    ok_dir = os.mkdir("/tmp/" + temp)
    if ok_dir is True:
        path = "/tmp/" + temp + "main.dmsl"
        f = open(path, "w+")
        f.write(code)
        f.close
        outstd = os.pipe("DmslRunner " + path)
        return outstd
    else:
        print("Error in creat files")
        pass


if __name__ == "__main__":
    instr = sys.argv[1]
    print(dmsl_runner(json_paser(instr)))

