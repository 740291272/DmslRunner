import os
import sys
import urllib.request
import urllib.parse
import json
import time
import base64


DEBUG = 0


def json_paser(injson):
    injson = base64.b64decode(injson)
    jsonin = json.loads(injson)
    if jsonin["language"] == "dmsl":
        code = jsonin["code"]
        code = base64.b64decode(code)
        if DEBUG == 1:
            print(code)
        return code
    else:
        print("json error")


def dmsl_runner(code):
    temp = str(time.time()).replace(".", "a")[0: 9]
    os.mkdir("/tmp/" + temp)
    path = "/tmp/" + temp + "/main.dmsl"
    f = open(path, "w+")
    f.write(code)
    run_path = "DmslRunner " + path
    outstd = os.popen(run_path)
    if DEBUG == 1:
        print(path)
        print(run_path)
        print(outstd)
    return outstd


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Arg Error")
    else:
        instr = sys.argv[1]
        if len(sys.argv) == 3:
            DEBUG = sys.argv[2]
        sta1 = json_paser(instr)
        sta2 = dmsl_runner(sta1)
        sta2 = sta2.read()
        print(sta2)