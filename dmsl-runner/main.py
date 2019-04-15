import os
import sys
import urllib.request
import urllib.parse
import json
import base64
import time

def json_paser(injson):
    print(injson)
    injson = injson.replace('*s', ' ')
    injson = injson.replace('*y', '"')
    print(injson)
    jsonin = json.loads(injson)
    if jsonin["language"] is "dmsl":
        code = jsonin["code"]
        return code


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


def back_post(str, address):
    url = str(address)
    headers = {
        'User-Agent': 'Mozilla/5.0 (Windows NT 10.0;Win64;x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/72.0.3626.119 Safari/537.36',
        'Content-Type': 'application/x-www-form-urlencoded;charset=UTF-8',
    }
    values = {
        'stdout': str
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
        back_post(dmsl_runner(json_paser(instr)), address)