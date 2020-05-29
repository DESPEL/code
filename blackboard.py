import requests
import json
import time

def login(session, csrf, username, password):

    data = {
        'user_id': username,
        'password': password,
        'login': 'Iniciar sesi\xF3n',
        'action': 'login',
        'new_loc': '',
        'blackboard.platform.security.NonceUtil.nonce': csrf
    }
    response = session.post('https://cetys.blackboard.com/webapps/login/', data=data)

    #for x in response:
    #    print(x)
    return response

def getAlerts(session):
    data = {
    'cmd': 'view',
    'streamName': 'alerts',
    'providers': '{}',
    'forOverview': 'false'
    }
    r = session.post('https://cetys.blackboard.com/webapps/streamViewer/streamViewer',data=data)
    data = {
    'cmd': 'loadStream',
    'streamName': 'alerts',
    'providers': '{}',
    'forOverview': 'false'
    }
    r = session.post('https://cetys.blackboard.com/webapps/streamViewer/streamViewer',data=data)
    alerts = json.loads(r.text)
    return alerts

def printAlerts(alerts):
    for alert in alerts["sv_streamEntries"]:
        print(alert["itemSpecificData"]["title"])
s = requests.Session()
r = s.get('http://cetys.blackboard.com/webapps/login/')

#print(r.text)

csrf = r.text.split("<input type=\'hidden\' name=\'blackboard.platform.security.NonceUtil.nonce\' value=\'")[1].split("\'")[0]


print("headers: ")
print(s.headers)
print("cookies: ")
print(s.cookies)

#print("csrf token: ", csrf)

r = login(s, csrf, "username", "password")

#print("headers: ")
#print(r.headers)
print("cookies:")
print(r.cookies)

print("session info:")
print(s.cookies)

alerts = getAlerts(s)
print("alerts")
#printAlerts(alerts)
