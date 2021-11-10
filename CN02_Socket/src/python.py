from socket import *
from threading import *
from datetime import *
import time
import os
import base64
import sys
import json

blocked = []

if not os.path.isdir("./cache"):
    os.makedirs("./cache")

f = open("blacklist.conf", 'r')
data = ""
while True:
    chunk = f.read()
    if not len(chunk):
        break
    data = chunk
f.close()
blocked = data.splitlines()

for file in os.listdir("./cache"):
    os.remove("./cache" + "/" + file)


def access(fileurl):
    if fileurl in keys:
        key = keys[fileurl]
    else:
        key = Lock()
        keys[fileurl] = key
    key.acquire()


def denied(fileurl):
    if fileurl in keys:
        key = keys[fileurl]
        key.release()
    else:
        print("Problem encoutered!!!")
        sys.exit(1)


def log(fileurl, cli_addr):
    fileurl = fileurl.replace("/", "__")
    if (fileurl not in logs):
        logs[fileurl] = []
    date = time.strptime(time.ctime(), "%a %b %d %H:%M:%S %Y")
    logs[fileurl].append({
        "datetime": date,
        "client": json.dumps(cli_addr)
    })


def cache(fileurl):
    try:
        log_address = logs[fileurl.replace("/", "__")]
        if (len(log_address) < 2):
            return False
        last = log_address[len(log_address) - 2]["datetime"]
        if datetime.fromtimestamp(time.mktime(last)) + datetime.timedelta(minutes=10) >= datetime.now():
            return True
        else:
            return False
    except Exception as e:
        print(e)
        return False


def getInfo(fileurl):
    if fileurl.startswith("/"):
        fileurl = fileurl.replace("/", "", 1)
    pathName = "./cache" + "/" + fileurl + fileurl.replace("/", "__")
    if os.path.isfile(pathName):
        lastmodified = time.strptime(time.ctime(path.getmtime(pathName)),
                                     "%a %b %d %H:%M:%S %Y")
        return pathName, lastmodified
    else:
        return pathName, None


def getCache(cli_addr, in4):
    access(in4["fullurl"])
    log(in4["fullurl"], cli_addr)
    docache = cache(in4["fullurl"])
    pathName, lastmodified = getInfo(in4["fullurl"])
    denied(in4["fullurl"])
    in4["DoCache"] = docache
    in4["pathName"] = pathName
    in4["timeModified"] = lastmodified
    return in4


def getSpace(fileurl):
    files = os.listdir("./cache")
    if len(files) < 3:
        return
    for file in files:
        access(file)
    lastmodified = min(logs[file][-1]["datetime"] for file in files)
    deleteFile = [
        file for file in files
        if keys[file][-1]["datetime"] == lastmodified][0]

    os.remove("./cache" + "/" + deleteFile)
    for file in files:
        denied(file)


def details(cli_addr, cli_data):
    try:
        lines = cli_data.splitlines()
        while lines[len(lines) - 1] == "":
            lines.remove('')
        firstline = lines[0].split()
        url = firstline[1]

        urlpos = url.find("://")
        if (urlpos != -1):
            protocol = url[:urlpos]
            url = url[(urlpos + 3):]
        else:
            protocol = "http"

        portpos = url.find(":")
        pathpos = url.find("/")
        if (pathpos == -1):
            pathpos = len(url)
        if portpos == -1 or pathpos < portpos:
            serverport = 80
            server = url[:pathpos]
        else:
            serverport = int(url[(portpos + 1):pathpos])
            server = url[:portpos]

        firstline[1] = url[pathpos:]
        lines[0] = " ".join(firstline)
        cli_data = "\r\n".join(lines) + '\r\n\r\n'

        return{
            "serverport": serverport,
            "serverurl": server,
            "fullurl": url,
            "clientdata": cli_data,
            "protocol": protocol,
            "method": firstline[0],
        }
    except Exception as e:
        print(e)
        print
        return None


def insertHeader(in4):
    lines = in4["clientdata"].splitlines()
    while lines[len(lines) - 1] == '':
        lines.remove('')

    head = time.strftime("%a %b %d %H:%M:%S %Y", in4["timeModified"])
    head = "If-Modified-Since: " + head
    lines.append(head)

    in4["clientdata"] = "\r\n".join(lines) + "\r\n\r\n"
    return in4


