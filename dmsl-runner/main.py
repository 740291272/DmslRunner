import os
import sys
import urllib.request
import urllib.parse
import json
import time

def json_paser(injson):
    injson = injson.replace('*s', ' ')
    injson = injson.replace('*y', '"')
    jsonin = json.loads(injson)
    if jsonin["language"] == "dmsl":
        code = jsonin["code"]
        code = str(code).replace('*n', '\n')
        print(code)
        return code
    else:
        print("json error")


def dmsl_runner(code):
    temp = str(time.time()).replace(".", "a")[0: 10]
    os.mkdir("/tmp/" + temp)
    path = "/tmp/" + temp + "main.dmsl"
    f = open(path, "w+")
    f.write(code)
    outstd = os.popen("DmslRunner " + path).read()
    return outstd


def back_post(str_in, address):
    url = str(address)
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0;Win64;x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36',
        'Content-Type': 'application/x-www-form-urlencoded;charset=UTF-8',
    }
    values = {
        'stdout': str_in
    }
    data = urllib.parse.urlencode(values).encode('utf-8')
    request = urllib.request.Request(url, data, headers)
    output = urllib.request.urlopen(request).read().decode('utf-8')
    return output


if __name__ == "__main__":
    if len(sys.argv) < 2:
        print("Arg Error")
    else:
        instr = sys.argv[1]
        address = sys.argv[2]
        sta1 = json_paser(instr)
        sta2 = dmsl_runner(sta1)
        print(sta2)
        back_post(sta2, address)