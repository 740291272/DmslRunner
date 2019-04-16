import os
import sys
import json
import time
import base64
import subprocess


DEBUG = 0


def json_paser(injson):
    injson = str.encode(injson)
    injson = base64.b64decode(injson)
    jsonin = json.loads(injson)
    if jsonin["language"] == "dmsl":
        code = jsonin["code"]
        code = bytes.decode(base64.b64decode(code))
        if DEBUG == 1:
            print(code)
        return code
    else:
        print("json error")


def dmsl_runner(code):
    temp = str(time.time()).replace(".", "a")[0: 13]
    os.mkdir("/tmp/" + temp)
    path = "/tmp/" + temp
    f = open(path + "/demo.dmsl", "w+")
    f.write(code)
    f.close()
    run_path = "cd " + path + " && DmslRunner demo.dmsl"

    try:
        outstd = subprocess.Popen(run_path, shell=True, stdout=subprocess.PIPE)
        outstd.wait()
        if DEBUG == 1:
            print(path)
            print(run_path)
            print(outstd)
        out = outstd.stdout.read()
        out = bytes.decode(out)
    except:
        out = "你的dmsl代码错误啦，回去重新学！"
    return out


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Arg Error")
    else:
        instr = sys.argv[1]
        sta1 = json_paser(instr)
        sta2 = dmsl_runner(sta1)
        print(sta2)