def GET(cli_socket, cli_addr, in4):
    try:
        cli_data = in4["clientdata"]
        docache = in4["DoCache"]
        pathName = in4["pathName"]
        timeModified = in4["timeModified"]

        ser_socket = socket(AF_INET, SOCK_STREAM)
        ser_socket.connect((in4["serverurl"], in4["serverport"]))
        ser_socket.send(in4["clientdata"])

        reply = ser_socket.recv(8192)
        if timeModified and "Not Modified" in reply:
            print("Returning cached file %s to %s" % (pathName, str(cli_addr)))
            print("\n")
            access(in4[fileurl])
            f = open(pathName, 'rb')
            chunk = f.read(8192)
            while chunk:
                cli_socket.send(chunk)
                chunk = f.read(8192)
            f.close()
            denied(in4["fullurl"])

        else:
            if docache:
                print("Caching file %s to %s" % (pathName, str(cli_addr)))
                print("\n")
                access(in4["fullurl"])
                f = open(pathName, "w+")
                while len(reply):
                    cli_socket.send(reply)
                    f.write(reply)
                    reply = ser_socket.recv(8192)
                f.close()
                denied(in4["fullurl"])
                cli_socket.send("\r\n\r\n")
            else:
                print("Without caching serving %s to %s" %
                      (pathName, str(cli_addr)))
                print("\n")
                while len(reply):
                    cli_socket.send(reply)
                    reply = ser_socket.recv(8192)
                cli_socket.send("\r\n\r\n")
        ser_socket.close()
        cli_socket.close()
        return
    except Exception as e:
        ser_socket.close()
        cli_socket.close()
        print(e)
        return


def POST(cli_socket, cli_addr, in4):
    try:
        ser_socket = socket(AF_INET, SOCK_STREAM)
        ser_socket.connect((in4["serverurl"], in4["serverport"]))
        ser_socket.send(in4["clientdata"])

        while True:
            reply = ser_socket.recv(8192)
            if (len(reply)):
                cli_socket.send(reply)
            else:
                break
        ser_socket.close()
        cli_socket.close()
        return
    except Exception as e:
        ser_socket.close()
        cli_socket.close()
        print(e)
        return


def firewall(cli_socket, cli_addr, in4):
    if not (in4["serverurl"]) in blocked:
        return False
    return True


def handle(cli_socket, cli_addr, cli_data):
    in4 = details(cli_addr, cli_data)
    if not in4:
        print("No details")
        print("\n")
        cli_socket.close()
        return

    isb = firewall(cli_socket, cli_addr, in4)
    if isb:
        with open('Forbidden.html', 'r') as f:
            html_string = f.read()
            cli_socket.send(html_string.encode())
    elif in4["method"] == "GET":
        in4 = getCache(cli_addr, in4)
        if in4["timeModified"]:
            in4 = insertHeader(in4)
        GET(cli_socket, cli_addr, in4)
    elif in4["method"] == "POST":
        POST(cli_socket, cli_addr, in4)

    cli_socket.close()
    print("\n")
    print


def start():
    try:
        proxy_sock = socket(AF_INET, SOCK_STREAM)
        proxy_sock.setsockopt(SOL_SOCKET, SO_REUSEADDR, 1)
        proxy_sock.bind(('127.0.0.1', 8888))
        proxy_sock.listen(50)

        print("SERVING PROXY ON %s port %s..." % (
            str(proxy_sock.getsockname()[0]),
            str(proxy_sock.getsockname()[1])
        ))
    except Exception as e:
        print("ERROR!!!")
        print("\n")
        print(e)
        proxy_sock.close()
        raise SystemExit

    while True:
        try:
            cli_socket, cli_addr = proxy_sock.accept()
            cli_data = cli_socket.recv(8192)
            Thread(target=handle, args=(cli_socket, cli_addr, cli_data,)).start()

        except KeyboardInterrupt:
            cli_socket.close()
            proxy_sock.close()
            print("Shutting down!!!...")
            print("\n")
            break


keys = {}
logs = {}
start()
